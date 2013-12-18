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
 * media.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ATTR_MEDIA_H_
#define ATTR_MEDIA_H_
#include <boost/optional.hpp>
#include "typed_attribute.h"
#include "../types/media.h"

namespace svg
{
namespace attr
{

struct media
{
    boost::optional<types::media::display> display;
    boost::optional<types::media::visibility> visibility;
    boost::optional<types::media::image_rendering> image_rendering;
    boost::optional<types::media::pointer_events> pointer_events;
    boost::optional<types::media::shape_rendering> shape_rendering;
    boost::optional<types::media::text_rendering> text_rendering;
    boost::optional<types::media::buffered_rendering> buffered_rendering;
    boost::optional<types::media::audio_level> audio_level;
    boost::optional<types::media::viewport_fill> viewport_fill;
    boost::optional<types::media::viewport_fill_opacity> viewport_fill_opacity;
};

void map_attributes(media& attr, attribute_map_t& attrs);

}
}

#endif /* ATTR_MEDIA_H_ */
