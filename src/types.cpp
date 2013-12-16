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
 * types.cpp
 *
 *  Created on: 2013-12-05
 *      Author: nicholas
 */

#include "types.h"
#include <stdexcept>
#include <ostream>
#include <istream>

namespace svg
{
namespace types
{

length::length()
 : value(0.0f), unit(unit_t::ucs)
{
}

length::length(float value)
 : value(value), unit(unit_t::ucs)
{
}
length::length(float value, unit_t unit)
 : value(value), unit(unit)
{
}

std::ostream& operator<<(std::ostream& os, const length& l)
{
    os << l.value;
    switch(l.unit)
    {
        case length::unit_t::ucs:
            break;
        case length::unit_t::cm:
            os << "cm";
            break;
        case length::unit_t::mm:
            os << "mm";
            break;
        case length::unit_t::pt:
            os << "pt";
            break;
        case length::unit_t::pc:
            os << "pc";
            break;
        case length::unit_t::px:
            os << "px";
            break;
        case length::unit_t::pct:
            os << "%";
            break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, length& l)
{
    is >> l.value;
    std::string tok;
    is >> tok;
    if(tok == "cm")
        l.unit = length::unit_t::cm;
    else if(tok == "mm")
        l.unit = length::unit_t::mm;
    else if(tok == "pt")
        l.unit = length::unit_t::pt;
    else if(tok == "pc")
        l.unit = length::unit_t::pc;
    else if(tok == "px")
        l.unit = length::unit_t::px;
    else if(tok == "%")
        l.unit = length::unit_t::pct;
    else if(tok.empty())
        l.unit = length::unit_t::ucs;
    else
        throw std::invalid_argument("unexpected unit in length: " + tok);
    return is;
}

bool parse_bool(const std::string& str)
{
    if(str == "true")
        return true;
    else if(str == "false")
        return false;
    throw std::invalid_argument("invalid value for bool: " + str);
}

}
}

