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
    is >> std::noskipws;
    auto begin = std::istreambuf_iterator<char>{is};
    auto end = std::istreambuf_iterator<char>{};

    char tag[] = {'u', 'r', 'l', '('};
    auto it = std::search(begin, end, std::begin(tag), std::end(tag));
    if(it != begin)
        throw std::invalid_argument("expected func-iri");
    is >> iri.iri;
    char c;
    is >> c;
    if(c != ')')
        throw std::invalid_argument("expected func-iri");
    return is;
}

}
}
