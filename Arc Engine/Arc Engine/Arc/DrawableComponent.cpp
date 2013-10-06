#include "DrawableComponent.h"

Arc::DrawableComponent::DrawableComponent( Unit* pUnit, Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
	: Component(pUnit),
	  _offset(offset),
	  _origin(origin),
	  _originLocation(ORIGIN_LOCATION_MANUAL),
	  _scale(scale),
	  _rotation(rotation),
	  _blendColor(blendColor)
{
}

Arc::DrawableComponent::DrawableComponent( Unit* pUnit, Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
	: Component(pUnit),
	_offset(offset),
	_origin(Vector2::ZERO),
	_originLocation(originLocation),
	_scale(scale),
	_rotation(rotation),
	_blendColor(blendColor)
{
}

Arc::DrawableComponent::~DrawableComponent(void)
{
}

void Arc::DrawableComponent::calcOriginLocation( void )
{
	Vector2 size = getSize() * getScale();
	switch (_originLocation)
	{
	case ORIGIN_LOCATION_TOP_LEFT:

		_origin = Vector2::ZERO;

		break;
	case ORIGIN_LOCATION_TOP_RIGHT:

		_origin = Vector2(size.width(), 0);

		break;
	case ORIGIN_LOCATION_BOTTOM_LEFT:

		_origin = Vector2(0, size.height());

		break;
	case ORIGIN_LOCATION_BOTTOM_RIGHT:

		_origin = Vector2(size.width(), size.height());

		break;
	case ORIGIN_LOCATION_CENTER:

		_origin = Vector2(size.halfWidth(), size.halfHeight());

		break;
	case ORIGIN_LOCATION_TOP_CENTER:

		_origin = Vector2(size.halfWidth(), 0);

		break;
	case ORIGIN_LOCATION_BOTTOM_CENTER:

		_origin = Vector2(size.halfWidth(), size.height());

		break;
	case ORIGIN_LOCATION_LEFT_CENTER:

		_origin = Vector2(0, size.halfHeight());

		break;
	case ORIGIN_LOCATION_RIGHT_CENTER:

		_origin = Vector2(size.width(), size.halfHeight());

		break;
	default:
		break;
	}
}

void Arc::DrawableComponent::setOrigin( Vector2 origin )
{
	_origin = origin;
	_originLocation = ORIGIN_LOCATION_MANUAL;
}

void Arc::DrawableComponent::setOriginLocation( OriginLocation originLocation )
{
	_originLocation = originLocation;
	calcOriginLocation();
}