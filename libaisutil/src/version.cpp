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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "aisutil/version.h"

// This is temporary
#define BUILD_STRING "fix-me-please"

namespace AISutil {
   namespace Version {
      // Program name
      const char* const programName = LIBAISUTIL_VERSION_NAME;
      
      // Program version numbers (raw)
      const unsigned short versionMajor = LIBAISUTIL_VERSION_MAJOR;
      const unsigned short versionMinor = LIBAISUTIL_VERSION_MINOR;

      // Version information (program name and version number, in its entirity)
      const char* const version = PACKAGE "-" LIBAISUTIL_VERSION_STRING;
      
      // Library version information (raw)
      const unsigned char libVersion = LIBAISUTIL_LIB_VERSION;
      const unsigned char libRevision = LIBAISUTIL_LIB_REVISION;
      const unsigned char libAge = LIBAISUTIL_LIB_AGE;
      
      // E-mail address to where bug reports should wind up
      const char* const bugsEmail = PACKAGE_BUGREPORT;
   };
};

