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

namespace dom
{
    typedef std::u16string DOMString;
    struct Node;
    struct Element;
    struct Document;

    struct DOMException : std::runtime_error
    {
        explicit DOMException(unsigned short code)
         : code(code), std::runtime_error()
        {
        }
        unsigned short code;
    };

    enum : unsigned short
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

    struct Node
    {
        DOMString namespaceURI() const;
        DOMString localName() const;
        Node parentNode() const;
        Document ownerDocument() const;
        DOMString textContent() const;
        void textContent(const DOMString& context);
        Node appendChild(in Node newChild); // throw(DOMException);
        Node insertBefore(in Node newChild, in Node refChild); // throw(DOMException);
        Node removeChild(in Node oldChild); // throw(DOMException);
        Node cloneNode(bool deep);
    };

    struct Element : Node, ElementTraversal
    {
        DOMString getAttributeNS(const DOMString& namespaceURI, const DOMString& localName); // throw(DOMException);  
        void setAttributeNS(const DOMString& namespaceURI, const DOMString& qualifiedName, const DOMString& value); // throw(DOMException);
        DOMString getAttribute(const DOMString& name);
        void setAttribute(const DOMString& name, const DOMString& value); // throw(DOMException);
    };

    struct Document : Node
    {
        Element createElementNS(const DOMString& namespaceURI, const DOMString& qualifiedName); // throw(DOMException);
        Element documentElement() const;
        Element getElementById(const DOMString& elementId);
    };

    struct ElementTraversal 
    {
        Element firstElementChild() const;
        Element lastElementChild() const;
        Element nextElementSibling() const;
        Element previousElementSibling() const;
        unsigned long childElementCount() const;
    };

    struct Location
    {  
        void assign(const DOMString& iri);
        void reload();
    };

    struct Window
    {
        Window parent() const;
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
        AbstractView defaultView() const;
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
        void addEventListener(const DOMString& type, in EventListener listener, bool useCapture);
        void removeEventListener(const DOMString& type, in EventListener listener, bool useCapture);
    };

    struct EventListener
    {
        void handleEvent(in Event evt);
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

    struct MouseEvent : UIEvent
    {        
        long screenX() const;
        long screenY() const;
        long clientX() const;
        long clientY() const;
        unsigned short button() const;
    };

    struct MouseWheelEvent : MouseEvent     
    {        
        long wheelDelta() const;
    };

    struct TextEvent : UIEvent    
    {        
        DOMString data() const;
    };

    struct KeyboardEvent : UIEvent     
    {        
        DOMString keyIdentifier() const;
    };

    struct UIEvent : Event     
    {        
        long detail() const;
    };

    struct ProgressEvent : Event     
    {        
        bool lengthComputable() const;
        unsigned long loaded() const;
        unsigned long total() const;
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
        long detail() const;
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
    struct SVGAnimationElement;
    struct SVGDocument;
    struct SVGGlobal;

    exception SVGException
    {
        unsigned short code;
    };

    const unsigned short SVG_WRONG_TYPE_ERR         = 0;
    const unsigned short SVG_INVALID_VALUE_ERR      = 1;
    const unsigned short SVG_MATRIX_NOT_INVERTABLE  = 2;

    struct SVGDocument : Document, EventTarget 
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
        attribute float currentScale;
        attribute float currentRotate;
        SVGPoint currentTranslate() const;
        SVGRect viewport() const;
        float getCurrentTime();
        void setCurrentTime(float seconds);
        SVGMatrix createSVGMatrixComponents(float a, float b, float c, float d, float e, float f);
        SVGRect createSVGRect();
        SVGPoint createSVGPoint();
        SVGPath createSVGPath();
        SVGRGBColor createSVGRGBColor(float red, float green, float blue) 
		raises(SVGException);
        void moveFocus(unsigned short motionType) 
		raises(DOMException);
        void setFocus(in EventTarget theObject) 
		raises(DOMException);
        EventTarget getCurrentFocusedObject();
    };

    struct SVGRGBColor
    {
        attribute unsigned long red;
        attribute unsigned long green;
        attribute unsigned long blue;
    };

    struct SVGRect
    {
        attribute float x;
        attribute float y;
        attribute float width;
        attribute float height;
    };

    struct SVGPoint
    {
        attribute float x;
        attribute float y;
        SVGPoint matrixTransform(in SVGMatrix matrix);
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
        float getComponent(unsigned long index); // throw(DOMException);
        SVGMatrix mMultiply(in SVGMatrix secondMatrix);
        SVGMatrix inverse(); // throw(SVGException);
        SVGMatrix mTranslate(float x, float y);
        SVGMatrix mScale(float scaleFactor);
        SVGMatrix mRotate(float angle);
    };

    struct SVGLocatable
    { 
        SVGRect   getBBox();
        SVGMatrix getScreenCTM();
        SVGRect   getScreenBBox();
    };

    struct SVGLocatableElement : SVGElement, SVGLocatable
    {
    };

    struct TraitAccess
    {
        DOMString getTrait(const DOMString& name); // throw(DOMException);
        DOMString getTraitNS(const DOMString& namespaceURI, const DOMString& name); // throw(DOMException);
        float getFloatTrait(const DOMString& name); // throw(DOMException);
        std::vector<float> getFloatListTrait(const DOMString& name); // throw(DOMException);
        SVGMatrix getMatrixTrait(const DOMString& name); // throw(DOMException);
        SVGRect getRectTrait(const DOMString& name); // throw(DOMException);
        SVGPath getPathTrait(const DOMString& name); // throw(DOMException);
        SVGRGBColor getRGBColorTrait(const DOMString& name); // throw(DOMException);
        DOMString getPresentationTrait(const DOMString& name); // throw(DOMException);
        DOMString getPresentationTraitNS(const DOMString& namespaceURI, const DOMString& name); // throw(DOMException);
        float getFloatPresentationTrait(const DOMString& name); // throw(DOMException);
        std::vector<float> getFloatListPresentationTrait(const DOMString& name); // throw(DOMException);
        SVGMatrix getMatrixPresentationTrait(const DOMString& name); // throw(DOMException);
        SVGRect getRectPresentationTrait(const DOMString& name); // throw(DOMException);
        SVGPath getPathPresentationTrait(const DOMString& name); // throw(DOMException);
        SVGRGBColor getRGBColorPresentationTrait(const DOMString& name); // throw(DOMException);
        void setTrait(const DOMString& name, const DOMString& value); // throw(DOMException);
        void setTraitNS(const DOMString& namespaceURI, const DOMString& name, const DOMString& value); // throw(DOMException);
        void setFloatTrait(const DOMString& name, float value); // throw(DOMException);
        void setFloatListTrait(const DOMString& name, const std::vector<float>& value); // throw(DOMException);
        void setMatrixTrait(const DOMString& name, in SVGMatrix matrix); // throw(DOMException);
        void setRectTrait(const DOMString& name, in SVGRect rect); // throw(DOMException);
        void setPathTrait(const DOMString& name, in SVGPath path); // throw(DOMException);
        void setRGBColorTrait(const DOMString& name, in SVGRGBColor color); // throw(DOMException);
    };

    struct SVGElement : Element, EventTarget, TraitAccess
    {
        attribute DOMString id;
    };

    struct SVGTimedElement : SVGElement, smil::ElementTimeControl
    {
        void pauseElement();
        void resumeElement();
        bool isPaused() const;
    };

    struct SVGAnimationElement : SVGTimedElement
    {
    };

    struct SVGVisualMediaElement : SVGLocatableElement, SVGTimedElement 
    {
    };

    struct SVGTimer : events::EventTarget
    {
       attribute long delay;
       attribute long repeatInterval;
       bool running() const;
       void start();
       void stop();
    };

    struct SVGGlobal
    {
       SVGTimer createTimer(long initialInterval, long repeatInterval);
       void getURL(const DOMString& iri, in AsyncStatusCallback callback);
       void postURL(const DOMString& iri, const DOMString& data, in AsyncStatusCallback callback, const DOMString& type, const DOMString& encoding);
       Node parseXML(const DOMString& data, in Document contextDoc);
    };

    struct AsyncStatusCallback 
    {
        void operationComplete(in AsyncURLStatus status);
    };

    struct AsyncURLStatus 
    {
        bool success() const;
        DOMString contentType() const;
        DOMString content() const;
    };

    struct EventListenerInitializer2
    {
        void initializeEventListeners(in Element scriptElement);
        EventListener createEventListener(in Element handlerElement);
    };

};

#endif /* SVG_H_ */
