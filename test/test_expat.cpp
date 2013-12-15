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
#include "colour.h"

namespace network
{
struct uri
{
};
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

    virtual boost::optional<std::string> get() const override
    {
        auto& v = value.get();
        using std::to_string;
        return v ? boost::make_optional(to_string(*v)) : boost::none;
    }
    virtual void set(const boost::optional<std::string>& value) override
    {
        auto& v = value.get();
        v = T{value};
    }

    virtual ~optional_typed_attribute_ref()
    {
    }
};

struct core_common_t
{
    boost::optional<std::string> id;
    boost::optional<network::uri> base;
    boost::optional<std::string> lang;
    boost::optional<std::string> _class;
    boost::optional<std::vector<std::string>> role;
    boost::optional<std::vector<std::string>> rel;
    boost::optional<std::vector<std::string>> rev;
    boost::optional<std::vector<std::string>> _typeof;
    boost::optional<std::string> content;
    boost::optional<std::string> datatype;
    boost::optional<std::string> resource;
    boost::optional<std::vector<std::string>> about;
    boost::optional<std::vector<std::string>> property;
};

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

struct conditional_t
{
    boost::optional<std::vector<network::uri>> requiredFeatures;
    boost::optional<std::vector<network::uri>> requiredExtensions;
    boost::optional<std::vector<std::string>> requiredFormats;
    boost::optional<std::vector<std::string>> requiredFonts;
    boost::optional<std::vector<std::string>> systemLanguage;
};

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

