#include "TextComponent.h"
#include "Unit.h"

Arc::TextComponent::TextComponent( Unit *pUnit, Font *pFont, string text /*= ""*/, Point offset /*= Point::ZERO*/, Angle rotation /*= Angle::ZERO*/, Color blendColor /*= Color::WHITE*/, Point origin /*= Point::ZERO*/ )
	: DrawableComponent(pUnit, offset, rotation, blendColor, origin),
	  _pRenderedText(nullptr)
{
	_pRenderedText = New RenderedText(text, pFont);
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

	data->renderTarget()->drawText(parent->getPos() + getOffset(), _pRenderedText, getBlendColor(), getRotation(), getOrigin());
}