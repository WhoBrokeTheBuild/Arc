#include "ImageComponent.h"
#include "Unit.h"

const Arc::ComponentType Arc::ImageComponent::CMP_TYPE_IMAGE = "image";

void Arc::ImageComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	data->getRenderTarget()->draw(parent->getPos() + getOffset(), _pTexture, Rect(Vector2::ZERO, _pTexture->getSize()), getBlendColor(), getRotation(), getScale(), getOrigin());
}