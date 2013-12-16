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
 * bidi.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef BIDI_H_
#define BIDI_H_
#include <iosfwd>

namespace svg
{
namespace types
{
namespace bidi
{

enum class direction
{
    ltr,
    rtl,
    inherit
};

enum class unicode_bidi
{
    normal,
    embed,
    bidi_override,
    inherit
};

std::ostream& operator<<(std::ostream& os, direction v);
std::istream& operator>>(std::istream& is, direction& v);

std::ostream& operator<<(std::ostream& os, unicode_bidi v);
std::istream& operator>>(std::istream& is, unicode_bidi& v);

}
}
}

#endif /* BIDI_H_ */
