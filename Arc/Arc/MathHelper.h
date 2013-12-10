#pragma once

#ifndef __ARC_MATH_HELPER_H__
#define __ARC_MATH_HELPER_H__

#include <cmath>

namespace Arc
{
	class MathHelper
	{
	public:

		static float floor  (float value, int accuracy);
		static float nearest(float value, int accuracy);
		static float ceil   (float value, int accuracy);

		static double floor  (double value, int accuracy);
		static double nearest(double value, int accuracy);
		static double ceil   (double value, int accuracy);

		template <class Number>
		static inline Number clamp(Number value, Number min, Number max) 
		{
			return ( ( value > max ) ? max : ( ( value < min ) ? min : value ) ); 
		}

		template <class Number>
		static inline int sign( Number value ) 
		{ 
			return ( value > 0 ? 1 : ( value < 0 ? -1 : 0 ) );
		}

		template <class Number>
		static inline Number approach( Number value, Number target, Number speed )
		{
			return ( ( value > target ) ? max( value - speed, target ) : min( value + speed, target ) );
		}

		template <class Number>
		static inline Number reduce( Number value, Number speed ) 
		{
			return ( ( value > 0 ) ? max( value - speed, 0 ) : min( value + speed, 0 ) ); 
		}

		template <class Number>
		static inline bool between( Number value, Number min, Number max ) 
		{ 
			return ( value >= min && value <= max); 
		}

		template <class Number>
		static inline Number lerp( Number start, Number end, float fraction) 
		{
			return (Number)( start + (end - start) * fraction );
		}

		/* Calculates a hermite interpolation
		 *
		 * Source: http://paulbourke.net/miscellaneous/interpolation/
		 *
		 * Tension: 1 is high, 0 normal, -1 is low
		 * Bias: 0 is even, positive is towards first segment, negative towards the other
		 */
		template <class Number>
		static Number hermite( Number x0, Number x1, Number x2, Number x3, Number mu, double tension, double bias);

	}; // class MathHelper

} // namespace Arc

#endif // __ARC_MATH_HELPER_H__