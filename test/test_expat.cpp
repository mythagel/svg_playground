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

#include "dom/qualified_name.h"
#include "dom/node.h"
#include "dom/element.h"
#include "dom/character.h"
#include "dom/basic_element.h"

#include "attr.h"

namespace network
{
struct uri
{
};

std::ostream& operator<<(std::ostream& os, const network::uri&)
{
    return os;
}
std::istream& operator>>(std::istream& is, network::uri&)
{
    return is;
}

}

namespace svg
{
namespace attr
{

struct bidi_t
{
    boost::optional<types::bidi::direction> direction;
    boost::optional<types::bidi::unicode_bidi> unicode_bidi;
};

struct media_t;
struct properties_t
{
    std::unique_ptr<bidi_t> bidi;

    enum class display_align_t
    {
        _auto,
        before,
        center,
        after,
        inherit
    };
    boost::optional<display_align_t> display_align;

    enum class line_increment_enum_t
    {
        _auto,
        inherit
    };
    using line_increment_t = boost::variant<line_increment_enum_t, float>;
    boost::optional<line_increment_t> line_increment;

    enum class stop_colour_enum_t
    {
        inherit
    };
    using stop_colour_t = boost::variant<stop_colour_enum_t, svg::types::colour>;
    boost::optional<stop_colour_t> stop_colour;

    enum class stop_opacity_enum_t
    {
        inherit
    };
    using stop_opacity_t = boost::variant<stop_opacity_enum_t, float>;
    boost::optional<stop_opacity_t> stop_opacity;

    std::unique_ptr<attr::media_t> media;

    enum class fill_opacity_enum_t
    {
        inherit
    };
    using fill_opacity_t = boost::variant<fill_opacity_enum_t, float>;
    boost::optional<fill_opacity_t> fill_opacity;

    enum class stroke_opacity_enum_t
    {
        inherit
    };
    using stroke_opacity_t = boost::variant<stroke_opacity_enum_t, float>;
    boost::optional<stroke_opacity_t> stroke_opacity;

    enum class paint_enum_t
    {
        none,
        currentColor,
        inherit
    };
    enum class system_paint_t
    {
        ActiveBorder,
        ActiveCaption,
        AppWorkspace,
        Background,
        ButtonFace,
        ButtonHighlight,
        ButtonShadow,
        ButtonText,
        CaptionText,
        GrayText,
        Highlight,
        HighlightText,
        InactiveBorder,
        InactiveCaption,
        InactiveCaptionText,
        InfoBackground,
        InfoText,
        Menu,
        MenuText,
        Scrollbar,
        ThreeDDarkShadow,
        ThreeDFace,
        ThreeDHighlight,
        ThreeDLightShadow,
        ThreeDShadow,
        Window,
        WindowFrame,
        WindowText
    };

    using paint_t = boost::variant<paint_enum_t, svg::types::colour, network::uri/*<FuncIRI> [ none | currentColor | <color>]*/, system_paint_t>;

    boost::optional<paint_t> fill;

    enum class fill_rule_t
    {
        inherit,
        nonzero,
        evenodd
    };
    boost::optional<fill_rule_t> fill_rule;

    boost::optional<paint_t> stroke;

    // TODO listof<T> as T (comma-wsp T)*
};

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

