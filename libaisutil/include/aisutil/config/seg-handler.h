/* $Id$
 *
 * Copyright (c) 2004 Alien Internet Services
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

#ifndef _INCLUDE_LIBAISUTIL_CONFIG_SEG_HANDLER_H_
# define _INCLUDE_LIBAISUTIL_CONFIG_SEG_HANDLER_H_ 1

# include <aisutil/config/handler.h>

namespace AIS {
   namespace Util {
      namespace Config {
	 /*!
	  * \brief Configuration data segment handler functoid base class
	  *
	  * This functiod is designed for handling transitions into (and
	  * subsequently out of) configuration segments.
	  * 
	  * Normally, you will not need to use one of these, because common
	  * segment handlers are provided by the library. However, there are
	  * instances where you need a fairly intuitive interface to a
	  * specific variable and a fake-segment with the data inside being
	  * processed in a specific way is often a great way do it from a
	  * user's perspective.
	  * 
	  * Segment handlers can serve two purposes:
	  *   - Initialisation of something (such as a variable) prior to
	  *     the configuration process continuing to load.
	  *   - The handling of the data within the two curly-braces that
	  *     contain that particular segment.
	  * 
	  * In the case of the latter, you must have a plan in effect for
	  * handling any nested segments (they are now your responsibility).
	  * 
	  * You must return with the position indicator pointing at the
	  * position of the terminating curly-brace ('}') of that segment.
	  */
	 class SegmentHandler : public Handler {
	  protected:
	    //! Default constructor
	    SegmentHandler(void)
	      {};

	  public:
	    //! Destructor
	    virtual ~SegmentHandler(void)
	      {};


	    //! The handler
	    virtual const bool handle(void)
	      { return false; /* !!! */ };
	 }; // class SegmentHandler
      }; // namespace Config
   }; // namespace Util
}; // namespace AIS

#endif // _INCLUDE_LIBAISUTIL_CONFIG_SEG_HANDLER_H_
