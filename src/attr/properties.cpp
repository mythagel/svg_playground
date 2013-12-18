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
 * properties.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "properties.h"

namespace svg
{
namespace attr
{

void map_attributes(properties& attr, attribute_map_t& attrs)
{
    map_attributes(attr.bidi, attrs);

    attrs.emplace("display-align", make_attr(attr.display_align));
    attrs.emplace("line-increment", make_attr(attr.line_increment));
    attrs.emplace("stop-colour", make_attr(attr.stop_colour));
    attrs.emplace("stop-opacity", make_attr(attr.stop_opacity));

    map_attributes(attr.media, attrs);

    attrs.emplace("fill-opacity", make_attr(attr.fill_opacity));
    attrs.emplace("stroke-opacity", make_attr(attr.stroke_opacity));
    attrs.emplace("fill", make_attr(attr.fill));
    attrs.emplace("fill-rule", make_attr(attr.fill_rule));
    attrs.emplace("stroke", make_attr(attr.stroke));
    attrs.emplace("stroke-dashoffset", make_attr(attr.stroke_dashoffset));
    attrs.emplace("stroke-linecap", make_attr(attr.stroke_linecap));
    attrs.emplace("stroke-linejoin", make_attr(attr.stroke_linejoin));
    attrs.emplace("stroke-miterlimit", make_attr(attr.stroke_miterlimit));
    attrs.emplace("stroke-width", make_attr(attr.stroke_width));
    attrs.emplace("color", make_attr(attr.color));
    attrs.emplace("color-rendering", make_attr(attr.color_rendering));
    attrs.emplace("solid-color", make_attr(attr.solid_color));
    attrs.emplace("solid-opacity", make_attr(attr.solid_opacity));
    attrs.emplace("font-family", make_attr(attr.font_family));
    attrs.emplace("font-size", make_attr(attr.font_size));
    attrs.emplace("font-style", make_attr(attr.font_style));
    attrs.emplace("font-variant", make_attr(attr.font_variant));
    attrs.emplace("font-weight", make_attr(attr.font_weight));
    attrs.emplace("text-anchor", make_attr(attr.text_anchor));
    attrs.emplace("text-align", make_attr(attr.text_align));
    attrs.emplace("vector-effect", make_attr(attr.vector_effect));
}

}
}
