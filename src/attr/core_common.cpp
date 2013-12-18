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
 * core_common.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "core_common.h"

namespace svg
{
namespace attr
{

void map_attributes(core_common& attr, attribute_map_t& attrs)
{
    attrs.emplace("id", make_attr(attr.id));
    attrs.emplace("base", make_attr(attr.base));
    attrs.emplace("lang", make_attr(attr.lang));
    attrs.emplace("class", make_attr(attr._class));
    attrs.emplace("role", make_attr(attr.role));
    attrs.emplace("rel", make_attr(attr.rel));
    attrs.emplace("rev", make_attr(attr.rev));
    attrs.emplace("typeof", make_attr(attr._typeof));
    attrs.emplace("content", make_attr(attr.content));
    attrs.emplace("datatype", make_attr(attr.datatype));
    attrs.emplace("resource", make_attr(attr.resource));
    attrs.emplace("about", make_attr(attr.about));
    attrs.emplace("property", make_attr(attr.property));
}

}
}
