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
 * aspect_ratio.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_ASPECT_RATIO_H_
#define TYPES_ASPECT_RATIO_H_
#include <iosfwd>

namespace svg
{
namespace types
{
namespace aspect_ratio
{

enum class align_t
{
    none,
    xMinYMin,
    xMidYMin,
    xMaxYMin,
    xMinYMid,
    xMidYMid,
    xMaxYMid,
    xMinYMax,
    xMidYMax,
    xMaxYMax
};

struct preserveAspectRatio
{
    bool defer;
    align_t align;
    bool meet;
};

std::ostream& operator<<(std::ostream& os, const preserveAspectRatio& v);
std::istream& operator>>(std::istream& is, preserveAspectRatio& v);

}
}
}

#endif /* TYPES_ASPECT_RATIO_H_ */
