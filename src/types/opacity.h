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
 * opacity.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_OPACITY_H_
#define TYPES_OPACITY_H_
#include <boost/variant.hpp>
#include <iosfwd>

namespace svg
{
namespace types
{
namespace opacity
{

enum class fill_opacity_enum_t
{
    inherit
};
using fill_opacity = boost::variant<fill_opacity_enum_t, float>;

enum class stroke_opacity_enum_t
{
    inherit
};
using stroke_opacity = boost::variant<stroke_opacity_enum_t, float>;

std::ostream& operator<<(std::ostream& os, const fill_opacity& v);
std::istream& operator>>(std::istream& is, fill_opacity& v);

std::ostream& operator<<(std::ostream& os, const stroke_opacity& v);
std::istream& operator>>(std::istream& is, stroke_opacity& v);

}
}
}

#endif /* TYPES_OPACITY_H_ */
