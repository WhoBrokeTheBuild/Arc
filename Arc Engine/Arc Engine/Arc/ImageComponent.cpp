#include "ImageComponent.h"
#include "Unit.h"

Arc::ImageComponent::ImageComponent( void )
{
	_pTexture = nullptr;
	Offset = Point::ZERO;
}

void Arc::ImageComponent::init( Texture *pTexture, Point offset )
{
	_pTexture = pTexture;
	Offset = offset;
}

void Arc::ImageComponent::term( void )
{
}

void Arc::ImageComponent::render( const RenderData* data )
{
	const Unit* parent = getParentUnit();

	data->renderTarget()->draw(parent->Pos + Offset, _pTexture, Rect(Vector2::ZERO, _pTexture->getSize()), BlendColor, Rotation, Origin);
}