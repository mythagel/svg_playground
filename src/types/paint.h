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
 * paint.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_PAINT_H_
#define TYPES_PAINT_H_
#include <boost/variant.hpp>
#include "colour.h"
#include "length.h"
#include "func_iri.h"
#include <string>
#include <iosfwd>

namespace svg
{
namespace types
{
namespace paint
{

enum class system_paint
{
    ActiveBorder,
    ActiveCaption,
    AppWorkspace,
    Background,
    ButtonFace,
    ButtonHighlight,
    ButtonShadow,
    ButtonText,
    CaptionText,
    GrayText,
    Highlight,
    HighlightText,
    InactiveBorder,
    InactiveCaption,
    InactiveCaptionText,
    InfoBackground,
    InfoText,
    Menu,
    MenuText,
    Scrollbar,
    ThreeDDarkShadow,
    ThreeDFace,
    ThreeDHighlight,
    ThreeDLightShadow,
    ThreeDShadow,
    Window,
    WindowFrame,
    WindowText
};

enum class paint_enum_t
{
    none,
    currentColor,
    inherit
};
struct paint_iri
{
    func_iri iri;
    enum fallback_enum_t
    {
        none,
        currentColor
    };
    boost::variant<fallback_enum_t, colour> fallback;
};
using paint = boost::variant<paint_enum_t, colour, paint_iri, system_paint>;

enum class fill_rule
{
    inherit,
    nonzero,
    evenodd
};

//stroke-dasharray

enum class stroke_dashoffset_enum_t
{
    inherit
};
using stroke_dashoffset = boost::variant<stroke_dashoffset_enum_t, length>;

enum class stroke_linecap
{
    butt,
    round,
    square,
    inherit
};

enum class stroke_linejoin
{
    miter,
    round,
    bevel,
    inherit
};

enum class stroke_miterlimit_enum_t
{
    inherit
};
using stroke_miterlimit = boost::variant<stroke_miterlimit_enum_t, float>;

enum class stroke_width_enum_t
{
    inherit
};
using stroke_width = boost::variant<stroke_width_enum_t, length>;

enum class color_enum_t
{
    inherit
};
using color = boost::variant<color_enum_t, types::colour>;

enum class color_rendering
{
    _auto,
    optimizeSpeed,
    optimizeQuality,
    inherit
};

std::ostream& operator<<(std::ostream& os, system_paint v);
std::istream& operator>>(std::istream& is, system_paint& v);

std::ostream& operator<<(std::ostream& os, const paint& v);
std::istream& operator>>(std::istream& is, paint& v);

std::ostream& operator<<(std::ostream& os, fill_rule v);
std::istream& operator>>(std::istream& is, fill_rule& v);

std::ostream& operator<<(std::ostream& os, const stroke_dashoffset& v);
std::istream& operator>>(std::istream& is, stroke_dashoffset& v);

std::ostream& operator<<(std::ostream& os, stroke_linecap v);
std::istream& operator>>(std::istream& is, stroke_linecap& v);

std::ostream& operator<<(std::ostream& os, stroke_linejoin v);
std::istream& operator>>(std::istream& is, stroke_linejoin& v);

std::ostream& operator<<(std::ostream& os, const stroke_miterlimit& v);
std::istream& operator>>(std::istream& is, stroke_miterlimit& v);

std::ostream& operator<<(std::ostream& os, const stroke_width& v);
std::istream& operator>>(std::istream& is, stroke_width& v);

std::ostream& operator<<(std::ostream& os, const color& v);
std::istream& operator>>(std::istream& is, color& v);

std::ostream& operator<<(std::ostream& os, color_rendering v);
std::istream& operator>>(std::istream& is, color_rendering& v);

}
}
}

#endif /* TYPES_PAINT_H_ */
