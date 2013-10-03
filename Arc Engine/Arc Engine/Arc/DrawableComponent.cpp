#include "DrawableComponent.h"

Arc::DrawableComponent::DrawableComponent( Unit* pUnit, Point offset /*= Point::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/, Point origin /*= Point::ZERO*/ )
	: Component(pUnit),
	  _offset(offset),
	  _origin(origin),
	  _rotation(rotation),
	  _blendColor(blendColor)
{
}

Arc::DrawableComponent::~DrawableComponent(void)
{
}
