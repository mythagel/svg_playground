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
 * clock_value.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "clock_value.h"
#include <stdexcept>
#include <ostream>
#include <istream>

namespace svg
{
namespace types
{

clock_value::clock_value()
 : value(0.0f), unit(unit_t::s)
{
}

clock_value::clock_value(float value)
 : value(value), unit(unit_t::s)
{
}
clock_value::clock_value(float value, unit_t unit)
 : value(value), unit(unit)
{
}

std::ostream& operator<<(std::ostream& os, const clock_value& l)
{
    os << l.value;
    switch(l.unit)
    {
        case clock_value::unit_t::s:
            os << "s";
            break;
        case clock_value::unit_t::ms:
            os << "ms";
            break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, clock_value& l)
{
    is >> l.value;
    std::string tok;
    is >> tok;
    if(tok == "s")
        l.unit = clock_value::unit_t::s;
    else if(tok == "ms")
        l.unit = clock_value::unit_t::ms;
    else
        throw std::invalid_argument("unexpected unit in clock-value: " + tok);
    return is;
}

}
}
