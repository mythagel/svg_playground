#include "expat.hh"
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdexcept>

struct parser : expat::parser<parser>
{
	void startNamespace(const std::string& prefix, const std::string& uri)
	{
	    std::cout << "ns " << prefix << " = " << uri << "\n";
	}
	void endNamespace(const std::string& prefix)
	{
	    std::cout << "END ns " << prefix << "\n";
	}

	void startElement(const expat::qname& name, const std::vector<std::pair<expat::qname, std::string>>& attributes)
	{
	    std::cout << "<" << name.prefix << ":" << name.local << " ";
	    for(auto& attr : attributes)
	        std::cout << attr.first.prefix << ":" << attr.first.local << " = '" << attr.second << "' ";
        std::cout << ">";
	}
	void endElement(const expat::qname& name)
	{
	    std::cout << "</" << name.prefix << ":" << name.local << ">";
	}

	void charData(const std::string& cdata)
	{
	    std::cout << cdata;
	}
	void CommentHandler(const std::string& data)
	{
	
	}
};

int main()
{
    std::ifstream f("x1.svg", std::ios::binary);
    if(!f) throw std::runtime_error("file x1.svg not found.");
    f >> std::noskipws;
    std::string s{std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>()};
    
    parser p;
    p.Parse(s);
    return 0;
}

