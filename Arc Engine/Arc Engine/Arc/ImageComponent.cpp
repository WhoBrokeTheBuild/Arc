#include "ImageComponent.h"
#include "Unit.h"

Arc::ImageComponent::ImageComponent( void )
{
	_pTexture = nullptr;
	Offset = Origin = Point::ZERO;
	Rotation = Angle::ZERO;
	BlendColor = Color::WHITE;
}

void Arc::ImageComponent::init( Texture *pTexture, Point offset /*= Point::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/, Point origin /*= Point::ZERO*/ )
{
	_pTexture  = pTexture;
	Offset     = offset;
	Rotation   = rotation;
	BlendColor = blendColor;
	Origin     = origin;
}

void Arc::ImageComponent::term( void )
{
}

void Arc::ImageComponent::render( const RenderData* data )
{
	const Unit* parent = getParentUnit();

	if (parent == nullptr)
        return;

	data->renderTarget()->draw(parent->Pos + Offset, _pTexture, Rect(Vector2::ZERO, _pTexture->getSize()), BlendColor, Rotation, Origin);
}
