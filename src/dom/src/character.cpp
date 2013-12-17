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
 * character.cpp
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#include "dom/character.h"
#include <stdexcept>

namespace dom
{

character_t::character_t(const std::string& data)
 : data(data)
{
}

node character_t::append(const node&)
{
    throw std::runtime_error("character node cannot have children.");
}

node character_t::insert(const node&, const node&)
{
    throw std::runtime_error("character node cannot have children.");
}

node character_t::erase(const node&)
{
    throw std::runtime_error("character node cannot have children.");
}

node character_t::clone(bool)
{
    auto dup = std::make_shared<character_t>(*this);
    dup->parent.reset();
    return dup;
}

character_t::~character_t()
{
}

}
