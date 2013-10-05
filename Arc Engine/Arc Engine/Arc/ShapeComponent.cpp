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

		data->renderTarget()->drawTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_RECTANGLE:

		data->renderTarget()->drawRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_PENTAGON:

		data->renderTarget()->drawPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_HEXAGON:

		data->renderTarget()->drawHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

		break;
	case SHAPE_CIRCLE:

		data->renderTarget()->drawCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );

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

		return _size * getScale();

		break;
	case SHAPE_TRIANGLE:
	case SHAPE_PENTAGON:
	case SHAPE_HEXAGON:
	case SHAPE_CIRCLE:

		return Size(_radius * 2.0f, _radius * 2.0f) * getScale();

		break;
	default:
		break;
	}

	return Vector2::ZERO;
}
