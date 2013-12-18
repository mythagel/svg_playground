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
 * core.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ATTR_CORE_H_
#define ATTR_CORE_H_
#include <boost/optional.hpp>
#include "typed_attribute.h"
#include "core_common.h"
#include "../types/core.h"

namespace svg
{
namespace attr
{

struct core
{
    core_common common;

    boost::optional<types::core::space> space;
};

void map_attributes(core& attr, attribute_map_t& attrs);

}
}

#endif /* ATTR_CORE_H_ */
