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
 * media.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "media.h"

namespace svg
{
namespace attr
{

void map_attributes(media& attr, attribute_map_t& attrs)
{
    attrs.emplace("display", make_attr(attr.display));
    attrs.emplace("visibility", make_attr(attr.visibility));
    attrs.emplace("image-rendering", make_attr(attr.image_rendering));
    attrs.emplace("pointer-events", make_attr(attr.pointer_events));
    attrs.emplace("shape-rendering", make_attr(attr.shape_rendering));
    attrs.emplace("text-rendering", make_attr(attr.text_rendering));
    attrs.emplace("buffered-rendering", make_attr(attr.buffered_rendering));
    attrs.emplace("audio-level", make_attr(attr.audio_level));
    attrs.emplace("viewport-fill", make_attr(attr.viewport_fill));
    attrs.emplace("viewport-fill-opacity", make_attr(attr.viewport_fill_opacity));
}

}
}
