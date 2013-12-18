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
 * func_iri.h
 *
 *  Created on: 2013-12-18
 *      Author: nicholas
 */

#ifndef PARSERS_FUNC_IRI_H_
#define PARSERS_FUNC_IRI_H_
#include <network/uri.hpp>

namespace svg
{
namespace types
{
namespace parsers
{

bool parse_func_iri(const char* c, const char* const end, network::uri& uri);

}
}
}

#endif /* PARSERS_FUNC_IRI_H_ */
