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
 * animate.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef ANIMATE_H_
#define ANIMATE_H_
#include <iosfwd>
#include <boost/variant.hpp>
#include <string>
#include "clock_value.h"

namespace svg
{
namespace types
{
namespace animate
{

enum class syncBehaviorDefault
{
    canSlip,
    locked,
    independent,
    inherit
};

enum class syncToleranceDefault_enum_t
{
    inherit
};
using syncToleranceDefault = boost::variant<syncToleranceDefault_enum_t, clock_value>;

std::ostream& operator<<(std::ostream& os, syncBehaviorDefault v);
std::istream& operator>>(std::istream& is, syncBehaviorDefault& v);

std::ostream& operator<<(std::ostream& os, const syncToleranceDefault& v);
std::istream& operator>>(std::istream& is, syncToleranceDefault& v);

}
}
}

#endif /* ANIMATE_H_ */
