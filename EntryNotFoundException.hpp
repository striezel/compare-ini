/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2014  Thoronador

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

#ifndef ENTRYNOTFOUNDEXCEPTION_HPP
#define ENTRYNOTFOUNDEXCEPTION_HPP

#include <exception>
#include <string>

class EntryNotFoundException : public std::exception
{
  public:
    /// constructor
    EntryNotFoundException(const std::string& n);


    /// destructor
    virtual ~EntryNotFoundException() throw() {}


    /** \brief returns the explanatory string
     * \return pointer to a NUL-terminated, explanatory C-string
     */
    virtual const char* what() const throw();
  private:
    std::string m_Explain;
}; //class

#endif // ENTRYNOTFOUNDEXCEPTION_HPP
