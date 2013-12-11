/* 
 * Copyright (C) 2013  Nicholas Gill
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * svg.h
 *
 *  Created on: 2013-11-29
 *      Author: nicholas
 */

#ifndef SVG_H_
#define SVG_H_
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <boost/optional.hpp>

/*
Restored from history for alternate purpose.

Will form the basis of the C++ DOM model (and in time the js api)
*/

namespace dom
{
    // spec requires u16 (std::u16string). Changed to std::string for own purposes.
    typedef std::string DOMString;
    struct Node;
    struct Element;
    struct Document;

    struct DOMException : std::runtime_error
    {
        explicit DOMException(unsigned short code);
        unsigned short code;
    };

    enum ExceptionCode : unsigned short
    {
        INDEX_SIZE_ERR                 = 1,
        DOMSTRING_SIZE_ERR             = 2,
        HIERARCHY_REQUEST_ERR          = 3,
        WRONG_DOCUMENT_ERR             = 4,
        INVALID_CHARACTER_ERR          = 5,
        NO_DATA_ALLOWED_ERR            = 6,
        NO_MODIFICATION_ALLOWED_ERR    = 7,
        NOT_FOUND_ERR                  = 8,
        NOT_SUPPORTED_ERR              = 9,
        INUSE_ATTRIBUTE_ERR            = 10,
        INVALID_STATE_ERR              = 11,
        SYNTAX_ERR                     = 12,
        INVALID_MODIFICATION_ERR       = 13,
        NAMESPACE_ERR                  = 14,
        INVALID_ACCESS_ERR             = 15,
        VALIDATION_ERR                 = 16,
        TYPE_MISMATCH_ERR              = 17
    };

    struct QName
    {
        std::string ns;
        std::string local;
    };

    struct Node
    {
        QName name;
        std::shared_ptr<Node> parent;
        std::shared_ptr<Document> document;
        std::string content;
        std::shared_ptr<Node> next_sibling;
        std::shared_ptr<Node> prev_sibling;
        std::shared_ptr<Node> first_child;
        std::shared_ptr<Node> last_child;
        
        std::shared_ptr<Node> appendChild(std::shared_ptr<Node> newChild); // throw(DOMException);
        std::shared_ptr<Node> insertBefore(std::shared_ptr<Node> newChild, std::shared_ptr<Node> refChild); // throw(DOMException);
        std::shared_ptr<Node> removeChild(std::shared_ptr<Node> oldChild); // throw(DOMException);
        std::shared_ptr<Node> cloneNode(bool deep);
        
        virtual ~Node();
    };

    struct ElementTraversal
    {
        Element firstElementChild() const;
        Element lastElementChild() const;
        Element nextElementSibling() const;
        Element previousElementSibling() const;
        unsigned long childElementCount() const;
    };

    struct Element : Node, ElementTraversal
    {
        DOMString getAttributeNS(const boost::optional<DOMString>& namespaceURI, const DOMString& localName); // throw(DOMException);  
        void setAttributeNS(const boost::optional<DOMString>& namespaceURI, const DOMString& qualifiedName, const DOMString& value); // throw(DOMException);
        DOMString getAttribute(const DOMString& name);
        void setAttribute(const DOMString& name, const DOMString& value); // throw(DOMException);
    };

    struct Document : Node
    {
        Element createElementNS(const boost::optional<DOMString>& namespaceURI, const DOMString& qualifiedName); // throw(DOMException);
        Element documentElement() const;
        boost::optional<Element> getElementById(const DOMString& elementId);
    };

    struct Location
    {  
        void assign(const DOMString& iri);
        void reload();
    };

    struct Window
    {
        boost::optional<Window> parent() const;
        Location location() const;
    };

};

namespace views
{
    struct DocumentView;

    struct AbstractView
    {
        DocumentView document() const;
    };

    struct DocumentView
    {
        boost::optional<AbstractView> defaultView() const;
    };

};

namespace events
{
    typedef dom::DOMString DOMString;
    typedef dom::DOMException DOMException;
    typedef dom::Document Document;
    typedef dom::Element Element;
    struct EventTarget;
    struct EventListener;
    struct Event;    

    struct EventTarget
    {
        void addEventListener(const DOMString& type, std::shared_ptr<EventListener> listener, bool useCapture);
        void removeEventListener(const DOMString& type, std::shared_ptr<EventListener> listener, bool useCapture);
    };

    struct EventListener
    {
        virtual void handleEvent(Event& evt) =0;
        virtual ~EventListener();
    };

    struct Event
    {
        EventTarget target() const;
        EventTarget currentTarget() const;
        DOMString type() const;
        bool cancelable() const;
        bool defaultPrevented() const;
        void stopPropagation();
        void preventDefault();
    };

    struct UIEvent : Event
    {
        long detail() const;
    };

    struct MouseEvent : UIEvent
    {
        const long screenX;
        const long screenY;
        const long clientX;
        const long clientY;
        const unsigned short button;
    };

    struct MouseWheelEvent : MouseEvent
    {
        const long wheelDelta;
    };

    struct TextEvent : UIEvent
    {
        const DOMString data;
    };

    struct KeyboardEvent : UIEvent
    {
        const DOMString keyIdentifier;
    };

    struct ProgressEvent : Event
    {
        const bool lengthComputable;
        const unsigned long loaded;
        const unsigned long total;
    };

};

namespace smil
{
    typedef events::Event Event;

    struct ElementTimeControl
    {
        void beginElementAt(float offset);
        void beginElement();
        void endElementAt(float offset);
        void endElement();
    };

    struct TimeEvent : Event
    {
        const long detail;
    };

};

namespace svg
{
    typedef dom::DOMString DOMString;
    typedef dom::DOMException DOMException;
    typedef dom::Document Document;
    typedef dom::Element Element;
    typedef dom::Node Node;
    typedef events::Event Event;
    typedef events::EventListener EventListener;
    typedef events::EventTarget EventTarget;
    struct SVGSVGElement;
    struct SVGRGBColor;
    struct SVGRect;
    struct SVGPoint;
    struct SVGPath;
    struct SVGMatrix;
    struct SVGLocatableElement;
    struct SVGElement;
    struct SVGTimedElement;
    struct SVGDocument;
    struct SVGGlobal;

    struct SVGException : std::runtime_error
    {
        explicit SVGException(unsigned short code);
        unsigned short code;
    };

    enum ExceptionCode : unsigned short
    {
        SVG_WRONG_TYPE_ERR         = 0,
        SVG_INVALID_VALUE_ERR      = 1,
        SVG_MATRIX_NOT_INVERTABLE  = 2
    };

    struct SVGDocument : Document, EventTarget
    {
    };

    struct SVGLocatable
    {
        SVGRect   getBBox();
        SVGMatrix getScreenCTM();
        SVGRect   getScreenBBox();
    };

    struct TraitAccess
    {
        DOMString getTrait(const DOMString& name); // throw(DOMException);
        DOMString getTraitNS(const DOMString& namespaceURI, const DOMString& name); // throw(DOMException);
        float getFloatTrait(const DOMString& name); // throw(DOMException);
        std::vector<float> getFloatListTrait(const DOMString& name); // throw(DOMException);
        SVGMatrix getMatrixTrait(const DOMString& name); // throw(DOMException);
        boost::optional<SVGRect> getRectTrait(const DOMString& name); // throw(DOMException);
        SVGPath getPathTrait(const DOMString& name); // throw(DOMException);
        boost::optional<SVGRGBColor> getRGBColorTrait(const DOMString& name); // throw(DOMException);
        DOMString getPresentationTrait(const DOMString& name); // throw(DOMException);
        DOMString getPresentationTraitNS(const DOMString& namespaceURI, const DOMString& name); // throw(DOMException);
        float getFloatPresentationTrait(const DOMString& name); // throw(DOMException);
        std::vector<float> getFloatListPresentationTrait(const DOMString& name); // throw(DOMException);
        SVGMatrix getMatrixPresentationTrait(const DOMString& name); // throw(DOMException);
        boost::optional<SVGRect> getRectPresentationTrait(const DOMString& name); // throw(DOMException);
        SVGPath getPathPresentationTrait(const DOMString& name); // throw(DOMException);
        boost::optional<SVGRGBColor> getRGBColorPresentationTrait(const DOMString& name); // throw(DOMException);
        void setTrait(const DOMString& name, const DOMString& value); // throw(DOMException);
        void setTraitNS(const DOMString& namespaceURI, const DOMString& name, const DOMString& value); // throw(DOMException);
        void setFloatTrait(const DOMString& name, float value); // throw(DOMException);
        void setFloatListTrait(const DOMString& name, const std::vector<float>& value); // throw(DOMException);
        void setMatrixTrait(const DOMString& name, const SVGMatrix& matrix); // throw(DOMException);
        void setRectTrait(const DOMString& name, const SVGRect& rect); // throw(DOMException);
        void setPathTrait(const DOMString& name, const SVGPath& path); // throw(DOMException);
        void setRGBColorTrait(const DOMString& name, const SVGRGBColor& color); // throw(DOMException);
    };

    struct SVGElement : Element, EventTarget, TraitAccess
    {
        boost::optional<DOMString> id() const;
        void id(const DOMString& id) const;
    };

    struct SVGLocatableElement : SVGElement, SVGLocatable
    {
    };

    struct SVGUseElement : SVGLocatableElement
    {
    };

    struct SVGElementInstance : EventTarget
    {
        SVGElement correspondingElement() const;
        SVGUseElement correspondingUseElement() const;
    };

    struct SVGTimedElement : SVGElement, smil::ElementTimeControl
    {
        void pauseElement();
        void resumeElement();
        bool isPaused() const;
    };

    struct SVGSVGElement : SVGLocatableElement, SVGTimedElement
    {
        enum : unsigned short
        {
            NAV_AUTO           = 1,
            NAV_NEXT           = 2,
            NAV_PREV           = 3,
            NAV_UP             = 4,
            NAV_UP_RIGHT       = 5,
            NAV_RIGHT          = 6,
            NAV_DOWN_RIGHT     = 7,
            NAV_DOWN           = 8,
            NAV_DOWN_LEFT      = 9,
            NAV_LEFT           = 10,
            NAV_UP_LEFT        = 11
        };
        float currentScale() const;
        void currentScale(float scale);
        float currentRotate() const;
        void currentRotate(float rotate);
        SVGPoint& currentTranslate() const;
        const SVGRect& viewport() const;
        float getCurrentTime();
        void setCurrentTime(float seconds);
        SVGMatrix createSVGMatrixComponents(float a, float b, float c, float d, float e, float f);
        SVGRect createSVGRect();
        SVGPoint createSVGPoint();
        SVGPath createSVGPath();
        SVGRGBColor createSVGRGBColor(float red, float green, float blue); // throw(SVGException);
        void moveFocus(unsigned short motionType); // throw(DOMException);
        void setFocus(const EventTarget& theObject); // throw(DOMException);
        EventTarget& getCurrentFocusedObject();
    };

    struct SVGRGBColor
    {
        unsigned long red() const;
        void red(unsigned long r);
        unsigned long green() const;
        void green(unsigned long g);
        unsigned long blue() const;
        void blue(unsigned long b);
    };

    struct SVGRect
    {
        float x() const;
        void x(float x);
        float y() const;
        void y(float y);
        float width() const;
        void width(float w);
        float height() const;
        void height(float h);
    };

    struct SVGPoint
    {
        float x() const;
        void x(float x);
        float y() const;
        void y(float y);
        SVGPoint matrixTransform(const SVGMatrix& matrix) const;
    };

    struct SVGPath
    {
        enum : unsigned short
        {
            MOVE_TO = 77,
            LINE_TO = 76,
            CURVE_TO = 67,
            QUAD_TO = 81,
            CLOSE = 90
        };
        
        unsigned long numberOfSegments() const;
        unsigned short getSegment(unsigned long cmdIndex); // throw(DOMException);
        float getSegmentParam(unsigned long cmdIndex, unsigned long paramIndex); // throw(DOMException);
        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void quadTo(float x1, float y1, float x2, float y2);
        void curveTo(float x1, float y1, float x2, float y2, float x3, float y3);
        void close();
    };

    struct SVGMatrix
    {
        float getComponent(unsigned long index) const; // throw(DOMException);
        SVGMatrix& mMultiply(SVGMatrix secondMatrix);
        SVGMatrix& inverse(); // throw(SVGException);
        SVGMatrix& mTranslate(float x, float y);
        SVGMatrix& mScale(float scaleFactor);
        SVGMatrix& mRotate(float angle);
    };

    struct SVGVisualMediaElement : SVGLocatableElement, SVGTimedElement
    {
    };

    struct SVGTimer : events::EventTarget
    {
       long delay() const;
       void delay(long delay);
       long repeatInterval() const;
       void repeatInterval(long repeat);
       bool running() const;
       void start();
       void stop();
    };

    struct AsyncURLStatus
    {
        const bool success;
        const boost::optional<DOMString> contentType;
        const boost::optional<DOMString> content;
    };

    struct AsyncStatusCallback
    {
        virtual void operationComplete(const AsyncURLStatus& status) =0;
        virtual ~AsyncStatusCallback();
    };

    struct SVGGlobal
    {
       SVGTimer createTimer(long initialInterval, long repeatInterval);
       void getURL(const DOMString& iri, std::shared_ptr<AsyncStatusCallback> callback);
       void postURL(const DOMString& iri, const DOMString& data, std::shared_ptr<AsyncStatusCallback> callback, const DOMString& type, const DOMString& encoding);
       boost::optional<Node> parseXML(const DOMString& data, Document contextDoc);
    };

};

#endif /* SVG_H_ */
