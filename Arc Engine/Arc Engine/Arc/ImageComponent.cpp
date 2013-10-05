#include "ImageComponent.h"
#include "Unit.h"

Arc::ImageComponent::ImageComponent( Unit* pUnit, Texture *pTexture, Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
	: DrawableComponent(pUnit, offset, origin, scale, rotation, blendColor),
      _pTexture(pTexture)
{
}

Arc::ImageComponent::ImageComponent( Unit* pUnit, Texture *pTexture, Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/  )
	: DrawableComponent(pUnit, offset, originLocation, scale, rotation, blendColor),
	_pTexture(pTexture)
{
	calcOriginLocation();
}

Arc::ImageComponent::~ImageComponent( void )
{
}

void Arc::ImageComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	data->renderTarget()->draw(parent->getPos() + getOffset(), _pTexture, Rect(Vector2::ZERO, _pTexture->getSize()), getBlendColor(), getRotation(), getScale(), getOrigin());
}