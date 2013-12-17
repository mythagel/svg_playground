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
 * bidi.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "bidi.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace bidi
{

std::ostream& operator<<(std::ostream& os, direction v)
{
    switch(v)
    {
        case direction::ltr:
            os << "ltr";
            break;
        case direction::rtl:
            os << "rtl";
            break;
        case direction::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, direction& v)
{
    std::string tok;
    is >> tok;
    if(tok == "ltr")
        v = direction::ltr;
    else if(tok == "rtl")
        v = direction::rtl;
    else if(tok == "inherit")
        v = direction::inherit;
    else
        throw std::invalid_argument("unrecognised value for direction: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, unicode_bidi v)
{
    switch(v)
    {
        case unicode_bidi::normal:
            os << "normal";
            break;
        case unicode_bidi::embed:
            os << "embed";
            break;
        case unicode_bidi::bidi_override:
            os << "bidi-override";
            break;
        case unicode_bidi::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, unicode_bidi& v)
{
    std::string tok;
    is >> tok;
    if(tok == "normal")
        v = unicode_bidi::normal;
    else if(tok == "embed")
        v = unicode_bidi::embed;
    else if(tok == "bidi-override")
        v = unicode_bidi::bidi_override;
    else if(tok == "inherit")
        v = unicode_bidi::inherit;
    else
        throw std::invalid_argument("unrecognised value for unicode_bidi: " + tok);
    return is;
}

}
}
}
