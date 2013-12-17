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
 * focus.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "focus.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace focus
{

std::ostream& operator<<(std::ostream& os, focusHighlight v)
{
    switch(v)
    {
        case focusHighlight::_auto:
            os << "auto";
            break;
        case focusHighlight::none:
            os << "none";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, focusHighlight& v)
{
    std::string tok;
    is >> tok;
    if(tok == "auto")
        v = focusHighlight::_auto;
    else if(tok == "none")
        v = focusHighlight::none;
    else
        throw std::invalid_argument("unrecognised value for focusHighlight: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, const navigation& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, navigation& v)
{
    return is;
}

}
}
}
