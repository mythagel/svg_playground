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
 * svg.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef TYPES_SVG_H_
#define TYPES_SVG_H_
#include <boost/variant.hpp>
#include "clock_value.h"
#include <iosfwd>

namespace svg
{
namespace types
{
namespace svg
{

enum class viewBox_enum_t
{
    none
};
struct viewBox_t
{
    float min_x;
    float min_y;
    float width;
    float height;
};
using viewBox = boost::variant<viewBox_enum_t, viewBox_t>;

enum class zoomAndPan
{
    disable,
    magnify
};

enum class version
{
    one_zero,
    one_one,
    one_two
};

enum class baseProfile
{
    none,
    tiny,
    basic,
    full
};

enum class snapshotTime_enum_t
{
    none
};
using snapshotTime = boost::variant<snapshotTime_enum_t, clock_value>;

enum class timelineBegin
{
    onLoad,
    onStart
};

enum class playbackOrder
{
    all,
    forwardOnly
};

std::ostream& operator<<(std::ostream& os, const viewBox& v);
std::istream& operator>>(std::istream& is, viewBox& v);

std::ostream& operator<<(std::ostream& os, zoomAndPan v);
std::istream& operator>>(std::istream& is, zoomAndPan& v);

std::ostream& operator<<(std::ostream& os, version v);
std::istream& operator>>(std::istream& is, version& v);

std::ostream& operator<<(std::ostream& os, baseProfile v);
std::istream& operator>>(std::istream& is, baseProfile& v);

std::ostream& operator<<(std::ostream& os, const snapshotTime& v);
std::istream& operator>>(std::istream& is, snapshotTime& v);

std::ostream& operator<<(std::ostream& os, timelineBegin v);
std::istream& operator>>(std::istream& is, timelineBegin& v);

std::ostream& operator<<(std::ostream& os, playbackOrder v);
std::istream& operator>>(std::istream& is, playbackOrder& v);

}
}
}

#endif /* TYPES_SVG_H_ */
