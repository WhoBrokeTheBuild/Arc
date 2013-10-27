#include "Origin.h"

const Arc::Origin Arc::Origin::ZERO = Origin(Point::ZERO);

void Arc::Origin::updateOrigin( void )
{
	switch (_originLocation)
	{
	case ORIGIN_LOCATION_TOP_LEFT:

		_origin = Vector2::ZERO;

		break;
	case ORIGIN_LOCATION_TOP_RIGHT:

		_origin = Vector2(_size.getWidth(), 0);

		break;
	case ORIGIN_LOCATION_BOTTOM_LEFT:

		_origin = Vector2(0, _size.getHeight());

		break;
	case ORIGIN_LOCATION_BOTTOM_RIGHT:

		_origin = Vector2(_size.getWidth(), _size.getHeight());

		break;
	case ORIGIN_LOCATION_CENTER:

		_origin = Vector2(_size.getHalfWidth(), _size.getHalfHeight());

		break;
	case ORIGIN_LOCATION_TOP_CENTER:

		_origin = Vector2(_size.getHalfWidth(), 0);

		break;
	case ORIGIN_LOCATION_BOTTOM_CENTER:

		_origin = Vector2(_size.getHalfWidth(), _size.getHeight());

		break;
	case ORIGIN_LOCATION_LEFT_CENTER:

		_origin = Vector2(0, _size.getHalfHeight());

		break;
	case ORIGIN_LOCATION_RIGHT_CENTER:

		_origin = Vector2(_size.getWidth(), _size.getHalfHeight());

		break;
	default:
		break;
	}
}