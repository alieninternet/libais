/* $Id$
 * 
 * Copyright (c) 1997,2003 Alien Internet Services
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

#ifndef _INCLUDE_AISUTIL_PEAKCOUNT_H_
# define _INCLUDE_AISUTIL_PEAKCOUNT_H_ 1

/*! \file
 * \brief A simple floating counter with an associated peak value
 * 
 * Basic floating counter with peak value template
 */ 

# include <algorithm>

namespace AIS {
   namespace Util {
      /*!
       * \brief Basic floating counter with peak value template
       * 
       * It's often required to maintain a floating counter for statistical
       * reasons, such as the number of people in a room. This number can
       * rise and fall, and often the highest value (the "peak" value) is
       * useful to know.
       * 
       * This template feigns the type you give it (normally an integer or
       * a floating point number) while adding a peak value you can access.
       * 
       * Note that the memory used per instance of this class will be exactly
       * twice the size of the given type.
       */
      template < class T > class PeakCount {
       public:
	 //! The type used for the value and peak numbers
	 typedef T value_type;
	 
       private:	
	 //! My type
	 typedef PeakCount < T > my_type;
	 
	 //! The current value
	 T value;
	 
	 //! The peak value
	 T peak;
	 
       public:
	 /*!
	  * \brief Constructor
	  *
	  * Create the new counter, optionally giving it a pre-existing value
	  * and also a peak value if necessary. Note that if the peak value
	  * given is less than the current value given, the current value
	  * will over-ride the given peak value.
	  * 
	  * \param _value The current value
	  * \param _peak The peak value
	  */
	 PeakCount(const T& _value = 0,
		   const T& _peak = 0)
	   : value(_value),
	     peak(std::max(_value, _peak))
	   {};

	 
	 /*!
	  * \brief Return the current value
	  * 
	  * \return The current value
	  */
	 const T& getValue(void) const
	   { return value; };
	 
	 /*!
	  * \brief Return the peak value
	  * 
	  * \return The highest value known (the peak)
	  */
	 const T& getPeak(void) const
	   { return peak; };
	 
	 /*!
	  * \brief Return the current value in its native form
	  * 
	  * In order to act like the given type, this class can convert back
	  * to that type naturally without having to always call getValue()
	  * explicitly.
	  * 
	  * \return The current value
	  */
	 operator T(void) const
	   { return value; };
	 
	 
	 /*!
	  * \brief Addition operator
	  * 
	  * If the number given (\p rhs) will shift the \a value to that
	  * greater than the current \a peak value, the \a peak value will be
	  * changed to equal the \a value.
	  * 
	  * \param rhs The number to add to the \a value
	  * \return The result of the addition
	  */
	 const my_type operator+(const T& rhs)
	   {	
	      my_type newValue(*this);
	      if ((newValue.value += rhs) > newValue.peak) {
		 newValue.peak = newValue.value;
	      }
	      return newValue;
	   };
	 
	 /*!
	  * \brief Addition operator
	  * 
	  * Note that adding two counters together will combine both
	  * the values and peak values together, in effect merging the
	  * two counters.
	  * 
	  * \param rhs Another counter to add to this counter
	  * \return The result of the addition
	  */
	 const my_type operator+(const my_type& rhs)
	   { return my_type(value + rhs.value, peak + rhs.peak); };
	 
	 /*!
	  * \brief Addition assignment operator
	  * 
	  * \param rhs The number to add to the \a value
	  * \return A reference to this instance after the addition
	  */
	 const my_type& operator+=(const T& rhs)
	   {
	      if ((value += rhs) > peak) {
		 peak = value;
	      }
	      return (*this);
	   };
	 
	 /*!
	  * \brief Addition assignment operator
	  * 
	  * \param rhs The counter to add to this one
	  * \return A reference to this instance after the addition
	  */
	 const my_type& operator+=(const my_type& rhs)
	   {
	      value += rhs.value;
	      peak += rhs.peak;
	      return (*this);
	   };


	 /*!
	  * \brief Prefix increment operator
	  * 
	  * \return A reference to this instance after the addition
	  */
	 const my_type& operator++(void)
	   { return ((*this) += T(1)); };
	 
	 /*!
	  * \brief Postfix increment operator
	  * 
	  * \return A copy of this instance as it was before the addition
	  */
	 const my_type operator++(int i)
	   {
	      my_type oldValue(*this);
	      ++(*this);
	      return oldValue;
	   };
	 
	 
	 /*!
	  * \brief Subtraction operator
	  *
	  * \param rhs The number to subtract from the \a value
	  * \return The result of the addition
	  */
	 const my_type operator-(const T& rhs)
	   {
	      my_type newValue(*this);
	      newValue.value -= rhs;
	      return newValue;
	   };
	 
	 /*!
	  * \brief Subtraction operator
	  *
	  * \param rhs Another counter to subtract from this one
	  * \return The result of the addition
	  */
	 const my_type operator-(const my_type& rhs)
	   {
	      return my_type(value - rhs.value, peak - rhs.peak);
	   };
	 
	 /*!
	  * \brief Subtraction assignment operator
	  * 
	  * \param rhs The number to subtract from the \a value
	  * \return A reference to this instance after the subtraction
	  */
	 const my_type& operator-=(const T& rhs)
	   {
	      value -= rhs;
	      return (*this);
	   };
	 
	 /*!
	  * \brief Subtraction assignment operator
	  * 
	  * \param rhs Another counter to subtract from this one
	  * \return A reference to this instance after the subtraction
	  */
	 const my_type& operator-=(const my_type& rhs)
	   {
	      value -= rhs.value;
	      peak -= rhs.peak;
	      return (*this);
	   };


	 /*!
	  * \brief Prefix decrement operator
	  * 
	  * \return A reference to this instance after the subtraction
	  */
	 const my_type& operator--(void)
	   {
	      --value;
	      return (*this);
	   };
	 
	 /*!
	  * \brief Postfix decrement operator
	  * 
	  * \return A copy of this instance as it was before the subtraction
	  */
	 const my_type operator--(int i)
	   {
	      my_type oldValue(*this);
	      --value;
	      return oldValue;
	   };
	 
	 
	 /*!
	  * \brief Assignment operator
	  * 
	  * \return A reference to this instance after the assignment
	  */
	 const my_type& operator=(const my_type& rhs)
	   {
	      value = rhs.value;
	      return (*this);
	   };
      }; // struct PeakCount
   }; // namespace Util
}; // namespace AIS
   
#endif // _INCLUDE_AISUTIL_PEAKCOUNT_H_
