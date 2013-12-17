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

#ifndef FOCUS_H_
#define FOCUS_H_
#include <boost/variant.hpp>
#include <iosfwd>

namespace svg
{
namespace types
{
namespace focus
{

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
using navigation = boost::variant<navigation_enum_t, std::string/*FuncIRI*/>;

std::ostream& operator<<(std::ostream& os, focusHighlight v);
std::istream& operator>>(std::istream& is, focusHighlight& v);

std::ostream& operator<<(std::ostream& os, const navigation& v);
std::istream& operator>>(std::istream& is, navigation& v);

}
}
}

#endif /* FOCUS_H_ */
