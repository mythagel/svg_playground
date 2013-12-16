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
 * core.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "core.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace core
{

std::ostream& operator<<(std::ostream& os, space v)
{
    switch(v)
    {
        case space::_default:
            os << "default";
            break;
        case space::preserve:
            os << "preserve";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, space& v)
{
    std::string tok;
    is >> tok;
    if(tok == "default")
        v = space::_default;
    else if(tok == "preserve")
        v = space::preserve;
    else
        throw std::invalid_argument("unrecognised value for space: " + tok);
    return is;
}

}
}
}
