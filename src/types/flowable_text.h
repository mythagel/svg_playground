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
 * flowable_text.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_FLOWABLE_TEXT_H_
#define TYPES_FLOWABLE_TEXT_H_
#include <boost/variant.hpp>
#include <iosfwd>

namespace svg
{
namespace types
{
namespace flowable_text
{

enum class display_align
{
    _auto,
    before,
    center,
    after,
    inherit
};

enum class line_increment_enum_t
{
    _auto,
    inherit
};
using line_increment = boost::variant<line_increment_enum_t, float>;

std::ostream& operator<<(std::ostream& os, display_align v);
std::istream& operator>>(std::istream& is, display_align& v);

std::ostream& operator<<(std::ostream& os, const line_increment& v);
std::istream& operator>>(std::istream& is, line_increment& v);

}
}
}

#endif /* TYPES_FLOWABLE_TEXT_H_ */
