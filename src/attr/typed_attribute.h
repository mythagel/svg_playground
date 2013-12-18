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
 * typed_attribute.h
 *
 *  Created on: 2013-12-17
 *      Author: nicholas
 */

#ifndef ATTR_TYPED_ATTRIBUTE_H_
#define ATTR_TYPED_ATTRIBUTE_H_
#include <boost/optional.hpp>
#include <string>
#include <functional>
#include <sstream>
#include "../make_unique.h"
#include <map>
#include "dom/qualified_name.h"

namespace svg
{
namespace attr
{

/* Generic string access to typed (member variable)
 * attributes */
struct typed_attribute
{
    virtual boost::optional<std::string> get() const = 0;
    virtual void set(const boost::optional<std::string>& value) =0;
    virtual ~typed_attribute();
};

/* Typed attribute whose storage is a reference to an
 * optional attribute elsewhere. */
template <typename T>
struct optional_typed_attribute_ref : typed_attribute
{
    std::reference_wrapper<boost::optional<T>> value;

    optional_typed_attribute_ref(boost::optional<T>& value)
     : value(std::ref(value))
    {
    }

    virtual boost::optional<std::string> get() const override
    {
        auto& v = value.get();
        if(!v)
            return boost::none;
        std::ostringstream s;
        s << *v;
        return { s.str() };
    }
    virtual void set(const boost::optional<std::string>& new_value) override
    {
        auto& v = value.get();
        if(new_value)
        {
            std::istringstream s(*new_value);
            if(!v)
                v = boost::make_optional(T());
            s >> *v;
        }
        else
        {
            v = boost::none;
        }
    }

    virtual ~optional_typed_attribute_ref()
    {
    }
};

template <>
struct optional_typed_attribute_ref<std::string> : typed_attribute
{
    std::reference_wrapper<boost::optional<std::string>> value;

    optional_typed_attribute_ref(boost::optional<std::string>& value)
     : value(std::ref(value))
    {
    }

    virtual boost::optional<std::string> get() const override
    {
        return value;
    }
    virtual void set(const boost::optional<std::string>& new_value) override
    {
        value.get() = new_value;
    }

    virtual ~optional_typed_attribute_ref()
    {
    }
};

template<typename T>
auto make_attr(boost::optional<T>& value) -> std::unique_ptr<optional_typed_attribute_ref<T>>
{
    return make_unique<optional_typed_attribute_ref<T>>(value);
}

using attribute_map_t = std::map<std::string, std::unique_ptr<typed_attribute>>;

}
}

#endif /* ATTR_TYPED_ATTRIBUTE_H_ */
