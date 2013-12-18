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
#include <stdexcept>

namespace svg
{
namespace element
{

svg::svg()
{
    map_attributes(*this, attributes);
}

svg::svg(const svg& o)
{
    map_attributes(*this, attributes);
}

dom::qualified_name svg::name() const
{
    return {"svg", "http://www.w3.org/2000/svg"};
}

dom::node svg::clone(bool deep)
{
    auto dup = std::make_shared<svg>(*this);
    dup->parent.reset();

    if(deep)
    {
        for(auto& child : dup->children)
            child = child->clone(deep);
    }
    else
    {
        dup->children.clear();
        return dup;
    }

    return dup;
}

boost::optional<std::string> svg::get_attribute(const dom::qualified_name& name) const
{
//    auto it = attributes.find(name);
//    if(it == end(attributes))
//        throw std::runtime_error("unknown attribute");

//    return (*it)->get();
}
void svg::set_attribute(const dom::qualified_name& name, const boost::optional<std::string>& value)
{
//    auto it = attributes.find(name);
//    if(it == end(attributes))
//        throw std::runtime_error("unknown attribute");

//    (*it)->set(value);
}

svg::~svg()
{
}

}
}
