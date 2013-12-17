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
 * media.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "media.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace media
{

std::ostream& operator<<(std::ostream& os, display v)
{
    switch(v)
    {
        case display::_inline:
            os << "inline";
            break;
        case display::block:
            os << "block";
            break;
        case display::list_item:
            os << "list-item";
            break;
        case display::run_in:
            os << "run-in";
            break;
        case display::compact:
            os << "compact";
            break;
        case display::marker:
            os << "marker";
            break;
        case display::table:
            os << "table";
            break;
        case display::inline_table:
            os << "inline-table";
            break;
        case display::table_row_group:
            os << "table-row-group";
            break;
        case display::table_header_group:
            os << "table-header-group";
            break;
        case display::table_footer_group:
            os << "table-footer-group";
            break;
        case display::table_row:
            os << "table-row";
            break;
        case display::table_column_group:
            os << "table-column-group";
            break;
        case display::table_column:
            os << "table-column";
            break;
        case display::table_cell:
            os << "table-cell";
            break;
        case display::table_caption:
            os << "table-caption";
            break;
        case display::none:
            os << "none";
            break;
        case display::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, display& v)
{
    std::string tok;
    is >> tok;
    if(tok == "inline")
        v = display::_inline;
    else if(tok == "block")
        v = display::block;
    else if(tok == "list-item")
        v = display::list_item;
    else if(tok == "run-in")
        v = display::run_in;
    else if(tok == "compact")
        v = display::compact;
    else if(tok == "marker")
        v = display::marker;
    else if(tok == "table")
        v = display::table;
    else if(tok == "inline-table")
        v = display::inline_table;
    else if(tok == "table-row-group")
        v = display::table_row_group;
    else if(tok == "table-header-group")
        v = display::table_header_group;
    else if(tok == "table-footer-group")
        v = display::table_footer_group;
    else if(tok == "table-row")
        v = display::table_row;
    else if(tok == "table-column-group")
        v = display::table_column_group;
    else if(tok == "table-column")
        v = display::table_column;
    else if(tok == "table-cell")
        v = display::table_cell;
    else if(tok == "table-caption")
        v = display::table_caption;
    else if(tok == "none")
        v = display::none;
    else if(tok == "inherit")
        v = display::inherit;
    else
        throw std::invalid_argument("unrecognised value for display: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, visibility v)
{
    return os;
}
std::istream& operator>>(std::istream& is, visibility& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, image_rendering v)
{
    return os;
}
std::istream& operator>>(std::istream& is, image_rendering& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, pointer_events v)
{
    return os;
}
std::istream& operator>>(std::istream& is, pointer_events& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, shape_rendering v)
{
    return os;
}
std::istream& operator>>(std::istream& is, shape_rendering& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, text_rendering v)
{
    return os;
}
std::istream& operator>>(std::istream& is, text_rendering& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, buffered_rendering v)
{
    return os;
}
std::istream& operator>>(std::istream& is, buffered_rendering& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const audio_level& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, audio_level& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const viewport_fill& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, viewport_fill& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const viewport_fill_opacity& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, viewport_fill_opacity& v)
{
    return is;
}

}
}
}
