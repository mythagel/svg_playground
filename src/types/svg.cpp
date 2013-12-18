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
 * svg.cpp
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#include "svg.h"
#include <ostream>
#include <istream>
#include <string>
#include <stdexcept>

namespace svg
{
namespace types
{
namespace svg
{

std::ostream& operator<<(std::ostream& os, const viewBox& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, viewBox& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, zoomAndPan v)
{
    switch(v)
    {
        case zoomAndPan::disable:
            os << "disable";
            break;
        case zoomAndPan::magnify:
            os << "magnify";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, zoomAndPan& v)
{
    std::string tok;
    is >> tok;
    if(tok == "disable")
        v = zoomAndPan::disable;
    else if(tok == "magnify")
        v = zoomAndPan::magnify;
    else
        throw std::invalid_argument("unrecognised value for zoomAndPan: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, version v)
{
    switch(v)
    {
        case version::one_zero:
            os << "1.0";
            break;
        case version::one_one:
            os << "1.1";
            break;
        case version::one_two:
            os << "1.2";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, version& v)
{
    std::string tok;
    is >> tok;
    if(tok == "1.0")
        v = version::one_zero;
    else if(tok == "1.1")
        v = version::one_one;
    else if(tok == "1.2")
        v = version::one_two;
    else
        throw std::invalid_argument("unrecognised value for version: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, baseProfile v)
{
    switch(v)
    {
        case baseProfile::none:
            os << "none";
            break;
        case baseProfile::tiny:
            os << "tiny";
            break;
        case baseProfile::basic:
            os << "basic";
            break;
        case baseProfile::full:
            os << "full";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, baseProfile& v)
{
    std::string tok;
    is >> tok;
    if(tok == "none")
        v = baseProfile::none;
    else if(tok == "tiny")
        v = baseProfile::tiny;
    else if(tok == "basic")
        v = baseProfile::basic;
    else if(tok == "full")
        v = baseProfile::full;
    else
        throw std::invalid_argument("unrecognised value for baseProfile: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, const snapshotTime& v)
{
    return os;
}
std::istream& operator>>(std::istream& is, snapshotTime& v)
{
    return is;
}

std::ostream& operator<<(std::ostream& os, timelineBegin v)
{
    switch(v)
    {
        case timelineBegin::onLoad:
            os << "onLoad";
            break;
        case timelineBegin::onStart:
            os << "onStart";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, timelineBegin& v)
{
    std::string tok;
    is >> tok;
    if(tok == "onLoad")
        v = timelineBegin::onLoad;
    else if(tok == "onStart")
        v = timelineBegin::onStart;
    else
        throw std::invalid_argument("unrecognised value for timelineBegin: " + tok);
    return is;
}

std::ostream& operator<<(std::ostream& os, playbackOrder v)
{
    switch(v)
    {
        case playbackOrder::all:
            os << "all";
            break;
        case playbackOrder::forwardOnly:
            os << "forwardOnly";
            break;
    }
    return os;
}
std::istream& operator>>(std::istream& is, playbackOrder& v)
{
    std::string tok;
    is >> tok;
    if(tok == "all")
        v = playbackOrder::all;
    else if(tok == "forwardOnly")
        v = playbackOrder::forwardOnly;
    else
        throw std::invalid_argument("unrecognised value for playbackOrder: " + tok);
    return is;
}

}
}
}
