#include "ImageComponent.h"
#include "Unit.h"

Arc::ImageComponent::ImageComponent( Unit* pUnit, Texture *pTexture, Point offset /*= Point::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/, Point origin /*= Point::ZERO*/ )
    : Component(pUnit),
      _pTexture(pTexture),
      Offset(offset),
      Rotation(rotation),
      BlendColor(blendColor),
      Origin(origin)
{
}

Arc::ImageComponent::~ImageComponent( void )
{
}

void Arc::ImageComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	data->renderTarget()->draw(parent->getPos() + Offset, _pTexture, Rect(Vector2::ZERO, _pTexture->getSize()), BlendColor, Rotation, Origin);
}
