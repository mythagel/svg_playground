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
 * focus.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_FOCUS_H_
#define TYPES_FOCUS_H_
#include <boost/variant.hpp>
#include <iosfwd>
#include "func_iri.h"
#include "boolean.h"

namespace svg
{
namespace types
{
namespace focus
{

enum class focusable_enum_t
{
    _auto
};
using focusable = boost::variant<focusable_enum_t, boolean>;

enum class focusHighlight
{
    _auto,
    none
};

enum class navigation_enum_t
{
    _auto,
    self
};
using navigation = boost::variant<navigation_enum_t, func_iri>;

std::ostream& operator<<(std::ostream& os, const focusable& v);
std::istream& operator>>(std::istream& is, focusable& v);

std::ostream& operator<<(std::ostream& os, focusHighlight v);
std::istream& operator>>(std::istream& is, focusHighlight& v);

std::ostream& operator<<(std::ostream& os, const navigation& v);
std::istream& operator>>(std::istream& is, navigation& v);

}
}
}

#endif /* TYPES_FOCUS_H_ */
