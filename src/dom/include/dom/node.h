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
 * node.h
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#ifndef DOM_NODE_H_
#define DOM_NODE_H_
#include <memory>
#include <vector>

namespace dom
{

struct node_t;
using node = std::shared_ptr<node_t>;

struct node_t : std::enable_shared_from_this<node_t>
{
    node parent;
    std::vector<node> children;

    virtual node append(const node& child);
    virtual node insert(const node& child, const node& ref);
    virtual node erase(const node& child);
    virtual node clone(bool deep) =0;

    virtual ~node_t();
};

}

#endif /* DOM_NODE_H_ */
