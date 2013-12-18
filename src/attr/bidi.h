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
 * bidi.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ATTR_BIDI_H_
#define ATTR_BIDI_H_
#include <boost/optional.hpp>
#include "typed_attribute.h"
#include "../types/bidi.h"

namespace svg
{
namespace attr
{

struct bidi
{
    boost::optional<types::bidi::direction> direction;
    boost::optional<types::bidi::unicode_bidi> unicode_bidi;
};

void map_attributes(bidi& attr, attribute_map_t& attrs);

}
}

#endif /* ATTR_BIDI_H_ */
