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
 * pathparser.cpp
 *
 *  Created on: 2013-12-04
 *      Author: nicholas
 */

#include "pathparser.h"
#include <cctype>
#include <cerrno>

namespace svg
{
namespace path
{

namespace
{

struct point
{
    float x;
    float y;
};

inline bool throw_if(bool cond, const std::string& what)
{
    if(cond) throw parser::error(what);
    return cond;
}

bool ws_p(const char c)
{
	switch(c)
	{
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			return true;
		default:
			return false;
	}
}

bool parse_whitespace(const char*& c, const char* const end)
{
    if(!ws_p(*c))
        return false;

    while(c != end && ws_p(*c))
        ++c;
    return true;
}

bool number_p(const char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '.':
			return true;
		default:
			return std::isdigit(c);
	}
}

bool parse_number(const char*& c, const char* const end, float& x)
{
    if(!number_p(*c))
        return false;

    const auto begin = c;

    errno = 0;
    x = strtof(c, const_cast<char**>(&c));
    throw_if(c == begin || errno, "expected number");
    throw_if(c >= end, "unexpected eof; strtof consumed too much");
    return true;
}

bool parse_comma_wsp(const char*& c, const char* const end)
{
    if(!ws_p(*c) && *c != ',')
        return false;

    parse_whitespace(c, end) && throw_if(c == end, "unexpected eof");

    if(*c == ',')
        throw_if(++c == end, "unexpected eof");

    parse_whitespace(c, end);
    return true;
}

bool parse_coordinate_pair(const char*& c, const char* const end, point& p)
{
    if(!parse_number(c, end, p.x))
        return false;

    parse_comma_wsp(c, end) && throw_if(c == end, "unexpected eof");

    throw_if(!parse_number(c, end, p.y), "expected coordinate-pair");
    return true;
}

}

bool parser::parse_moveto(const char*& c, const char* const end)
{
    if(*c != 'M' && *c != 'm')
        return false;

    const auto cmd = *c++;
    throw_if(c == end, "unexpected eof");
    
    point p;
    throw_if(!parse_coordinate_pair(c, end, p), "expected coordinate-pair");
    move_to(cmd == 'M', p.x, p.y);

    while(c != end && parse_coordinate_pair(c, end, p))
        line_to(cmd == 'M', p.x, p.y);
    
    return true;
}
bool parser::parse_lineto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_horizontal_lineto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_vertical_lineto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_curveto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_smooth_curveto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_quadratic_bezier_curveto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_smooth_quadratic_bezier_curveto(const char*& c, const char* const end)
{
    return false;
}
bool parser::parse_closepath(const char*& c, const char* const end)
{
    return false;
}

parser::error::error(const std::string& what)
 : std::runtime_error(what)
{
}
parser::error::~error() noexcept
{
}

void parser::parse(const char* c, const char* const end)
{
	while(c != end)
	{
		if( parse_whitespace(c, end) || 
            parse_moveto(c, end) ||
            parse_lineto(c, end) || 
            parse_horizontal_lineto(c, end) || 
            parse_vertical_lineto(c, end) || 
            parse_curveto(c, end) || 
            parse_smooth_curveto(c, end) || 
            parse_quadratic_bezier_curveto(c, end) || 
            parse_smooth_quadratic_bezier_curveto(c, end) || 
            parse_closepath(c, end) )
			continue;
		else
			throw error{"expected wsp / moveto / lineto / horizontal-lineto / vertical-lineto / curveto / smooth-curveto / quadratic-bezier-curveto / smooth-quadratic-bezier-curveto / closepath"};
	}
	eof();
}

parser::~parser()
{
}

}
}

