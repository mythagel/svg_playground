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
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "func_iri.h"
#include <ostream>
#include <istream>
#include <iterator>
#include <stdexcept>
#include "parsers/func_iri.h"

namespace svg
{
namespace types
{

std::ostream& operator<<(std::ostream& os, const func_iri& iri)
{
    os << "url(" << iri << ")";
    return os;
}
std::istream& operator>>(std::istream& is, func_iri& iri)
{
    std::string s;
    is >> s;

    auto c = s.c_str();
    auto end = c + s.size();

    if(!parsers::parse_func_iri(c, end, iri.iri))
        throw std::invalid_argument("expected func-iri");

    return is;
}

}
}
