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
#include <utility>
#include <stdexcept>

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
    qualified_name name;

    element_t(const qualified_name& name)
     : name(name)
    {
    }

    // interface for attribute iterators.
    // read/write still needs to be virtual.
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

    virtual node insert(const node& child, const node& ref) override
    {
        throw std::runtime_error("character node cannot have children.");
    }

    virtual node erase(const node& child) override
    {
        throw std::runtime_error("character node cannot have children.");
    }

    virtual node clone(bool)
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
    std::map<qualified_name, std::string> attributes;

    basic_element_t(const qualified_name& name)
     : element_t(name)
    {
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
    }

    virtual ~basic_element_t()
    {
    }
};

}

struct parser : expat::parser<parser>
{
    std::stack<dom::node> stack;
    dom::node root;
    void startNamespace(const std::string&, const std::string&)
	{
	}
    void endNamespace(const std::string&)
	{
	}

	void startElement(const expat::qname& name, const std::vector<std::pair<expat::qname, std::string>>& attributes)
	{
        // based on the qualified element name could construct different subclasses of element_t
        dom::element element = std::make_shared<dom::basic_element_t>(dom::qualified_name{ name.local, name.prefix });

	    for(auto& attr : attributes)
            element->set_attribute({ attr.first.local, attr.first.prefix }, attr.second);

        stack.push(element);
	}
	void endElement(const expat::qname& name)
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

std::ostream& operator<<(std::ostream& os, const dom::node& node)
{
    os << "{\n";
    if(auto element = std::dynamic_pointer_cast<dom::element_t>(node))
    {
        os << element->name.ns << ":" << element->name.local << "\n";
        // TODO attributes...
    }
    else if(auto cdata = std::dynamic_pointer_cast<dom::character_t>(node))
    {
        os << "char: '" << cdata->data << "'\n";
    }

    for(auto& child : node->children)
        os << "child: " << child << "\n";
    os << "}\n";
    return os;
}

int main()
{
    std::ifstream f("x1.svg", std::ios::binary);
    if(!f) throw std::runtime_error("file x1.svg not found.");
    f >> std::noskipws;
    std::string s{std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>()};
    
    parser p;
    p.Parse(s);

    auto root = p.root;
    std::cout << root;
    return 0;
}

