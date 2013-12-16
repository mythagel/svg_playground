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
#include "colour.h"
#include "make_unique.h"

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

namespace dom
{

struct node_t;
using node = std::shared_ptr<node_t>;

struct qualified_name
{
    std::string ns;
    std::string local;
    qualified_name()
    {
    }
    qualified_name(const std::string& local, const std::string& ns = {})
     : ns(ns), local(local)
    {
    }

    bool operator==(const qualified_name& name) const
    {
        return std::tie(ns, local) == std::tie(name.ns, name.local);
    }
    bool operator!=(const qualified_name& name) const
    {
        return std::tie(ns, local) != std::tie(name.ns, name.local);
    }
    bool operator<(const qualified_name& name) const
    {
        return std::tie(ns, local) < std::tie(name.ns, name.local);
    }
};

struct node_t : std::enable_shared_from_this<node_t>
{
    node parent;
    std::vector<node> children;

    virtual node append(const node& child)
    {
        auto it = std::find(begin(children), end(children), child);
        if(it != end(children))
            children.erase(it);

        child->parent = shared_from_this();
        children.push_back(child);
        return child;
    }

    virtual node insert(const node& child, const node& ref)
    {
        auto it = std::find(begin(children), end(children), ref);

        child->parent = shared_from_this();
        children.insert(it, child);
        return child;
    }

    virtual node erase(const node& child)
    {
        auto it = std::find(begin(children), end(children), child);
        if(it != end(children))
            children.erase(it);

        child->parent.reset();
        return child;
    }

    virtual node clone(bool deep) =0;

    virtual ~node_t()
    {
    }
};

/*
Node types
element
character
cdata

*/

struct element_t;
using element = std::shared_ptr<element_t>;

struct element_t : node_t
{
    element_t()
    {
    }

    virtual qualified_name name() const =0;
    virtual boost::optional<std::string> get_attribute(const qualified_name& name) const =0;
    virtual void set_attribute(const qualified_name& name, const boost::optional<std::string>& value) =0;

    virtual ~element_t()
    {
    }
};

struct character_t;
using character = std::shared_ptr<character_t>;

struct character_t : node_t
{
    std::string data;

    character_t(const std::string& data)
     : data(data)
    {
    }

    virtual node append(const node&) override
    {
        throw std::runtime_error("character node cannot have children.");
    }

    virtual node insert(const node&, const node&) override
    {
        throw std::runtime_error("character node cannot have children.");
    }

    virtual node erase(const node&) override
    {
        throw std::runtime_error("character node cannot have children.");
    }

    virtual node clone(bool) override
    {
        auto dup = std::make_shared<character_t>(*this);
        dup->parent.reset();
        return dup;
    }

    virtual ~character_t()
    {
    }
};

struct basic_element_t : element_t
{
    qualified_name element_name;
    std::map<qualified_name, std::string> attributes;

    basic_element_t(const qualified_name& name)
     : element_name(name)
    {
    }

    virtual qualified_name name() const override
    {
        return element_name;
    }

    virtual boost::optional<std::string> get_attribute(const qualified_name& name) const override
    {
        auto it = attributes.find(name);
        if(it != end(attributes))
            return boost::make_optional(it->second);
        return {};
    }

    virtual void set_attribute(const qualified_name& name, const boost::optional<std::string>& value) override
    {
        if(value)
            attributes[name] = *value;
        else
            attributes.erase(name);
    }

    virtual node clone(bool deep) override
    {
        auto dup = std::make_shared<basic_element_t>(*this);
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

    virtual ~basic_element_t()
    {
    }
};

}

namespace svg
{
namespace attr
{

/* Generic string access to typed (member variable)
 * attributes */
struct typed_attribute
{
    virtual boost::optional<std::string> get() const = 0;
    virtual void set(const boost::optional<std::string>& value) =0;
    virtual ~typed_attribute()
    {
    }
};

/* Typed attribute whose storage is a reference to an
 * optional attribute elsewhere. */
template <typename T>
struct optional_typed_attribute_ref : typed_attribute
{
    std::reference_wrapper<boost::optional<T>> value;

    optional_typed_attribute_ref(boost::optional<T>& value)
     : value(std::ref(value))
    {
    }

    virtual boost::optional<std::string> get() const override
    {
        auto& v = value.get();
        if(!v)
            return boost::none;
        std::ostringstream s;
        s << *v;
        return { s.str() };
    }
    virtual void set(const boost::optional<std::string>& new_value) override
    {
        auto& v = value.get();
        if(new_value)
        {
            std::istringstream s(*new_value);
            if(!v)
                v = boost::make_optional(T());
            s >> *v;
        }
        else
        {
            v = boost::none;
        }
    }

    virtual ~optional_typed_attribute_ref()
    {
    }
};

template <>
struct optional_typed_attribute_ref<std::string> : typed_attribute
{
    std::reference_wrapper<boost::optional<std::string>> value;

    optional_typed_attribute_ref(boost::optional<std::string>& value)
     : value(std::ref(value))
    {
    }

    virtual boost::optional<std::string> get() const override
    {
        return value;
    }
    virtual void set(const boost::optional<std::string>& new_value) override
    {
        value.get() = new_value;
    }

    virtual ~optional_typed_attribute_ref()
    {
    }
};

template<typename T>
auto make_ref(boost::optional<T>& value) -> std::unique_ptr<optional_typed_attribute_ref<T>>
{
    return make_unique<optional_typed_attribute_ref<T>>(value);
}

using attribute_map_t = std::map<std::string, std::unique_ptr<typed_attribute>>;

struct stringlist_t
{
    std::vector<std::string> data;
};

std::ostream& operator<<(std::ostream& os, const stringlist_t& list)
{
    std::copy(begin(list.data), end(list.data), std::ostream_iterator<std::string>(os, " "));
    return os;
}
std::istream& operator>>(std::istream& is, stringlist_t& list)
{
    list.data = std::vector<std::string>(std::istream_iterator<std::string>{is}, std::istream_iterator<std::string>{});
    return is;
}

struct bidi_t
{
    enum class direction_t
    {
        ltr,
        rtl,
        inherit
    };
    boost::optional<direction_t> direction;

    enum class unicode_bidi_t
    {
        normal,
        embed,
        bidi_override,
        inherit
    };
    boost::optional<unicode_bidi_t> unicode_bidi;
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
    boost::optional<stringlist_t> role;
    boost::optional<stringlist_t> rel;
    boost::optional<stringlist_t> rev;
    boost::optional<stringlist_t> _typeof;
    boost::optional<std::string> content;
    boost::optional<std::string> datatype;
    boost::optional<std::string> resource;
    boost::optional<stringlist_t> about;
    boost::optional<stringlist_t> property;
};

void map_attributes(core_common_t& attr, attribute_map_t& attrs)
{
    attrs.emplace("id", make_ref(attr.id));
    attrs.emplace("base", make_ref(attr.base));
    attrs.emplace("lang", make_ref(attr.lang));
    attrs.emplace("class", make_ref(attr._class));
    attrs.emplace("role", make_ref(attr.role));
    attrs.emplace("rel", make_ref(attr.rel));
    attrs.emplace("rev", make_ref(attr.rev));
    attrs.emplace("typeof", make_ref(attr._typeof));
    attrs.emplace("content", make_ref(attr.content));
    attrs.emplace("datatype", make_ref(attr.datatype));
    attrs.emplace("resource", make_ref(attr.resource));
    attrs.emplace("about", make_ref(attr.about));
    attrs.emplace("property", make_ref(attr.property));
}

struct core_t
{
    core_common_t common;

    enum class space_t
    {
        _default,
        preserve
    };

    boost::optional<space_t> space;
};

std::ostream& operator<<(std::ostream& os, core_t::space_t e)
{
    switch(e)
    {
        case core_t::space_t::_default:
            os << "default";
            break;
        case core_t::space_t::preserve:
            os << "preserve";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, core_t::space_t& e)
{
    std::string tok;
    is >> tok;
    if(tok == "default")
        e = core_t::space_t::_default;
    else if(tok == "preserve")
        e = core_t::space_t::preserve;
    else
        throw std::invalid_argument("unrecognised value for space: " + tok);
    return is;
}

void map_attributes(core_t& attr, attribute_map_t& attrs)
{
    map_attributes(attr.common, attrs);
    attrs.emplace("space", make_ref(attr.space));
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
//    attrs.emplace("requiredFeatures", make_ref(attr.requiredFeatures));
//    attrs.emplace("requiredExtensions", make_ref(attr.requiredExtensions));
//    attrs.emplace("requiredFormats", make_ref(attr.requiredFormats));
//    attrs.emplace("requiredFonts", make_ref(attr.requiredFonts));
//    attrs.emplace("systemLanguage", make_ref(attr.systemLanguage));
}

struct media_t
{
    enum class display_t
    {
        _inline,
        block,
        list_item,
        run_in,
        compact,
        marker,
        table,
        inline_table,
        table_row_group,
        table_header_group,
        table_footer_group,
        table_row,
        table_column_group,
        table_column,
        table_cell,
        table_caption,
        none,
        inherit
    };
    boost::optional<display_t> display;

    enum class visibility_t
    {
        visible,
        hidden,
        inherit
    };
    boost::optional<visibility_t> visibility;

    enum class image_rendering_t
    {
        _auto,
        optimizeSpeed,
        optimizeQuality,
        inherit
    };
    boost::optional<image_rendering_t> image_rendering;

    enum class pointer_events_t
    {
        visiblePainted,
        visibleFill,
        visibleStroke,
        visible,
        painted,
        fill,
        stroke,
        all,
        none,
        inherit
    };
    boost::optional<pointer_events_t> pointer_events;

    enum class shape_rendering_t
    {
        _auto,
        optimizeSpeed,
        crispEdges,
        geometricPrecision,
        inherit
    };
    boost::optional<shape_rendering_t> shape_rendering;

    enum class text_rendering_t
    {
        _auto,
        optimizeSpeed,
        optimizeLegibility,
        geometricPrecision,
        inherit
    };
    boost::optional<text_rendering_t> text_rendering;

    enum class buffered_rendering_t
    {
        _auto,
        dynamic,
        _static,
        inherit
    };
    boost::optional<buffered_rendering_t> buffered_rendering;

    enum class audio_level_enum_t
    {
        inherit
    };
    using audio_level_t = boost::variant<audio_level_enum_t, float>;
    boost::optional<audio_level_t> audio_level;

    enum class viewport_fill_enum_t
    {
        inherit,
        none
    };
    using viewport_fill_t = boost::variant<viewport_fill_enum_t, svg::types::colour>;
    boost::optional<viewport_fill_t> viewport_fill;

    enum class viewport_fill_opacity_enum_t
    {
        inherit
    };
    using viewport_fill_opacity_t = boost::variant<viewport_fill_opacity_enum_t, float>;
    boost::optional<viewport_fill_opacity_t> viewport_fill_opacity;
};

std::ostream& operator<<(std::ostream& os, media_t::display_t e)
{
    switch(e)
    {
        case media_t::display_t::_inline:
            os << "inline";
            break;
        case media_t::display_t::block:
            os << "block";
            break;
        case media_t::display_t::list_item:
            os << "list-item";
            break;
        case media_t::display_t::run_in:
            os << "run-in";
            break;
        case media_t::display_t::compact:
            os << "compact";
            break;
        case media_t::display_t::marker:
            os << "marker";
            break;
        case media_t::display_t::table:
            os << "table";
            break;
        case media_t::display_t::inline_table:
            os << "inline-table";
            break;
        case media_t::display_t::table_row_group:
            os << "table-row-group";
            break;
        case media_t::display_t::table_header_group:
            os << "table-header-group";
            break;
        case media_t::display_t::table_footer_group:
            os << "table-footer-group";
            break;
        case media_t::display_t::table_row:
            os << "table-row";
            break;
        case media_t::display_t::table_column_group:
            os << "table-column-group";
            break;
        case media_t::display_t::table_column:
            os << "table-column";
            break;
        case media_t::display_t::table_cell:
            os << "table-cell";
            break;
        case media_t::display_t::table_caption:
            os << "table-caption";
            break;
        case media_t::display_t::none:
            os << "none";
            break;
        case media_t::display_t::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, media_t::display_t& e)
{
    std::string tok;
    is >> tok;
    if(tok == "inline")
        e = media_t::display_t::_inline;
    else if(tok == "block")
        e = media_t::display_t::block;
    else if(tok == "list-item")
        e = media_t::display_t::list_item;
    else if(tok == "run-in")
        e = media_t::display_t::run_in;
    else if(tok == "compact")
        e = media_t::display_t::compact;
    else if(tok == "marker")
        e = media_t::display_t::marker;
    else if(tok == "table")
        e = media_t::display_t::table;
    else if(tok == "inline-table")
        e = media_t::display_t::inline_table;
    else if(tok == "table-row-group")
        e = media_t::display_t::table_row_group;
    else if(tok == "table-header-group")
        e = media_t::display_t::table_header_group;
    else if(tok == "table-footer-group")
        e = media_t::display_t::table_footer_group;
    else if(tok == "table-row")
        e = media_t::display_t::table_row;
    else if(tok == "table-column-group")
        e = media_t::display_t::table_column_group;
    else if(tok == "table-column")
        e = media_t::display_t::table_column;
    else if(tok == "table-cell")
        e = media_t::display_t::table_cell;
    else if(tok == "table-caption")
        e = media_t::display_t::table_caption;
    else if(tok == "none")
        e = media_t::display_t::none;
    else if(tok == "inherit")
        e = media_t::display_t::inherit;
    else
        throw std::invalid_argument("unrecognised value for display: " + tok);
    return is;
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

