#pragma once

#ifndef __ARC_ORIGIN_H__
#define __ARC_ORIGIN_H__

#include "Common.h"
#include "ManagedObject.h"

#include "OriginLocation.h"

namespace Arc
{
	class Origin
		: public ManagedObject
	{
	protected:

		Point 
			_origin;

		Size
			_size;

		OriginLocation
			_originLocation;

		virtual void updateOrigin( void );

	public:

		static const Origin
			ZERO;

		inline Origin( Point origin, Size size = Size::ZERO )
			: _origin(origin),
			  _size(size),
			  _originLocation(ORIGIN_LOCATION_MANUAL)
		{ }

		inline Origin( OriginLocation originLocation, Size size = Size::ZERO )
			: _origin(),
			  _size(size),
			  _originLocation(originLocation)
		{
			updateOrigin();
		}

		virtual inline ~Origin( void ) { }

		virtual inline string toString( void ) const { return "Origin"; }

		virtual inline void setPoint( Point origin )
		{ 
			_origin = origin; 
			_originLocation = ORIGIN_LOCATION_MANUAL;
		}

		virtual inline void setLocation( OriginLocation location )
		{
			_originLocation = location;
			updateOrigin();
		}

		virtual inline Point getPoint( void ) const { return _origin; }
		virtual inline OriginLocation getLocation( void ) const { return _originLocation; }

		virtual inline Size getSize( void ) const { return _size; }
		virtual inline void setSize( Size size ) { _size = size; }

	}; // class Origin

} // namespace Arc

#endif // __ARC_ORIGIN_H__