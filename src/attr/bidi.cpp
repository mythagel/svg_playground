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
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "bidi.h"

namespace svg
{
namespace attr
{

void map_attributes(bidi& attr, attribute_map_t& attrs)
{
    attrs.emplace("direction", make_attr(attr.direction));
    attrs.emplace("unicode-bidi", make_attr(attr.unicode_bidi));
}

}
}
