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
 * qualified_name.h
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#ifndef DOM_QUALIFIED_NAME_H_
#define DOM_QUALIFIED_NAME_H_
#include <string>
#include <boost/variant.hpp>

namespace dom
{

class qualified_name
{
private:
    enum class ns_e
    {
        xml,
        xlink,
        svg
    };
    boost::variant<ns_e, std::string> ns_;
    std::string local_;

    void assign(const std::string& local, const std::string& ns);
public:
    qualified_name();
    explicit qualified_name(const std::string& local);
    qualified_name(const std::string& local, const std::string& ns);

    std::string ns() const;
    std::string local() const;

    bool operator==(const qualified_name& name) const;
    bool operator!=(const qualified_name& name) const;
    bool operator<(const qualified_name& name) const;
};

}

#endif /* DOM_QUALIFIED_NAME_H_ */
