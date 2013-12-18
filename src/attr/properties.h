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
 * properties.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ATTR_PROPERTIES_H_
#define ATTR_PROPERTIES_H_
#include <boost/optional.hpp>
#include "typed_attribute.h"
#include "bidi.h"
#include "../types/flowable_text.h"
#include "../types/gradient.h"
#include "../types/opacity.h"
#include "../types/paint.h"
#include "../types/solidcolour.h"
#include "../types/text.h"
#include "../types/vectoreffects.h"
#include "media.h"

namespace svg
{
namespace attr
{

struct properties
{
    attr::bidi bidi;

    boost::optional<types::flowable_text::display_align> display_align;
    boost::optional<types::flowable_text::line_increment> line_increment;

    boost::optional<types::gradient::stop_colour> stop_colour;
    boost::optional<types::gradient::stop_opacity> stop_opacity;

    attr::media media;

    boost::optional<types::opacity::fill_opacity> fill_opacity;
    boost::optional<types::opacity::stroke_opacity> stroke_opacity;

    boost::optional<types::paint::paint> fill;
    boost::optional<types::paint::fill_rule> fill_rule;
    boost::optional<types::paint::paint> stroke;
    // TODO stroke-dasharray
    boost::optional<types::paint::stroke_dashoffset> stroke_dashoffset;
    boost::optional<types::paint::stroke_linecap> stroke_linecap;
    boost::optional<types::paint::stroke_linejoin> stroke_linejoin;
    boost::optional<types::paint::stroke_miterlimit> stroke_miterlimit;
    boost::optional<types::paint::stroke_width> stroke_width;
    boost::optional<types::paint::color> color;
    boost::optional<types::paint::color_rendering> color_rendering;

    boost::optional<types::solidcolour::solid_color> solid_color;
    boost::optional<types::solidcolour::solid_opacity> solid_opacity;

    boost::optional<types::text::font_family> font_family;
    boost::optional<types::text::font_size> font_size;
    boost::optional<types::text::font_style> font_style;
    boost::optional<types::text::font_variant> font_variant;
    boost::optional<types::text::font_weight> font_weight;
    boost::optional<types::text::text_anchor> text_anchor;
    boost::optional<types::text::text_align> text_align;

    boost::optional<types::vectoreffects::vector_effect> vector_effect;
};

void map_attributes(properties& attr, attribute_map_t& attrs);

}
}

#endif /* ATTR_PROPERTIES_H_ */
