#pragma once

#ifndef __ANGLE_HELPER_H__
#define __ANGLE_HELPER_H__

#define PI  3.14159
#define PI2 6.28318

#define TO_RAD (PI / 180.0)
#define TO_DEG (180.0 / PI)

#include "Direction.h"

namespace Arc
{
	class AngleHelper
	{
	public:

		static inline float toRad( int deg ) { return (float)( deg * TO_RAD ); }
		static inline float toDeg( int rad ) { return (float)( rad * TO_DEG ); }

		static inline float toRad( float deg ) { return (float)( deg * TO_RAD ); }
		static inline float toDeg( float rad ) { return (float)( rad * TO_DEG ); }

		static inline double toRad( double deg ) { return (double)( deg * TO_RAD ); }
		static inline double toDeg( double rad ) { return (double)( rad * TO_DEG ); }

		static Direction angleDegToDirFour ( float angle );
		static Direction angleDegToDirEight( float angle );

		static inline Direction angleRadToDirFour ( float angle ) { return AngleHelper::angleDegToDirFour(AngleHelper::toDeg(angle)); }
		static inline Direction angleRadToDirEight( float angle ) { return AngleHelper::angleDegToDirEight(AngleHelper::toDeg(angle)); }

	}; // static class AngleHelper

} // namespace Arc

#endif // __ANGLE_HELPER_H__