/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2014, 2022, 2024  Dirk Stolle

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
      /** \brief Constructs a new exception object.
       *
       * \param name    name of the entry that was not found
       */
    explicit EntryNotFoundException(const std::string& name);


    virtual ~EntryNotFoundException() throw() {}


    /** \brief Returns the explanatory string.
     * \return pointer to a NUL-terminated, explanatory C-string
     */
    virtual const char* what() const throw();
  private:
    std::string m_Explain;
}; // class

#endif // ENTRYNOTFOUNDEXCEPTION_HPP
