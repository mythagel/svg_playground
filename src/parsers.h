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
 * parsers.h
 *
 *  Created on: 2013-12-05
 *      Author: nicholas
 */

#ifndef PARSERS_H_
#define PARSERS_H_

namespace svg
{
namespace parser
{

bool ws_p(const char c);
bool parse_whitespace(const char*& c, const char* const end);

bool number_p(const char c);
bool parse_number(const char*& c, const char* const end, float& x);

bool parse_comma_wsp(const char*& c, const char* const end);

}
}

#endif /* PARSERS_H_ */
