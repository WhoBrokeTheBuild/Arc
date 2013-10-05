#include "TextComponent.h"
#include "Unit.h"

Arc::TextComponent::TextComponent( Unit *pUnit, Font *pFont, string text /*= ""*/, Point offset /*= Point::ZERO*/, Point origin /*= Point::ZERO*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
	: DrawableComponent(pUnit, offset, origin, scale, rotation, blendColor),
	  _pRenderedText(nullptr)
{
	_pRenderedText = New RenderedText(text, pFont);
}

Arc::TextComponent::TextComponent( Unit *pUnit, Font *pFont, string text /*= ""*/, Point offset /*= Point::ZERO*/, OriginLocation originLocation /*= OriginLocation::ORIGIN_LOCATION_TOP_LEFT*/, Vector2 scale /*= Vector2::ONE*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/ )
	: DrawableComponent(pUnit, offset, originLocation, scale, rotation, blendColor),
	 _pRenderedText(nullptr)
{
	_pRenderedText = New RenderedText(text, pFont);
	calcOriginLocation();
}

Arc::TextComponent::~TextComponent(void)
{
	delete _pRenderedText;
}

void Arc::TextComponent::render( const RenderData* data )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	data->renderTarget()->drawText(parent->getPos() + getOffset(), _pRenderedText, getBlendColor(), getRotation(), getScale(), getOrigin());
}