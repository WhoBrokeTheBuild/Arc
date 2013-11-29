#include "ImageComponent.h"
#include "Unit.h"

const Arc::EventType Arc::ImageComponent::EVENT_TEXTURE_CHANGED = "imageComponent.textureChanged";

const Arc::UnitComponentType Arc::ImageComponent::UNIT_CMP_TYPE_IMAGE = "image";

void Arc::ImageComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	data->getRenderTarget()->draw(parent->getPos() + getOffset(), _pTexture, _sourceRect, getBlendColor(), getRotation(), getScale(), getOrigin());
}
