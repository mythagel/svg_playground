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
 * text.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TEXT_H_
#define TEXT_H_
#include <boost/variant.hpp>
#include <string>
#include <iosfwd>
#include "length.h"

namespace svg
{
namespace types
{
namespace text
{

enum class font_family_enum_t
{
    inherit
};
using font_family = boost::variant<font_family_enum_t, std::string/*font family*/>;

enum class font_size_enum_t
{
    inherit
};
enum class font_size_absolute_enum_t
{
    xx_small,
    x_small,
    small,
    medium,
    large,
    x_large,
    xx_large
};
enum class font_size_relative_enum_t
{
    larger,
    smaller
};
using font_size = boost::variant<font_size_enum_t, font_size_absolute_enum_t, font_size_relative_enum_t, types::length>;

enum class font_style
{
    normal,
    italic,
    oblique,
    inherit
};

enum class font_variant
{
    normal,
    small_caps,
    inherit
};

enum class font_weight
{
    normal,
    bold,
    bolder,
    lighter,
    _100,
    _200,
    _300,
    _400,
    _500,
    _600,
    _700,
    _800,
    _900,
    inherit
};

enum class text_anchor
{
    start,
    middle,
    end,
    inherit
};

enum class text_align
{
    start,
    center,
    end,
    inherit
};

std::ostream& operator<<(std::ostream& os, const font_family& v);
std::istream& operator>>(std::istream& is, font_family& v);

std::ostream& operator<<(std::ostream& os, const font_size& v);
std::istream& operator>>(std::istream& is, font_size& v);

std::ostream& operator<<(std::ostream& os, font_style v);
std::istream& operator>>(std::istream& is, font_style& v);

std::ostream& operator<<(std::ostream& os, font_variant v);
std::istream& operator>>(std::istream& is, font_variant& v);

std::ostream& operator<<(std::ostream& os, font_weight v);
std::istream& operator>>(std::istream& is, font_weight& v);

std::ostream& operator<<(std::ostream& os, text_anchor v);
std::istream& operator>>(std::istream& is, text_anchor& v);

std::ostream& operator<<(std::ostream& os, text_align v);
std::istream& operator>>(std::istream& is, text_align& v);

}
}
}

#endif /* TEXT_H_ */
