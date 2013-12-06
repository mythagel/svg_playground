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

template <std::size_t N>
auto make_array(char(&s)[N]) -> std::array<char, N>
{
    return std::array<char, N>(std::begin(s), std::end(s));
}

namespace svg
{

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

struct attribute
{
    std::string name;
protected:
    explicit attribute(const std::string& name)
     : name(name)
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
    
    void add_attribute(attribute& attr)
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
    std::string get() const
    {
        std::stringstream s;
        s << value;
        return s.str();
    }
    void set(const std::string& ss)
    {
        std::stringstream s(ss);
        s >> value;
    }
};

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
    
    std::string get() const
    {
        if(!value) throw std::runtime_error("no value");
        std::stringstream s;
        s << *value;
        return s.str();
    }
    void set(const std::string& ss)
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
    void add_attributes()
    {
        add_attribute(x1);
        add_attribute(y1);
        add_attribute(x2);
        add_attribute(x2);
        add_attribute(stroke_width);
    }

    line_element()
     : element("line"), x1("x1"), y1("y1"), x2("x2"), y2("y2"), stroke_width("stroke_width")
    {
        add_attributes();
    }
    line_element(const line_element& o)
     : element(o), x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2), stroke_width(o.stroke_width)
    {
        add_attributes();
    }
    line_element& operator=(line_element o)
    {
        std::swap(x1, o.x1);
        std::swap(y1, o.y1);
        std::swap(x2, o.x2);
        std::swap(y2, o.y2);
        std::swap(stroke_width, o.stroke_width);

        add_attributes();
        return *this;
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
