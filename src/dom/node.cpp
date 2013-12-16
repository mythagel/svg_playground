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
 * node.cpp
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#include "node.h"
#include <algorithm>

namespace dom
{

node node_t::append(const node& child)
{
    auto it = std::find(begin(children), end(children), child);
    if(it != end(children))
        children.erase(it);

    child->parent = shared_from_this();
    children.push_back(child);
    return child;
}

node node_t::insert(const node& child, const node& ref)
{
    auto it = std::find(begin(children), end(children), ref);

    child->parent = shared_from_this();
    children.insert(it, child);
    return child;
}

node node_t::erase(const node& child)
{
    auto it = std::find(begin(children), end(children), child);
    if(it != end(children))
        children.erase(it);

    child->parent.reset();
    return child;
}

node_t::~node_t()
{
}

}
