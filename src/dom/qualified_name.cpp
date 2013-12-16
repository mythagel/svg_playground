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
 * qualified_name.cpp
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#include "qualified_name.h"
#include <tuple>

namespace dom
{

qualified_name::qualified_name()
{
}
qualified_name::qualified_name(const std::string& local)
 : ns(), local(local)
{
}
qualified_name::qualified_name(const std::string& local, const std::string& ns)
 : ns(ns), local(local)
{
}

bool qualified_name::operator==(const qualified_name& name) const
{
    return std::tie(ns, local) == std::tie(name.ns, name.local);
}
bool qualified_name::operator!=(const qualified_name& name) const
{
    return std::tie(ns, local) != std::tie(name.ns, name.local);
}
bool qualified_name::operator<(const qualified_name& name) const
{
    return std::tie(ns, local) < std::tie(name.ns, name.local);
}

}
