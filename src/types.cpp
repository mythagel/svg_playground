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

namespace svg
{
namespace types
{

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

