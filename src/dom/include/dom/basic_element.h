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
 * basic_element.h
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#ifndef BASIC_ELEMENT_H_
#define BASIC_ELEMENT_H_
#include "element.h"
#include "qualified_name.h"
#include <map>
#include <string>
#include <boost/optional.hpp>

namespace dom
{

struct basic_element_t : element_t
{
    qualified_name element_name;
    std::map<qualified_name, std::string> attributes;

    basic_element_t(const qualified_name& name);

    virtual qualified_name name() const override;
    virtual boost::optional<std::string> get_attribute(const qualified_name& name) const override;
    virtual void set_attribute(const qualified_name& name, const boost::optional<std::string>& value) override;
    virtual node clone(bool deep) override;

    virtual ~basic_element_t();
};

}

#endif /* BASIC_ELEMENT_H_ */
