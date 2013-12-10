#include "ShapeComponent.h"
#include "Unit.h"

const Arc::UnitComponentType Arc::ShapeComponent::UNIT_CMP_TYPE_SHAPE = "shape";

const Arc::EventType Arc::ShapeComponent::EVENT_SHAPE_CHANGED  = "shapeComponent.shapeChanged";
const Arc::EventType Arc::ShapeComponent::EVENT_FILLED_CHANGED = "shapeComponent.filledChanged";

void Arc::ShapeComponent::render( const RenderTarget* pTarget )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
		return;

	switch (_shape)
	{
	case SHAPE_TRIANGLE:

		if (isFilled())
		{
			pTarget->fillTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			pTarget->drawTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_RECTANGLE:

		if (isFilled())
		{
			pTarget->fillRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			pTarget->drawRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_PENTAGON:

		if (isFilled())
		{
			pTarget->fillPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			pTarget->drawPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_HEXAGON:

		if (isFilled())
		{
			pTarget->fillHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			pTarget->drawHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}

		break;
	case SHAPE_CIRCLE:

		if (isFilled())
		{
			pTarget->fillCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
		}
		else
		{
			pTarget->drawCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getScale(), getOrigin() );
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
