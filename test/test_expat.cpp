#include "expat.hh"
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <stack>

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <utility>
#include <stdexcept>
#include <sstream>
#include "make_unique.h"

#include "types/colour.h"
#include "types/stringlist.h"
#include "types/core.h"
#include "types/media.h"
#include "types/bidi.h"
#include "types/flowable_text.h"
#include "types/gradient.h"
#include "types/opacity.h"
#include "types/paint.h"
#include "types/solidcolour.h"
#include "types/text.h"
#include "types/vectoreffects.h"
#include "types/focus.h"

#include "dom/qualified_name.h"
#include "dom/node.h"
#include "dom/element.h"
#include "dom/character.h"
#include "dom/basic_element.h"

#include "attr.h"
#include "network/uri.hpp"

namespace svg
{
namespace attr
{

struct bidi_t
{
    boost::optional<types::bidi::direction> direction;
    boost::optional<types::bidi::unicode_bidi> unicode_bidi;
};

void map_attributes(bidi_t& attr, attribute_map_t& attrs)
{
    attrs.emplace("direction", make_attr(attr.direction));
    attrs.emplace("unicode-bidi", make_attr(attr.unicode_bidi));
}

struct media_t
{
    boost::optional<types::media::display> display;
    boost::optional<types::media::visibility> visibility;
    boost::optional<types::media::image_rendering> image_rendering;
    boost::optional<types::media::pointer_events> pointer_events;
    boost::optional<types::media::shape_rendering> shape_rendering;
    boost::optional<types::media::text_rendering> text_rendering;
    boost::optional<types::media::buffered_rendering> buffered_rendering;
    boost::optional<types::media::audio_level> audio_level;
    boost::optional<types::media::viewport_fill> viewport_fill;
    boost::optional<types::media::viewport_fill_opacity> viewport_fill_opacity;
};

void map_attributes(media_t& attr, attribute_map_t& attrs)
{
    attrs.emplace("display", make_attr(attr.display));
    attrs.emplace("visibility", make_attr(attr.visibility));
    attrs.emplace("image-rendering", make_attr(attr.image_rendering));
    attrs.emplace("pointer-events", make_attr(attr.pointer_events));
    attrs.emplace("shape-rendering", make_attr(attr.shape_rendering));
    attrs.emplace("text-rendering", make_attr(attr.text_rendering));
    attrs.emplace("buffered-rendering", make_attr(attr.buffered_rendering));
    attrs.emplace("audio-level", make_attr(attr.audio_level));
    attrs.emplace("viewport-fill", make_attr(attr.viewport_fill));
    attrs.emplace("viewport-fill-opacity", make_attr(attr.viewport_fill_opacity));
}

struct properties_t
{
    std::unique_ptr<bidi_t> bidi;

    boost::optional<types::flowable_text::display_align> display_align;
    boost::optional<types::flowable_text::line_increment> line_increment;

    boost::optional<types::gradient::stop_colour> stop_colour;
    boost::optional<types::gradient::stop_opacity> stop_opacity;

    std::unique_ptr<attr::media_t> media;

    boost::optional<types::opacity::fill_opacity> fill_opacity;
    boost::optional<types::opacity::stroke_opacity> stroke_opacity;

    boost::optional<types::paint::paint> fill;
    boost::optional<types::paint::fill_rule> fill_rule;
    boost::optional<types::paint::paint> stroke;
    // TODO stroke-dasharray
    boost::optional<types::paint::stroke_dashoffset> stroke_dashoffset;
    boost::optional<types::paint::stroke_linecap> stroke_linecap;
    boost::optional<types::paint::stroke_linejoin> stroke_linejoin;
    boost::optional<types::paint::stroke_miterlimit> stroke_miterlimit;
    boost::optional<types::paint::stroke_width> stroke_width;
    boost::optional<types::paint::color> color;
    boost::optional<types::paint::color_rendering> color_rendering;

    boost::optional<types::solidcolour::solid_color> solid_color;
    boost::optional<types::solidcolour::solid_opacity> solid_opacity;

    boost::optional<types::text::font_family> font_family;
    boost::optional<types::text::font_size> font_size;
    boost::optional<types::text::font_style> font_style;
    boost::optional<types::text::font_variant> font_variant;
    boost::optional<types::text::font_weight> font_weight;
    boost::optional<types::text::text_anchor> text_anchor;
    boost::optional<types::text::text_align> text_align;

    boost::optional<types::vectoreffects::vector_effect> vector_effect;
};

void map_attributes(properties_t& attr, attribute_map_t& attrs)
{
    if(attr.bidi)
        map_attributes(*attr.bidi, attrs);

    attrs.emplace("display-align", make_attr(attr.display_align));
    attrs.emplace("line-increment", make_attr(attr.line_increment));
    attrs.emplace("stop-colour", make_attr(attr.stop_colour));
    attrs.emplace("stop-opacity", make_attr(attr.stop_opacity));

    if(attr.media)
        map_attributes(*attr.media, attrs);

    attrs.emplace("fill-opacity", make_attr(attr.fill_opacity));
    attrs.emplace("stroke-opacity", make_attr(attr.stroke_opacity));
    attrs.emplace("fill", make_attr(attr.fill));
    attrs.emplace("fill-rule", make_attr(attr.fill_rule));
    attrs.emplace("stroke", make_attr(attr.stroke));
    attrs.emplace("stroke-dashoffset", make_attr(attr.stroke_dashoffset));
    attrs.emplace("stroke-linecap", make_attr(attr.stroke_linecap));
    attrs.emplace("stroke-linejoin", make_attr(attr.stroke_linejoin));
    attrs.emplace("stroke-miterlimit", make_attr(attr.stroke_miterlimit));
    attrs.emplace("stroke-width", make_attr(attr.stroke_width));
    attrs.emplace("color", make_attr(attr.color));
    attrs.emplace("color-rendering", make_attr(attr.color_rendering));
    attrs.emplace("solid-color", make_attr(attr.solid_color));
    attrs.emplace("solid-opacity", make_attr(attr.solid_opacity));
    attrs.emplace("font-family", make_attr(attr.font_family));
    attrs.emplace("font-size", make_attr(attr.font_size));
    attrs.emplace("font-style", make_attr(attr.font_style));
    attrs.emplace("font-variant", make_attr(attr.font_variant));
    attrs.emplace("font-weight", make_attr(attr.font_weight));
    attrs.emplace("text-anchor", make_attr(attr.text_anchor));
    attrs.emplace("text-align", make_attr(attr.text_align));
    attrs.emplace("vector-effect", make_attr(attr.vector_effect));
}

struct core_common_t
{
    boost::optional<std::string> id;
    boost::optional<network::uri> base;
    boost::optional<std::string> lang;
    boost::optional<std::string> _class;
    boost::optional<types::stringlist_t> role;
    boost::optional<types::stringlist_t> rel;
    boost::optional<types::stringlist_t> rev;
    boost::optional<types::stringlist_t> _typeof;
    boost::optional<std::string> content;
    boost::optional<std::string> datatype;
    boost::optional<std::string> resource;
    boost::optional<types::stringlist_t> about;
    boost::optional<types::stringlist_t> property;
};

void map_attributes(core_common_t& attr, attribute_map_t& attrs)
{
    attrs.emplace("id", make_attr(attr.id));
    attrs.emplace("base", make_attr(attr.base));
    attrs.emplace("lang", make_attr(attr.lang));
    attrs.emplace("class", make_attr(attr._class));
    attrs.emplace("role", make_attr(attr.role));
    attrs.emplace("rel", make_attr(attr.rel));
    attrs.emplace("rev", make_attr(attr.rev));
    attrs.emplace("typeof", make_attr(attr._typeof));
    attrs.emplace("content", make_attr(attr.content));
    attrs.emplace("datatype", make_attr(attr.datatype));
    attrs.emplace("resource", make_attr(attr.resource));
    attrs.emplace("about", make_attr(attr.about));
    attrs.emplace("property", make_attr(attr.property));
}

struct core_t
{
    core_common_t common;

    boost::optional<types::core::space> space;
};

void map_attributes(core_t& attr, attribute_map_t& attrs)
{
    map_attributes(attr.common, attrs);
    attrs.emplace("space", make_attr(attr.space));
}

struct conditional_t
{
    boost::optional<std::vector<network::uri>> requiredFeatures;
    boost::optional<std::vector<network::uri>> requiredExtensions;
    boost::optional<std::vector<std::string>> requiredFormats;
    boost::optional<std::vector<std::string>> requiredFonts;
    boost::optional<std::vector<std::string>> systemLanguage;
};

void map_attributes(conditional_t& attr, attribute_map_t& attrs)
{
//    attrs.emplace("requiredFeatures", make_attr(attr.requiredFeatures));
//    attrs.emplace("requiredExtensions", make_attr(attr.requiredExtensions));
//    attrs.emplace("requiredFormats", make_attr(attr.requiredFormats));
//    attrs.emplace("requiredFonts", make_attr(attr.requiredFonts));
//    attrs.emplace("systemLanguage", make_attr(attr.systemLanguage));
}

}

dom::qualified_name SVG = {"svg", "http://www.w3.org/2000/svg"};
dom::qualified_name DESC = {"desc", "http://www.w3.org/2000/svg"};

struct svg_element_t : dom::basic_element_t
{
    svg_element_t()
     : basic_element_t(SVG)
    {
    }

    virtual dom::node clone(bool deep) override
    {
        auto dup = std::make_shared<svg_element_t>(*this);
        dup->parent.reset();

        if(deep)
        {
            for(auto& child : dup->children)
                child = child->clone(deep);
        }
        else
        {
            dup->children.clear();
            return dup;
        }

        return dup;
    }

    virtual ~svg_element_t()
    {
    }
};

struct desc_element_t : dom::element_t
{
    std::string description;

    std::unique_ptr<attr::core_t> core;
    std::unique_ptr<attr::conditional_t> conditional;
    std::unique_ptr<attr::media_t> media;

    std::vector<std::unique_ptr<attr::typed_attribute>> attributes;

    desc_element_t()
    {
    }

    desc_element_t(const desc_element_t& o)
     : description(o.description)/*, todo copy ptrs*/
    {
    }

    desc_element_t(desc_element_t&& o) = default;

    virtual dom::qualified_name name() const override
    {
        return DESC;
    }

    virtual dom::node append(const dom::node& child) override
    {
        if(std::dynamic_pointer_cast<dom::character_t>(child))
            return element_t::append(child);
        throw std::runtime_error("desc node cannot have non-text children.");
    }

    virtual dom::node insert(const dom::node& child, const dom::node& ref) override
    {
        if(std::dynamic_pointer_cast<dom::character_t>(child))
            return element_t::insert(child, ref);
        throw std::runtime_error("desc node cannot have non-text children.");
    }

    virtual dom::node erase(const dom::node& child) override
    {
        return element_t::erase(child);
    }

    virtual dom::node clone(bool deep) override
    {
        auto dup = std::make_shared<desc_element_t>(*this);
        dup->parent.reset();

        if(deep)
        {
            for(auto& child : dup->children)
                child = child->clone(deep);
        }
        else
        {
            dup->children.clear();
            return dup;
        }

        return dup;
    }

    virtual boost::optional<std::string> get_attribute(const dom::qualified_name& name) const override
    {
        /* need a good way to map variable attributes to access by name.
         * something that associates the (potential) value with a name
         * so it can be get and set. */
        return {};
    }
    virtual void set_attribute(const dom::qualified_name& name, const boost::optional<std::string>& value) override
    {

    }

    virtual ~desc_element_t()
    {
    }
};

}

dom::element default_construct_element(const dom::qualified_name& name)
{
    if(name == svg::SVG)
        return std::make_shared<svg::svg_element_t>();
    else if(name == svg::DESC)
        return std::make_shared<svg::desc_element_t>();
    return std::make_shared<dom::basic_element_t>(name);
}

struct parser : expat::parser<parser>
{
    std::stack<dom::node> stack;
    dom::node root;
    std::function<dom::element(const dom::qualified_name&)> construct_element;

    void startNamespace(const std::string&, const std::string&)
	{
	}
    void endNamespace(const std::string&)
	{
	}

	void startElement(const expat::qname& name, const std::vector<std::pair<expat::qname, std::string>>& attributes)
	{
        // based on the qualified element name could construct different subclasses of element_t
        dom::element element = construct_element({ name.local, name.prefix });

	    for(auto& attr : attributes)
            element->set_attribute({ attr.first.local, attr.first.prefix }, attr.second);

        stack.push(element);
	}
    void endElement(const expat::qname&)
	{
        auto node = stack.top();
        stack.pop();

        if(!stack.empty())
            stack.top()->append(node);
        else
            root = node;
	}

	void charData(const std::string& cdata)
	{
        dom::node node = std::make_shared<dom::character_t>(cdata);
        if(!stack.empty())
            stack.top()->append(node);
    }
    void CommentHandler(const std::string&)
	{
	}
};

void write(std::ostream& os, const dom::node& node, int level = 0)
{
    auto indent = std::string(level, ' ');

    if(auto element = std::dynamic_pointer_cast<dom::element_t>(node))
    {
        os << indent << element->name().ns << ":" << element->name().local << "\n";
        // no interface to iterate over attributes (and none needed)...
    }
    else if(auto cdata = std::dynamic_pointer_cast<dom::character_t>(node))
    {
        os << indent << "'" << cdata->data << "'\n";
    }

    for(auto& child : node->children)
        write(os, child, level+1);
}

std::ostream& operator<<(std::ostream& os, const dom::node& node)
{
    write(os, node);
    return os;
}

int main()
{
    std::ifstream f("x1.svg", std::ios::binary);
    if(!f) throw std::runtime_error("file x1.svg not found.");
    f >> std::noskipws;
    std::string s{std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>()};
    
    parser p;
    p.construct_element = default_construct_element;
    p.Parse(s);

    auto root = p.root;
    std::cout << root;
    return 0;
}

