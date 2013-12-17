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
 * basic_element.cpp
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#include "dom/basic_element.h"

namespace dom
{

basic_element_t::basic_element_t(const qualified_name& name)
 : element_name(name)
{
}

qualified_name basic_element_t::name() const
{
    return element_name;
}

boost::optional<std::string> basic_element_t::get_attribute(const qualified_name& name) const
{
    auto it = attributes.find(name);
    if(it != end(attributes))
        return boost::make_optional(it->second);
    return {};
}

void basic_element_t::set_attribute(const qualified_name& name, const boost::optional<std::string>& value)
{
    if(value)
        attributes[name] = *value;
    else
        attributes.erase(name);
}

node basic_element_t::clone(bool deep)
{
    auto dup = std::make_shared<basic_element_t>(*this);
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

basic_element_t::~basic_element_t()
{
}

}
