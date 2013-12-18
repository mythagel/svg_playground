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
 * qualified_name.cpp
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#include "dom/qualified_name.h"
#include <tuple>
#include <stdexcept>

namespace dom
{

namespace
{
constexpr auto XML_NS = "http://www.w3.org/XML/1998/namespace";
constexpr auto XLINK_NS = "http://www.w3.org/1999/xlink";
constexpr auto SVG_NS = "http://www.w3.org/2000/svg";
}

void qualified_name::assign(const std::string& local, const std::string& ns)
{
    local_ = local;
    if(ns == XML_NS)
        ns_ = ns_e::xml;
    else if(ns == XLINK_NS)
        ns_ = ns_e::xlink;
    else if(ns == SVG_NS)
        ns_ = ns_e::svg;
    else
        ns_ = ns;
}

qualified_name::qualified_name()
{
}
qualified_name::qualified_name(const std::string& local)
 : ns_(), local_(local)
{
    assign(local, {});
}
qualified_name::qualified_name(const std::string& local, const std::string& ns)
 : ns_(ns), local_(local)
{
    assign(local, ns);
}

std::string qualified_name::ns() const
{
    struct map : boost::static_visitor<std::string>
    {
        std::string operator()(ns_e ns) const
        {
            switch(ns)
            {
                case ns_e::xml:
                    return XML_NS;
                case ns_e::xlink:
                    return XLINK_NS;
                case ns_e::svg:
                    return SVG_NS;
            }
            throw std::logic_error("Unmapped namespace");
        }

        std::string operator()(const std::string &ns) const
        {
            return ns;
        }
    };
    return boost::apply_visitor(map{}, ns_);
}
std::string qualified_name::local() const
{
    return local_;
}

bool qualified_name::operator==(const qualified_name& name) const
{
    return std::tie(ns_, local_) == std::tie(name.ns_, name.local_);
}
bool qualified_name::operator!=(const qualified_name& name) const
{
    return std::tie(ns_, local_) != std::tie(name.ns_, name.local_);
}
bool qualified_name::operator<(const qualified_name& name) const
{
    return std::tie(ns_, local_) < std::tie(name.ns_, name.local_);
}

}
