#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>



inline bool throw_if(bool cond, const std::string& what)
{
    if(cond) throw std::logic_error(what);
    return cond;
}

int main()
{
//    bool ws_p(const char c);
//    bool parse_whitespace(const char*& c, const char* const end);

//    bool number_p(const char c);
//    bool parse_number(const char*& c, const char* const end, float& x);

//    bool parse_comma_wsp(const char*& c, const char* const end);

//    bool parse_bool(const std::string& str);

    return 0;
}
