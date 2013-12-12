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

namespace experimental
{

/*
Restored from history for alternate purpose.

Will form the basis of the C++ DOM model (and in time the js api)
*/

namespace dom
{
    struct node_t;
    struct element_t;
    struct document_t;

    using node = std::shared_ptr<node_t>;
    using element = std::shared_ptr<element_t>;
    using document = std::shared_ptr<document_t>;

    struct error : std::runtime_error
    {
        enum ErrorCode
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
        } code;
        explicit error(ErrorCode code);
    };

    struct QName
    {
        std::string ns;
        std::string local;
    };

    struct node_t : std::enable_shared_from_this<node_t>
    {
        QName name;
        document doc;
        node parent;
        std::vector<node> children;
        
        std::string textContent() const;
        void textContent(const std::string& context);
        node appendChild(node newChild); // throw(DOMException);
        node insertBefore(node newChild, node refChild); // throw(DOMException);
        node removeChild(node oldChild); // throw(DOMException);
        virtual node cloneNode(bool deep) =0;
        
        virtual ~node_t();
    };

    struct ElementTraversal
    {
        virtual element firstElementChild() const =0;
        virtual element lastElementChild() const =0;
        virtual element nextElementSibling() const =0;
        virtual element previousElementSibling() const =0;
        virtual unsigned long childElementCount() const =0;
    };

    struct element_t : node_t, ElementTraversal
    {
        virtual std::string getAttribute(const QName& name) =0; // throw(DOMException);  
        virtual std::string getAttribute(const std::string& name) =0;
        virtual void setAttribute(const QName& name, const std::string& value) =0; // throw(DOMException);
        virtual void setAttribute(const std::string& name, const std::string& value) =0; // throw(DOMException);
    };

    struct document_t : node_t
    {
        element createElementNS(const boost::optional<std::string>& namespaceURI, const std::string& qualifiedName); // throw(DOMException);
        element documentElement() const;
        element getElementById(const std::string& elementId);
    };

    struct Location
    {
        void assign(const std::string& iri);
        void reload();
    };

    struct Window
    {
        boost::optional<Window> parent() const;
        Location location() const;
    };

}

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

}

namespace events
{
    typedef dom::error error;
    typedef dom::document document;
    typedef dom::element element;
    struct EventTarget;
    struct EventListener;
    struct Event;    

    struct EventTarget
    {
        void addEventListener(const std::string& type, std::shared_ptr<EventListener> listener, bool useCapture);
        void removeEventListener(const std::string& type, std::shared_ptr<EventListener> listener, bool useCapture);
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
        std::string type() const;
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
        long screenX;
        long screenY;
        long clientX;
        long clientY;
        unsigned short button;
    };

    struct MouseWheelEvent : MouseEvent
    {
        long wheelDelta;
    };

    struct TextEvent : UIEvent
    {
        std::string data;
    };

    struct KeyboardEvent : UIEvent
    {
        std::string keyIdentifier;
    };

    struct ProgressEvent : Event
    {
        bool lengthComputable;
        unsigned long loaded;
        unsigned long total;
    };

}

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
        long detail;
    };

}

namespace svg
{
    typedef dom::error error;
    typedef dom::document document;
    typedef dom::element element;
    typedef dom::node node;
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

    struct SVGDocument : dom::document_t, EventTarget
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
        std::string getTrait(const std::string& name); // throw(DOMException);
        std::string getTraitNS(const std::string& namespaceURI, const std::string& name); // throw(DOMException);
        float getFloatTrait(const std::string& name); // throw(DOMException);
        std::vector<float> getFloatListTrait(const std::string& name); // throw(DOMException);
        SVGMatrix getMatrixTrait(const std::string& name); // throw(DOMException);
        boost::optional<SVGRect> getRectTrait(const std::string& name); // throw(DOMException);
        SVGPath getPathTrait(const std::string& name); // throw(DOMException);
        boost::optional<SVGRGBColor> getRGBColorTrait(const std::string& name); // throw(DOMException);
        std::string getPresentationTrait(const std::string& name); // throw(DOMException);
        std::string getPresentationTraitNS(const std::string& namespaceURI, const std::string& name); // throw(DOMException);
        float getFloatPresentationTrait(const std::string& name); // throw(DOMException);
        std::vector<float> getFloatListPresentationTrait(const std::string& name); // throw(DOMException);
        SVGMatrix getMatrixPresentationTrait(const std::string& name); // throw(DOMException);
        boost::optional<SVGRect> getRectPresentationTrait(const std::string& name); // throw(DOMException);
        SVGPath getPathPresentationTrait(const std::string& name); // throw(DOMException);
        boost::optional<SVGRGBColor> getRGBColorPresentationTrait(const std::string& name); // throw(DOMException);
        void setTrait(const std::string& name, const std::string& value); // throw(DOMException);
        void setTraitNS(const std::string& namespaceURI, const std::string& name, const std::string& value); // throw(DOMException);
        void setFloatTrait(const std::string& name, float value); // throw(DOMException);
        void setFloatListTrait(const std::string& name, const std::vector<float>& value); // throw(DOMException);
        void setMatrixTrait(const std::string& name, const SVGMatrix& matrix); // throw(DOMException);
        void setRectTrait(const std::string& name, const SVGRect& rect); // throw(DOMException);
        void setPathTrait(const std::string& name, const SVGPath& path); // throw(DOMException);
        void setRGBColorTrait(const std::string& name, const SVGRGBColor& color); // throw(DOMException);
    };

    struct SVGElement : dom::element_t, EventTarget, TraitAccess
    {
        boost::optional<std::string> id() const;
        void id(const std::string& id) const;
    };

    struct SVGLocatableElement : SVGElement, SVGLocatable
    {
    };

    struct SVGUseElement : SVGLocatableElement
    {
    };

    struct SVGElementInstance : EventTarget
    {
        SVGElement* correspondingElement() const;
        SVGUseElement* correspondingUseElement() const;
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
        const boost::optional<std::string> contentType;
        const boost::optional<std::string> content;
    };

    struct AsyncStatusCallback
    {
        virtual void operationComplete(const AsyncURLStatus& status) =0;
        virtual ~AsyncStatusCallback();
    };

    struct SVGGlobal
    {
       SVGTimer createTimer(long initialInterval, long repeatInterval);
       void getURL(const std::string& iri, std::shared_ptr<AsyncStatusCallback> callback);
       void postURL(const std::string& iri, const std::string& data, std::shared_ptr<AsyncStatusCallback> callback, const std::string& type, const std::string& encoding);
       node parseXML(const std::string& data, document contextDoc);
    };

}

}

#endif /* SVG_H_ */
