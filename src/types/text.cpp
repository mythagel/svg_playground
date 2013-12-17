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
 * text.cpp
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#include "text.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace text
{

std::ostream& operator<<(std::ostream& os, const font_family& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, font_family& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, const font_size& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, font_size& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, font_style v)
{
    switch(v)
    {
        case font_style::normal:
            os << "normal";
            break;
        case font_style::italic:
            os << "italic";
            break;
        case font_style::oblique:
            os << "oblique";
            break;
        case font_style::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, font_style& v)
{
    std::string tok;
    is >> tok;
    if(tok == "normal")
        v = font_style::normal;
    else if(tok == "italic")
        v = font_style::italic;
    else if(tok == "oblique")
        v = font_style::oblique;
    else if(tok == "inherit")
        v = font_style::inherit;
    else
        throw std::invalid_argument("unrecognised value for font-style: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, font_variant v)
{
    switch(v)
    {
        case font_variant::normal:
            os << "normal";
            break;
        case font_variant::small_caps:
            os << "small-caps";
            break;
        case font_variant::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, font_variant& v)
{
    std::string tok;
    is >> tok;
    if(tok == "normal")
        v = font_variant::normal;
    else if(tok == "small-caps")
        v = font_variant::small_caps;
    else if(tok == "inherit")
        v = font_variant::inherit;
    else
        throw std::invalid_argument("unrecognised value for font-variant: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, font_weight v)
{
    switch(v)
    {
        case font_weight::normal:
            os << "normal";
            break;
        case font_weight::bold:
            os << "bold";
            break;
        case font_weight::bolder:
            os << "bolder";
            break;
        case font_weight::lighter:
            os << "lighter";
            break;
        case font_weight::_100:
            os << "100";
            break;
        case font_weight::_200:
            os << "200";
            break;
        case font_weight::_300:
            os << "300";
            break;
        case font_weight::_400:
            os << "400";
            break;
        case font_weight::_500:
            os << "500";
            break;
        case font_weight::_600:
            os << "600";
            break;
        case font_weight::_700:
            os << "700";
            break;
        case font_weight::_800:
            os << "800";
            break;
        case font_weight::_900:
            os << "900";
            break;
        case font_weight::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, font_weight& v)
{
    std::string tok;
    is >> tok;
    if(tok == "normal")
        v = font_weight::normal;
    else if(tok == "bold")
        v = font_weight::bold;
    else if(tok == "bolder")
        v = font_weight::bolder;
    else if(tok == "lighter")
        v = font_weight::lighter;
    else if(tok == "100")
        v = font_weight::_100;
    else if(tok == "200")
        v = font_weight::_200;
    else if(tok == "300")
        v = font_weight::_300;
    else if(tok == "400")
        v = font_weight::_400;
    else if(tok == "500")
        v = font_weight::_500;
    else if(tok == "600")
        v = font_weight::_600;
    else if(tok == "700")
        v = font_weight::_700;
    else if(tok == "800")
        v = font_weight::_800;
    else if(tok == "900")
        v = font_weight::_900;
    else if(tok == "inherit")
        v = font_weight::inherit;
    else
        throw std::invalid_argument("unrecognised value for font-variant: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, text_anchor v)
{
    switch(v)
    {
        case text_anchor::start:
            os << "start";
            break;
        case text_anchor::middle:
            os << "middle";
            break;
        case text_anchor::end:
            os << "end";
            break;
        case text_anchor::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, text_anchor& v)
{
    std::string tok;
    is >> tok;
    if(tok == "start")
        v = text_anchor::start;
    else if(tok == "middle")
        v = text_anchor::middle;
    else if(tok == "end")
        v = text_anchor::end;
    else if(tok == "inherit")
        v = text_anchor::inherit;
    else
        throw std::invalid_argument("unrecognised value for text-anchor: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, text_align v)
{
    switch(v)
    {
        case text_align::start:
            os << "start";
            break;
        case text_align::center:
            os << "center";
            break;
        case text_align::end:
            os << "end";
            break;
        case text_align::inherit:
            os << "inherit";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, text_align& v)
{
    std::string tok;
    is >> tok;
    if(tok == "start")
        v = text_align::start;
    else if(tok == "center")
        v = text_align::center;
    else if(tok == "end")
        v = text_align::end;
    else if(tok == "inherit")
        v = text_align::inherit;
    else
        throw std::invalid_argument("unrecognised value for text-align: " + tok);
    return is;
}

}
}
}
