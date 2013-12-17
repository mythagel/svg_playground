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
 * vectoreffects.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "vectoreffects.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace vectoreffects
{

std::ostream& operator<<(std::ostream& os, vector_effect v)
{
    switch(v)
    {
        case vector_effect::none:
            os << "none";
            break;
        case vector_effect::non_scaling_stroke:
            os << "non-scaling-stroke";
            break;
        case vector_effect::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, vector_effect& v)
{
    std::string tok;
    is >> tok;
    if(tok == "none")
        v = vector_effect::none;
    else if(tok == "non-scaling-stroke")
        v = vector_effect::non_scaling_stroke;
    else if(tok == "inherit")
        v = vector_effect::inherit;
    else
        throw std::invalid_argument("unrecognised value for vector-effect: " + tok);
    return is;
}

}
}
}
