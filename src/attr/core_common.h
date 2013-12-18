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
 * core_common.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ATTR_CORE_COMMON_H_
#define ATTR_CORE_COMMON_H_
#include <boost/optional.hpp>
#include "typed_attribute.h"
#include <string>
#include <network/uri.hpp>
#include "../types/stringlist.h"

namespace svg
{
namespace attr
{

struct core_common
{
    boost::optional<std::string> id;
    boost::optional<network::uri> base;
    boost::optional<std::string> lang;
    boost::optional<std::string> _class;
    boost::optional<types::stringlist_t> role;
    boost::optional<types::stringlist_t> rel;
    boost::optional<types::stringlist_t> rev;
    boost::optional<types::stringlist_t> _typeof;
    boost::optional<std::string> content;
    boost::optional<std::string> datatype;
    boost::optional<std::string> resource;
    boost::optional<types::stringlist_t> about;
    boost::optional<types::stringlist_t> property;
};

void map_attributes(core_common& attr, attribute_map_t& attrs);

}
}

#endif /* ATTR_CORE_COMMON_H_ */
