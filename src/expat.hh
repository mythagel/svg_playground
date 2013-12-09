/*
 * expat.hh
 *
 *  Created on: 14/03/2011
 *      Author: nicholas
 */

#ifndef EXPATHH_H_
#define EXPATHH_H_
#include <string>
#include <vector>
#include <expat.h>

namespace expat
{

struct qname
{
    std::string prefix;
    std::string local;
};

template <typename T>
class parser : T
{
private:
	XML_Parser m_Parser;
	static const char NS_CHAR = 0x0C;

	// adapter functions
	static void startNamespace(void *userData, const XML_Char *prefix, const XML_Char *uri)
	{
		auto parser = static_cast<T*>(userData);
    	parser->startNamespace(prefix?prefix:"", uri?uri:"");
	}
	static void endNamespace(void *userData, const XML_Char *prefix)
	{
		auto parser = static_cast<T*>(userData);
    	parser->endNamespace(prefix?prefix:"");
	}

	static void startElement(void *userData, const char *nsname, const char **atts)
	{
	    auto parser = static_cast<T*>(userData);
	    auto name = SplitNamespace(nsname?nsname:"");

	    std::vector<std::pair<qname, std::string> > attributes;
	    while (*atts)
	    {
		    auto attribute_name = SplitNamespace(atts[0]?atts[0]:"");
		    attributes.emplace_back(attribute_name, atts[1]?atts[1]:"");
		    atts += 2;
	    }

	    parser->startElement(name, attributes);
	}
	static void endElement(void *userData, const char *nsname)
	{
	    auto parser = static_cast<T*>(userData);
	    auto name = SplitNamespace(nsname?nsname:"");

	    parser->endElement(name);
	}

	static void charData(void *userData, const XML_Char *s, int len)
	{
	    auto parser = static_cast<T*>(userData);
	    parser->charData(std::string(s, len));
	}
	static void CommentHandler(void *userData, const XML_Char *data)
	{
	    auto parser = static_cast<T*>(userData);
	    parser->CommentHandler(std::string(data?data:""));
	}

	static qname SplitNamespace(const std::string& nsname)
	{
	    auto pos = nsname.find(NS_CHAR);
	    if(pos != std::string::npos)
	        return { nsname.substr(0, pos), nsname.substr(pos+1, std::string::npos) };
	    else
		    return { {}, nsname };
	}
protected:
//	void startNamespace(const std::string& prefix, const std::string& uri);
//	void endNamespace(const std::string& prefix);

//	void startElement(const qname& name, const std::vector<std::pair<qname, std::string>>& attributes);
//	void endElement(const qname& name);

//	void charData(const std::string& cdata);
//	void CommentHandler(const std::string& data);
	parser()
	{
	    m_Parser = XML_ParserCreateNS(NULL, NS_CHAR);

	    XML_SetUserData(m_Parser, this);
	    XML_SetElementHandler(m_Parser, parser::startElement, parser::endElement);
	    XML_SetNamespaceDeclHandler(m_Parser, parser::startNamespace, parser::endNamespace);
	    XML_SetCharacterDataHandler(m_Parser, parser::charData);
	    XML_SetCommentHandler(m_Parser, parser::CommentHandler);
	}

public:
	operator XML_Parser() const
	{
	    return m_Parser;
    }

	/*
	 * Clients should call GetBuffer to get a handle to a buffer, then fill that
	 * buffer with data.
	 *
	 * After this Clients can call ParseBuffer to parse the given buffer.
	 *
	 * This saves double copying.
	 */
	void* GetBuffer(size_t size)
	{
        return XML_GetBuffer(m_Parser, size);
	}
	bool ParseBuffer(size_t len, bool done)
	{
	    int res = XML_ParseBuffer(m_Parser, len, done);
	    return res == XML_STATUS_OK;
	}

	/*
	 * One-shot parse the given string.
	 */
	bool Parse(const std::string& s)
	{
	    int res = XML_Parse(m_Parser, s.c_str(), s.size(), true);
	    return res == XML_STATUS_OK;
	}

	~parser()
	{
	    XML_ParserFree(m_Parser);
	}
};

}

#endif /* EXPATHH_H_ */

