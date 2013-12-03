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
 * colour.h
 *
 *  Created on: 2013-12-03
 *      Author: nicholas
 */

#ifndef COLOUR_H_
#define COLOUR_H_
#include <string>
#include <cstdint>
#include <iosfwd>

namespace svg
{
namespace types
{

struct colour
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    colour();
    colour(uint8_t r, uint8_t g, uint8_t b);
    colour(const std::string& str);
};

std::ostream& operator<<(std::ostream& os, const colour& c);

}
}

#endif /* COLOUR_H_ */
