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
 * gradient.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_GRADIENT_H_
#define TYPES_GRADIENT_H_
#include <boost/variant.hpp>
#include "colour.h"
#include <iosfwd>

namespace svg
{
namespace types
{
namespace gradient
{

enum class stop_colour_enum_t
{
    inherit
};
using stop_colour = boost::variant<stop_colour_enum_t, colour>;

enum class stop_opacity_enum_t
{
    inherit
};
using stop_opacity = boost::variant<stop_opacity_enum_t, float>;

std::ostream& operator<<(std::ostream& os, const stop_colour& v);
std::istream& operator>>(std::istream& is, stop_colour& v);

std::ostream& operator<<(std::ostream& os, const stop_opacity& v);
std::istream& operator>>(std::istream& is, stop_opacity& v);

}
}
}

#endif /* TYPES_GRADIENT_H_ */
