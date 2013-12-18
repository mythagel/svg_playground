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
 * animate.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "animate.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

#include <sstream>

namespace svg
{
namespace types
{
namespace animate
{

std::ostream& operator<<(std::ostream& os, syncBehaviorDefault v)
{
    switch(v)
    {
        case syncBehaviorDefault::canSlip:
            os << "canSlip";
            break;
        case syncBehaviorDefault::locked:
            os << "locked";
            break;
        case syncBehaviorDefault::independent:
            os << "independent";
            break;
        case syncBehaviorDefault::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, syncBehaviorDefault& v)
{
    std::string tok;
    is >> tok;
    if(tok == "canSlip")
        v = syncBehaviorDefault::canSlip;
    else if(tok == "locked")
        v = syncBehaviorDefault::locked;
    else if(tok == "independent")
        v = syncBehaviorDefault::independent;
    else if(tok == "inherit")
        v = syncBehaviorDefault::inherit;
    else
        throw std::invalid_argument("unrecognised value for syncBehaviorDefault: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, const syncToleranceDefault& v)
{
    struct map : boost::static_visitor<std::ostream&>
    {
        map(std::ostream& os)
         : os(os)
        {
        }

        std::ostream& os;
        std::ostream& operator()(syncToleranceDefault_enum_t e) const
        {
            switch(e)
            {
                case syncToleranceDefault_enum_t::inherit:
                    os << "inherit";
                    return os;
                default:
                    throw std::logic_error("Unexpected syncToleranceDefault enum");
            }
        }

        std::ostream& operator()(const clock_value &clock) const
        {
            os << clock;
            return os;
        }
    };
    return boost::apply_visitor(map{os}, v);
}
std::istream& operator>>(std::istream& is, syncToleranceDefault& v)
{
    std::string tok;
    is >> tok;
    if(tok == "inherit")
    {
        v = syncToleranceDefault_enum_t::inherit;
    }
    else
    {
        /* Actually... all parsing is on fixed size strings.
           perhaps change to to_string() & from_string()
           */
        std::istringstream ss(tok);
        clock_value clock;
        ss >> clock;
        v = clock;
    }
    return is;
}

}
}
}
