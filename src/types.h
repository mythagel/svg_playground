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
 * types.h
 *
 *  Created on: 2013-12-05
 *      Author: nicholas
 */

#ifndef TYPES_H_
#define TYPES_H_
#include <string>
#include <vector>
#include <iosfwd>

namespace svg
{
namespace types
{

struct length
{
    float value;
    enum class unit_t
    {
        ucs,
        cm,
        mm,
        pt,
        pc,
        px,
        pct
    } unit;

    length();
    explicit length(float value);
    explicit length(float value, unit_t unit);
};

std::ostream& operator<<(std::ostream& os, const length& l);
std::istream& operator>>(std::istream& is, length& l);

bool parse_bool(const std::string& str);

// std::vector<std::string> parse_string_list(const std::string& str);

}
}

#endif /* TYPES_H_ */
