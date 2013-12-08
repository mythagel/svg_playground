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
 * document.h
 *
 *  Created on: 2013-12-05
 *      Author: nicholas
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include "colour.h"
#include "types.h"
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <array>
#include <cstddef>
#include <sstream>
#include <vector>
#include <map>
#include <functional>

namespace svg
{

namespace graphic_elements
{

struct shape
{
    //shapes: 'circle', 'ellipse', 'line', 'path', 'polygon', 'polyline' and 'rect'
    // fill
    // stroke
};

struct text
{
};

struct media
{
};

}

/*
a node in a document
unlike an xml node that stores data - this node is just an interface
every node has a node parent? and node children*

svg structure is read using expat into these structured node data.
subclasses of node store the actual data.

what are the requirements?!?!?!

attributes need to know their owner so they can know their parent (for inheritable attributes)


e.g.

struct svg : node
{
    type1 field1;
    type2 field2;
    type3 field3;

    T get(const std::string& name);
}


animation elements: 'animate', 'animateColor', 'animateMotion', 'animateTransform' and 'set'
container elements: 'a', 'defs', 'g', 'svg' and 'switch'
descriptive elements: 'desc', 'metadata', and 'title'
graphics elements: 'animation', 'circle', 'ellipse', 'image', 'line', 'path', 'polygon', 'polyline', 'rect', 'text', 'textArea', 'use' and 'video'
graphics referencing elements: 'animation', 'foreignObject', 'image', 'use' and 'video'
media elements: 'animation', 'audio' and 'video'
text content elements: 'text', 'textArea' and 'tspan'
text content block elements: 'text' and 'textArea'
timed elements: 'audio', 'animate', 'animateColor', 'animateMotion', 'animateTransform', 'animation', 'set' and 'video'

*/

struct attribute_tags
{
/*
need to store attribute properties common to all instances of that attribute
svg:inheritable / inherited are independant.
svg:animatable as well.
*/
};

struct attribute
{
    std::string name;
    bool inherit;
protected:
    explicit attribute(const std::string& name, bool inherit = false)
     : name(name), inherit(inherit)
    {
    }
public:

    virtual explicit operator bool() const =0;
    virtual std::string get() const =0;  // can throw if not set.
    virtual void set(const std::string& s) =0; // can throw if invalid format

    virtual ~attribute()
    {
    }
};

struct element
{
    std::string name;
protected:
    std::map<std::string, std::reference_wrapper<attribute>> attributes;
    
    explicit element(const std::string& name)
     : name(name)
    {
    }
    element(const element& o)
     : name(o.name), attributes()
    {
    }
    element& operator=(element o)
    {
        std::swap(name, o.name);
        attributes.clear();
        return *this;
    }
    
    void expose_attribute(attribute& attr)
    {
        attributes.emplace(attr.name, attr);
    }
public:

/*
node has unique named attributes
need to be able to get attribute by name
    can query parent for inherited attributes
    ?get_attribute()
    ?get_inherited_attribute()

attributes are strongly typed
regular functions need fast (direct) access to the types (via member access).
node need to be able to lookup attribute by name.
have a map of names to attribute pointers (pointers to own attribute members)

*/

    attribute& get(const std::string& name)
    {
        auto it = attributes.find(name);
        if(it == end(attributes))
            throw std::runtime_error("unknown attribute");
        return it->second;
    }

    virtual ~element()
    {
    }
};

template <typename T>
struct typed_attribute : attribute
{
    T value;
    
    explicit typed_attribute(const std::string& name, T default_ = {})
     : attribute(name), value{default_}
    {
    }
    
    explicit operator bool() const
    {
        return true;
    }
    const T& operator*() const
    {
        return value;
    }
    T& operator*()
    {
        return value;
    }
    std::string get() const override
    {
        std::stringstream s;
        s << *this;
        return s.str();
    }
    void set(const std::string& ss) override
    {
        std::stringstream s(ss);
        s >> *this;
    }
};

// TODO type tags may be needed in the attribute structures, i.e.
// two datatypes STORED as float values need to be parsed differently
// i.e. 'three' could be parsed and stored as a float value for a different
// datatype.
std::istream& operator>>(std::istream& is, typed_attribute<float>& f)
{
    is >> f.value;
    return is;
}
std::ostream& operator<<(std::ostream& os, const typed_attribute<float>& f)
{
    os << f.value;
    return os;
}
std::istream& operator>>(std::istream& is, typed_attribute<int>& f)
{
    is >> f.value;
    return is;
}
std::ostream& operator<<(std::ostream& os, const typed_attribute<int>& f)
{
    os << f.value;
    return os;
}

template <typename T>
struct optional_typed_attribute : attribute
{
    boost::optional<T> value;
    
    optional_typed_attribute(const std::string& name)
     : attribute(name)
    {
    }
    
    explicit operator bool() const
    {
        return value;
    }
    
    const T& operator*() const
    {
        if(!value) throw std::runtime_error("no value");
        return *value;
    }
    T& operator*()
    {
        if(!value) throw std::runtime_error("no value");
        return *value;
    }
    
    std::string get() const override
    {
        if(!value) throw std::runtime_error("no value");
        std::stringstream s;
        s << *value;
        return s.str();
    }
    void set(const std::string& ss) override
    {
        std::stringstream s(ss);
        T v;
        s >> v;
        value = v;
    }
};

struct line_element : element
{
    typed_attribute<float> x1;
    typed_attribute<float> y1;
    typed_attribute<float> x2;
    typed_attribute<float> y2;

    optional_typed_attribute<int> stroke_width;
    void expose_attributes()
    {
        expose_attribute(x1);
        expose_attribute(y1);
        expose_attribute(x2);
        expose_attribute(x2);
        expose_attribute(stroke_width);
    }

    line_element()
     : element("line"), x1("x1"), y1("y1"), x2("x2"), y2("y2"), stroke_width("stroke_width")
    {
        expose_attributes();
    }
    line_element(const line_element& o)
     : element(o), x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2), stroke_width(o.stroke_width)
    {
        expose_attributes();
    }
    line_element& operator=(line_element o)
    {
        std::swap(x1, o.x1);
        std::swap(y1, o.y1);
        std::swap(x2, o.x2);
        std::swap(y2, o.y2);
        std::swap(stroke_width, o.stroke_width);

        expose_attributes();
        return *this;
    }
    
    virtual ~line_element()
    {
    }
};

namespace bidi
{
enum class direction
{
    ltr,
    rtl
};

enum class unicode_bidi
{
    normal,
    embed,
    bidi_override
};

std::istream& operator>>(std::istream& is, optional_typed_attribute<direction>& f)
{
    std::string tok;
    is >> tok;
    if(tok == "ltr")
        f.value = direction::ltr;
    else if(tok == "rtl")
        f.value = direction::rtl;
    else if(tok == "inherit")
    {
        f.value = boost::none;
        f.inherit = true;
    }
    else
        throw std::runtime_error("invalid value: " + tok);
    return is;
}
std::ostream& operator<<(std::ostream& os, const optional_typed_attribute<direction>& f)
{
    if(f.value)
    {
        switch(*f.value)
        {
            case direction::ltr:
                os << "ltr";
                break;
            case direction::rtl:
                os << "rtl";
                break;
        }
    }
    else if(f.inherit)
        os << "inherit";
// todo how to represent inherit properly.
    return os;
}

}


namespace text
{
enum class display_align
{
    auto_,
    before,
    center,
    after
};

enum class line_increment
{
    auto_,
    // number
};
}

namespace gradient
{

}

namespace media
{

}

namespace paint
{
    struct paint{};
    
    enum class fill_rule
    {
        nonzero,
        evenodd
    };
    
    struct stroke_dasharray{};
    
    enum class stroke_linecap
    {
        butt,
        round,
        square
    };
    
    enum class stroke_linejoin
    {
        miter,
        round,
        bevel
    };
    
    enum class color_rendering
    {
        auto_,
        optimizeSpeed,
        optimizeQuality
    };
}

struct document
{
    // TODO wrappers for optional, default values and inherit.
    bidi::direction direction;
    bidi::unicode_bidi unicode_bidi;
    text::display_align display_align;
    text::line_increment line_increment;

    // inherit
    types::colour stop_colour;
    float stop_opacity;
    
    float audio_level;
    
    float fill_opacity;
    float stroke_opacity;
    
    paint::paint fill;
    paint::fill_rule fill_rule;
    paint::paint stroke;
    paint::stroke_dasharray stroke_dasharray;
    types::length stroke_dashoffset;
    paint::stroke_linecap stroke_linecap;
    paint::stroke_linejoin stroke_linejoin;
    float stroke_miterlimit;
    float stroke_width;
    types::colour colour;
    paint::color_rendering color_rendering;
    
    
    // types for allowable svg attributes
    
};

}

#endif /* DOCUMENT_H_ */
