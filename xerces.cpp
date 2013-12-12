#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <memory>
#include <iostream>
#include <boost/optional.hpp>

namespace
{
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}

int main (int argc, char* args[]) {
using namespace xercesc;

    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n" << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    auto errHandler = make_unique<HandlerBase>();
    auto parser = make_unique<XercesDOMParser>();
    parser->setErrorHandler(errHandler.get());
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);


    auto xmlFile = "x1.svg";

    try {
        parser->parse(xmlFile);

        std::unique_ptr<DOMDocument> doc{parser->adoptDocument()};
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
        return -1;
    }

    return 0;
}
