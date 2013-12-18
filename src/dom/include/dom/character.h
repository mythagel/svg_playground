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
 * character.h
 *
 *  Created on: 2013-12-16
 *      Author: nicholas
 */

#ifndef DOM_CHARACTER_H_
#define DOM_CHARACTER_H_
#include <memory>
#include <string>
#include "node.h"

namespace dom
{

struct character_t;
using character = std::shared_ptr<character_t>;

struct character_t : node_t
{
    std::string data;

    character_t(const std::string& data);

    virtual node append(const node&) override;
    virtual node insert(const node&, const node&) override;
    virtual node erase(const node&) override;
    virtual node clone(bool) override;

    virtual ~character_t();
};

}

#endif /* DOM_CHARACTER_H_ */
