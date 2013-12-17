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
 * vectoreffects.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef VECTOREFFECTS_H_
#define VECTOREFFECTS_H_
#include <iosfwd>

namespace svg
{
namespace types
{
namespace vectoreffects
{

enum class vector_effect
{
    none,
    non_scaling_stroke,
    inherit
};

std::ostream& operator<<(std::ostream& os, vector_effect v);
std::istream& operator>>(std::istream& is, vector_effect& v);

}
}
}

#endif /* VECTOREFFECTS_H_ */
