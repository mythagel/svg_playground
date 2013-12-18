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
 * clock_value.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef TYPES_CLOCK_VALUE_H_
#define TYPES_CLOCK_VALUE_H_
#include <iosfwd>

namespace svg
{
namespace types
{

struct clock_value
{
    float value;
    enum class unit_t
    {
        s,
        ms
    } unit;

    clock_value();
    explicit clock_value(float value);
    explicit clock_value(float value, unit_t unit);
};

std::ostream& operator<<(std::ostream& os, const clock_value& l);
std::istream& operator>>(std::istream& is, clock_value& l);

}
}

#endif /* TYPES_CLOCK_VALUE_H_ */
