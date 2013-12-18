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
 * func_iri.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "func_iri.h"
#include <stdexcept>
#include <system_error>

namespace svg
{
namespace types
{
namespace parsers
{

namespace
{
inline bool throw_if(bool cond, const std::string& what)
{
    if(cond) throw std::runtime_error(what);
    return cond;
}
}

bool parse_func_iri(const char* c, const char* const end, network::uri& uri)
{
    char tag[] = {'u', 'r', 'l', '('};
    auto it = std::search(c, end, std::begin(tag), std::end(tag));
    if(it != c) return false;
    c += sizeof(tag);
    throw_if(c == end, "unexpected eof");

    auto iri_c = c;

    while(c != end && *c != ')')
        ++c;
    throw_if(c == end, "unexpected eof");

    std::error_code ec;
    uri = network::make_uri(iri_c, c, ec);
    if(ec) throw std::system_error(ec);

    throw_if(*c != ')', "expected )");
    ++c;
    return true;
}

}
}
}
