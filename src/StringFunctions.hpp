/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2011, 2022  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#ifndef STRINGFUNCTIONS_HPP
#define STRINGFUNCTIONS_HPP

#include <string>

/** \brief Removes all leading and trailing spaces and (horizontal) tabulators
 * from the given string.
 *
 * \param str1  the affected string
 */
void trim(std::string& str1);

/** \brief Tries to remove the bracket pair surrounding the rest of the string,
 * if they match.
 *
 * \param expr  the string
 * \return Returns true, if something was removed, false otherwise.
 */
bool removeEnclosingBrackets(std::string& expr);

#endif // STRINGFUNCTIONS_HPP
