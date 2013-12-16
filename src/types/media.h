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
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef MEDIA_H_
#define MEDIA_H_
#include <boost/variant.hpp>
#include <iosfwd>
#include "colour.h"

namespace svg
{
namespace types
{
namespace media
{

enum class display
{
    _inline,
    block,
    list_item,
    run_in,
    compact,
    marker,
    table,
    inline_table,
    table_row_group,
    table_header_group,
    table_footer_group,
    table_row,
    table_column_group,
    table_column,
    table_cell,
    table_caption,
    none,
    inherit
};

enum class visibility
{
    visible,
    hidden,
    inherit
};

enum class image_rendering
{
    _auto,
    optimizeSpeed,
    optimizeQuality,
    inherit
};

enum class pointer_events
{
    visiblePainted,
    visibleFill,
    visibleStroke,
    visible,
    painted,
    fill,
    stroke,
    all,
    none,
    inherit
};

enum class shape_rendering
{
    _auto,
    optimizeSpeed,
    crispEdges,
    geometricPrecision,
    inherit
};

enum class text_rendering
{
    _auto,
    optimizeSpeed,
    optimizeLegibility,
    geometricPrecision,
    inherit
};

enum class buffered_rendering
{
    _auto,
    dynamic,
    _static,
    inherit
};

enum class audio_level_enum_t
{
    inherit
};
using audio_level = boost::variant<audio_level_enum_t, float>;

enum class viewport_fill_enum_t
{
    inherit,
    none
};
using viewport_fill = boost::variant<viewport_fill_enum_t, types::colour>;

enum class viewport_fill_opacity_enum_t
{
    inherit
};
using viewport_fill_opacity = boost::variant<viewport_fill_opacity_enum_t, float>;


std::ostream& operator<<(std::ostream& os, display v);
std::istream& operator>>(std::istream& is, display& v);

std::ostream& operator<<(std::ostream& os, visibility v);
std::istream& operator>>(std::istream& is, visibility& v);

std::ostream& operator<<(std::ostream& os, image_rendering v);
std::istream& operator>>(std::istream& is, image_rendering& v);

std::ostream& operator<<(std::ostream& os, pointer_events v);
std::istream& operator>>(std::istream& is, pointer_events& v);

std::ostream& operator<<(std::ostream& os, shape_rendering v);
std::istream& operator>>(std::istream& is, shape_rendering& v);

std::ostream& operator<<(std::ostream& os, text_rendering v);
std::istream& operator>>(std::istream& is, text_rendering& v);

std::ostream& operator<<(std::ostream& os, buffered_rendering v);
std::istream& operator>>(std::istream& is, buffered_rendering& v);

std::ostream& operator<<(std::ostream& os, const audio_level& v);
std::istream& operator>>(std::istream& is, audio_level& v);

std::ostream& operator<<(std::ostream& os, const viewport_fill& v);
std::istream& operator>>(std::istream& is, viewport_fill& v);

std::ostream& operator<<(std::ostream& os, const viewport_fill_opacity& v);
std::istream& operator>>(std::istream& is, viewport_fill_opacity& v);

}
}
}

#endif /* MEDIA_H_ */
