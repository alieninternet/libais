/* $Id$
 * Version and Compile information
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

namespace AISutil {
   namespace Version {
      extern const char *programName;			// Program name
      extern const unsigned short versionMajor;		// Version major number
      extern const unsigned short versionMinor;		// Version minor number
      extern const char *version;			// Version identity
      extern const unsigned char libVersion;		// Library API version
      extern const unsigned char libRevision;		// Library API revision
      extern const unsigned char libAge;		// Library API age
      extern const char *bugsEmail;			// Bug report e-mail
   };
};
   
#endif // _INCLUDE_LIBAISUTIL_VERSION_H_
   
