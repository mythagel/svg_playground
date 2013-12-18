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
 * boolean.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "boolean.h"
#include <string>
#include <ostream>
#include <istream>
#include <stdexcept>

namespace svg
{
namespace types
{

std::ostream& operator<<(std::ostream& os, const boolean& b)
{
    os << (b.value ? "true" : "false" );
    return os;
}
std::istream& operator>>(std::istream& is, boolean& b)
{
    std::string tok;
    is >> tok;
    if(tok == "true")
        b.value = true;
    else if(tok == "false")
        b.value = false;
    else
        throw std::invalid_argument("unrecognised value for boolean: " + tok);
    return is;
}

}
}
