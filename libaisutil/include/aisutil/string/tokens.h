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

/*! \file
 * \brief String tokeniser routines
 * 
 * This file contains routines designed to break \e tokens out of a string.
 */

# include <aisutil/string/string.h>

namespace AIS {
   namespace Util {
      /*!
       * \brief String tokeniser class for the String class
       * 
       * \ingroup Strings
       */
      class StringTokens : public String {
       protected:
	 //! Our position, usually pointing to the first char of the next token
	 size_type position;
	 
       public:
	 /*! 
	  * \brief Constructor
	  * 
	  * Create a new string, ready to be tokenised!
	  * 
	  * \param string A string to hold
	  * \param pos A location within the \p string to begin tokenisation.
	  *    If this is not provided, tokenisation will begin at the start
	  *    of the string.
	  */ 
	 template <class T>
	   StringTokens(const T& string,
			const String::size_type pos = 0)
	     : String(string),
	       position(pos)
	     {};
	 
	 //! Destructor
	 ~StringTokens(void)
	   {};
      
	 /*!
	  * \brief Any more tokens left?
	  * 
	  * By checking the position indicator, we can tell if there are any
	  * more tokens left. At the very least, there may be one token left
	  * if the position is not located at the end of the string.
	  * 
	  * \return Whether there are any more tokens left
	  * \retval true There are more tokens
	  * \retval false There are no more tokens left
	  */
	 const bool hasMoreTokens(void) const
	   { return (position < length()); };
	 
	 /*!
	  * \brief Count the number of tokens
	  *
	  * Count the total number of tokens contained within the string,
	  * looking for a space or a tab delimiter.
	  * 
	  * \return The total number of tokens contained within the string
	  */
	 const unsigned int countTokens(void) const;
	 
	 /*!
	  * \brief Count the number of tokens, using the given \p delimiter
	  * 
	  * Count the total number of tokens contained within the string,
	  * using the given \p delimiter as the delimiter between the tokens.
	  * 
	  * \return The total number of tokens contained within the string
	  */
	 const unsigned int countTokens(const char delimiter) const;
	 
	 /*! 
	  * \brief Get the next token
	  *
	  * Return the next token, delimitered by either a space or a tab. The
	  * position indicator will be moved to point to the beginning of the
	  * next token following this one.
	  * 
	  * \return The next token
	  */
	 const String nextToken(void);
	 
	 /*!
	  * \brief Get the next token, using the given \p delimiter
	  * 
	  * Return the next token, delimitered by the given \p delimiter. The
	  * position indicator will be moved to point to the beginning of the
	  * next token following this one.
	  * 
	  * \return The next token
	  */
	 const String nextToken(const char delimiter);
	 
	 //! Get next IRC style token
	 const String nextColonToken(void);
	 
	 /*!
	  * \brief Get the rest of the data from the string
	  * 
	  * This will take the \e rest of the data left in the string and
	  * return it as a new string. It will not displace the position
	  * indicator, so any further nextToken() calls will act as normal.
	  * 
	  * \return Everything from the last point a token was taken from, up
	  *    up until the end of the string
	  */
	 const String rest(void) const
	   { return substr(position, length() - position); };
      }; // class StringTokens
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_STRING_STRINGTOKENS_H_
