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
 * svg.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef ELEMENT_SVG_H_
#define ELEMENT_SVG_H_
#include "dom/element.h"
#include "../attr/typed_attribute.h"
#include "../attr/svg.h"

namespace svg
{
namespace element
{

struct svg : dom::element_t, attr::svg
{
    attr::attribute_map_t attributes;

    svg();
    svg(const svg& o);

    virtual dom::qualified_name name() const override;
    virtual dom::node clone(bool deep) override;

    virtual boost::optional<std::string> get_attribute(const dom::qualified_name& name) const override;
    virtual void set_attribute(const dom::qualified_name& name, const boost::optional<std::string>& value) override;

    virtual ~svg();
};

}
}

#endif /* ELEMENT_SVG_H_ */
