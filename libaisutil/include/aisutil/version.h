/* $Id$
 * 
 * Copyright (c) 2002,2003 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_VERSION_H_
# define _INCLUDE_LIBAISUTIL_VERSION_H_ 1

/*! \file
 * \brief Version information
 *
 * This file contains a list of \c extern symbols to assist in obtaining
 * various version information from the library.
 */

namespace AIS {
   namespace Util {
      /*!
       * \brief Version and compile-time information
       * 
       * This version information is for you to access in your own programs.
       * It's used quite often as supplementary and/or extended information
       * about programs which use the library in order to assist end users
       * in debugging faults. Software using an older version of the library
       * installed on the system can be easily identified, should there be a
       * problem with that particular version.
       */
      namespace Version {
	 //! The library's name
	 extern const char* const libraryName;
	 
	 //! The major version number of the library
	 extern const unsigned short versionMajor;
	 
	 //! The minor version number of the library
	 extern const unsigned short versionMinor;
	 
	 /*!
	  * \brief A string identifying the library and its version
	  * 
	  * This is a string including the library's name and its version
	  * number in the 'preferred' display format.
	  */
	 extern const char* const version;
	 
	 extern const unsigned char libVersion;	//!< Library API version
	 extern const unsigned char libRevision;//!< Library API revision
	 extern const unsigned char libAge;	//!< Library API age
	 
	 /*!
	  * \brief Bug report e-mail address
	  * 
	  * This is an email address to contact to submit bug reports about
	  * the library. No support can be provided for software using the
	  * library at this address, though.
	  */
	 extern const char* const bugsEmail;
      }; // namespace Version
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_LIBAISUTIL_VERSION_H_
   
