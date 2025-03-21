/* $Id$
 * 
 * Copyright (c) 2003,2004 Alien Internet Services
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

#define TEST_RETURN_PASS	0
#define TEST_RETURN_FAIL	1
#define TEST_RETURN_IGNORE	77	// AutoMake will ignore this return

#include <iostream>

#define TEST_VERBOSE \
     (argc > 1)

#define TEST_STATUS(x) \
     if (TEST_VERBOSE) { \
	std::cout << x << std::endl; \
     }

#define TEST_FAIL_IF(x) \
     if (x) { \
	return TEST_RETURN_FAIL; \
     }

#define TEST_IGNORE_IF(x) \
     if (x) { \
	return TEST_RETURN_IGNORE; \
     }

#define TEST_ASSERT(x) \
     if (!(x)) { \
	return TEST_RETURN_FAIL; \
     }

#define TEST_END \
     TEST_STATUS("All tests were successful"); \
     return TEST_RETURN_PASS
   
