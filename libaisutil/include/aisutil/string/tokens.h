/* $Id$
 * 
 * Copyright (c) 1999,2000,2002,2003 Alien Internet Services
 *
 * This file is a part of LibAISutil.
 * 
 * LibAISutil is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * LibAISutil is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with LibAISutil; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _INCLUDE_LIBAISUTIL_STRING_STRINGTOKENS_H_
# define _INCLUDE_LIBAISUTIL_STRING_STRINGTOKENS_H_ 1

# include <aisutil/string/string.h>


namespace AISutil {
   //! String tokeniser class for the String class
   class StringTokens : public String {
    private:
      //! Our position, usually pointing to the first char of the next token
      size_type position;
      
    public:
      //! Constructor
      template <class T>
	StringTokens(const T& s, 
		     const String::size_type p = 0)
	: String(s),
          position(p)
	{};
      
      //! Destructor
      ~StringTokens(void)
	{};
      
      //! Any more tokens left?
      bool hasMoreTokens(void) const
	{ return (position < length()); };

      //! Count the number of tokens
      unsigned int countTokens(void) const;
      
      //! Count the number of tokens, using the given delimiter
      unsigned int countTokens(const char delimiter) const;
      
      //! Get the next token
      String nextToken(void);
      
      //! Get the next token, using the given delimiter
      String nextToken(const char delimiter);
      
      //! Get next IRC style token
      String nextColonToken(void);
      
      //! Get the rest of the line (without displacing the current position)
      String rest(void) const
	{ return substr(position, length() - position); };
   }; // class StringTokens
}; // namespace AISutil

#endif // _INCLUDE_LIBAISUTIL_STRING_STRINGTOKENS_H_
