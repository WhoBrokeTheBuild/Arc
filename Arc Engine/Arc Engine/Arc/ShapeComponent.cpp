#include "ShapeComponent.h"
#include "Unit.h"

const Arc::ComponentType Arc::ShapeComponent::CMP_TYPE_SHAPE = "shape";

void Arc::ShapeComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
		return;

	switch (_shape)
	{
	case SHAPE_TRIANGLE:

		if (isFilled())
		{
			data->getRenderTarget()->fillTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			data->getRenderTarget()->drawTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_RECTANGLE:

		if (isFilled())
		{
			data->getRenderTarget()->fillRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			data->getRenderTarget()->drawRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_PENTAGON:

		if (isFilled())
		{
			data->getRenderTarget()->fillPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			data->getRenderTarget()->drawPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_HEXAGON:

		if (isFilled())
		{
			data->getRenderTarget()->fillHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			data->getRenderTarget()->drawHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_CIRCLE:

		if (isFilled())
		{
			data->getRenderTarget()->fillCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			data->getRenderTarget()->drawCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

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
