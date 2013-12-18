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
 * element.h
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#ifndef DOM_ELEMENT_H_
#define DOM_ELEMENT_H_
#include <memory>
#include <string>
#include "node.h"
#include "qualified_name.h"
#include <boost/optional.hpp>

namespace dom
{

struct element_t;
using element = std::shared_ptr<element_t>;

struct element_t : node_t
{
    virtual qualified_name name() const =0;
    virtual boost::optional<std::string> get_attribute(const qualified_name& name) const =0;
    virtual void set_attribute(const qualified_name& name, const boost::optional<std::string>& value) =0;

    virtual ~element_t();
};

}

#endif /* DOM_ELEMENT_H_ */
