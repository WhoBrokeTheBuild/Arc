#include "ShapeComponent.h"
#include "Unit.h"

Arc::ShapeComponent::ShapeComponent( Unit* pUnit, Point offset /*= Point::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/, Point origin /*= Point::ZERO */ )
    : DrawableComponent(pUnit, offset, rotation, blendColor, origin)
{
}

Arc::ShapeComponent::~ShapeComponent( void)
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

		data->renderTarget()->drawTriangle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getOrigin() );

		break;
	case SHAPE_RECTANGLE:

		data->renderTarget()->drawRect(parent->getPos() + getOffset(), _size, getBlendColor(), getRotation(), getOrigin() );

		break;
	case SHAPE_PENTAGON:

		data->renderTarget()->drawPentagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getOrigin() );

		break;
	case SHAPE_HEXAGON:

		data->renderTarget()->drawHexagon(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getOrigin() );

		break;
	case SHAPE_CIRCLE:

		data->renderTarget()->drawCircle(parent->getPos() + getOffset(), _radius, getBlendColor(), getRotation(), getOrigin() );

		break;
    default:
        break;
	}
}
