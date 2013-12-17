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
 * flowable_text.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "flowable_text.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace flowable_text
{

std::ostream& operator<<(std::ostream& os, display_align v)
{
    switch(v)
    {
        case display_align::_auto:
            os << "auto";
            break;
        case display_align::before:
            os << "before";
            break;
        case display_align::center:
            os << "center";
            break;
        case display_align::after:
            os << "after";
            break;
        case display_align::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, display_align& v)
{
    std::string tok;
    is >> tok;
    if(tok == "auto")
        v = display_align::_auto;
    else if(tok == "before")
        v = display_align::before;
    else if(tok == "center")
        v = display_align::center;
    else if(tok == "after")
        v = display_align::after;
    else if(tok == "inherit")
        v = display_align::inherit;
    else
        throw std::invalid_argument("unrecognised value for display_align: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, const line_increment& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, line_increment& v)
{
    return is;
}

}
}
}
