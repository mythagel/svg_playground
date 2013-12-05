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
 * colour.cpp
 *
 *  Created on: 2013-12-03
 *      Author: nicholas
 */

#include "colour.h"
#include <stdexcept>
#include <cstdio>
#include <iostream>
#include <iomanip>

namespace svg
{
namespace types
{

namespace
{

struct
{
    const char* name;
    const char* value;
} colour_map[] = 
{
    {"black", "rgb(0, 0, 0)"},
    {"green", "rgb(0, 128, 0)"},
    {"silver", "rgb(192, 192, 192)"},
    {"lime", "rgb(0, 255, 0)"},
    {"gray", "rgb(128, 128, 128)"},
    {"olive", "rgb(128, 128, 0)"},
    {"white", "rgb(255, 255, 255)"},
    {"yellow", "rgb(255, 255, 0)"},
    {"maroon", "rgb(128, 0, 0)"},
    {"navy", "rgb(0, 0, 128)"},
    {"red", "rgb(255, 0, 0)"},
    {"blue", "rgb(0, 0, 255)"},
    {"purple", "rgb(128, 0, 128)"},
    {"teal", "rgb(0, 128, 128)"},
    {"fuchsia", "rgb(255, 0, 255)"},
    {"aqua", "rgb(0, 255, 255)"}
};

}

colour::colour()
 : r(), g(), b()
{
}

colour::colour(uint8_t r, uint8_t g, uint8_t b)
 : r(r), g(g), b(b)
{
}

colour::colour(const std::string& str)
 : r(), g(), b()
{
    if(str.empty()) throw std::invalid_argument("empty colour specification");
    auto clr = str;
    
    // normalise #rgb to #rrggbb
    if(clr.size() == 4 && clr[0] == '#')
        clr = std::string("#") + clr[1]+clr[1] + clr[2]+clr[2] + clr[3]+clr[3];
    
    // normalise names to values
    for(auto& colour : colour_map)
    {
        if(clr == colour.name)
        {
            clr = colour.value;
            break;
        }
    }
    
    if(clr.size() == 7 && clr[0] == '#')
    {
        if (std::sscanf(clr.c_str() + 1, "%2hhx%2hhx%2hhx", &r, &g, &b) != 3)
            throw std::invalid_argument("Invalid colour " + str);
    }
    else if(clr.find("rgb(") == 0 && clr.back() == ')')
    {
        if (sscanf(clr.c_str() + 4, "%hhu , %hhu , %hhu", &r, &g, &b) != 3)
        {
            float rf, gf, bf;
            if (sscanf(clr.c_str() + 4, "%f%% , %f%% , %f%%", &rf, &gf, &bf) != 3)
                throw std::invalid_argument("Invalid colour " + str);
            r = (rf / 100.0) * 255;
            g = (gf / 100.0) * 255;
            b = (bf / 100.0) * 255;
        }
    }
    else
    {
        throw std::invalid_argument("Invalid colour " + str);
    }
}

std::ostream& operator<<(std::ostream& os, const colour& c)
{
    os << "rgb(" << static_cast<int>(c.r) << ", " << static_cast<int>(c.g) << ", " << static_cast<int>(c.b) << ")";
//    os << '#' << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c.r) 
//       << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c.g) 
//       << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(c.b);
    return os;
}

}
}

