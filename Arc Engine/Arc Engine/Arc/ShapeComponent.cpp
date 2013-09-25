#include "ShapeComponent.h"
#include "Unit.h"

Arc::ShapeComponent::ShapeComponent(void)
{
}

void Arc::ShapeComponent::init( bool filled /*= false*/, Point offset /*= Point::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/, Point origin /*= Point::ZERO */ )
{
	Offset = offset;
	Rotation = rotation;
	BlendColor = blendColor;
	Origin = origin;
	Filled = filled;
}

void Arc::ShapeComponent::term( void )
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

		if (Filled)
			data->renderTarget()->fillTriangle(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );
		else
			data->renderTarget()->drawTriangle(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );

		break;
	case SHAPE_RECTANGLE:

		if (Filled)
			data->renderTarget()->fillRect(parent->Pos + Offset, _size, BlendColor, Rotation, Origin );
		else
			data->renderTarget()->drawRect(parent->Pos + Offset, _size, BlendColor, Rotation, Origin );

		break;
	case SHAPE_PENTAGON:

		if (Filled)
			data->renderTarget()->fillPentagon(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );
		else
			data->renderTarget()->drawPentagon(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );

		break;
	case SHAPE_HEXAGON:

		if (Filled)
			data->renderTarget()->fillHexagon(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );
		else
			data->renderTarget()->drawHexagon(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );

		break;
	case SHAPE_CIRCLE:

		if (Filled)
			data->renderTarget()->fillCircle(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );
		else
			data->renderTarget()->drawCircle(parent->Pos + Offset, _radius, BlendColor, Rotation, Origin );

		break;
	}
}
