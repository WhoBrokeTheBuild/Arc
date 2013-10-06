#include "ShapeComponent.h"
#include "Unit.h"

Arc::ShapeComponent::ShapeComponent( Unit* pUnit, Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO */, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
    : DrawableComponent(pUnit, offset, origin, scale, rotation, blendColor)
{
}

Arc::ShapeComponent::ShapeComponent( Unit* pUnit, Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
	: DrawableComponent(pUnit, offset, originLocation, scale, rotation, blendColor)
{
	calcOriginLocation();
}

Arc::ShapeComponent::~ShapeComponent( void )
{
}

void Arc::ShapeComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
		return;

	switch (_shape)
	{
	case SHAPE_TRIANGLE:

		data->getRenderTarget()->drawTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_RECTANGLE:

		data->getRenderTarget()->drawRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_PENTAGON:

		data->getRenderTarget()->drawPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_HEXAGON:

		data->getRenderTarget()->drawHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_CIRCLE:

		data->getRenderTarget()->drawCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
    default:
        break;
	}
}

Arc::Vector2 Arc::ShapeComponent::getSize( void ) const
{	
	switch (_shape)
	{
	case SHAPE_RECTANGLE:

		return _size;

		break;
	case SHAPE_TRIANGLE:
	case SHAPE_PENTAGON:
	case SHAPE_HEXAGON:
	case SHAPE_CIRCLE:

		return Size(_radius * 2.0f, _radius * 2.0f);

		break;
	default:
		break;
	}

	return Vector2::ZERO;
}
