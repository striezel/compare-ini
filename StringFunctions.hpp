/*
 -------------------------------------------------------------------------------
    This file is part of the Morrowind Tools Project.
    Copyright (C) 2011 Thoronador

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

#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <string>

/* removes all leading and trailing spaces and (horizontal) tabulators from the
   given string

   parameters:
       str1 - the affected string
*/
void trim(std::string& str1);

/*tries to remove the bracket pair surrounding the rest of the string, if they
  match. Returns true, if something was removed, false otherwise.

  parameters:
      expr - the string
*/
bool removeEnclosingBrackets(std::string& expr);

#endif // UTILITYFUNCTIONS_H
