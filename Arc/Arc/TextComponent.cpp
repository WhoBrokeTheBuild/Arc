#include "TextComponent.h"
#include "Unit.h"

const Arc::UnitComponentType Arc::TextComponent::UNIT_CMP_TYPE_TEXT = "text";

const Arc::EventType Arc::TextComponent::EVENT_TEXT_CHANGED = "textComponent.textChanged";
const Arc::EventType Arc::TextComponent::EVENT_FONT_CHANGED = "textComponent.fontChanged";

Arc::TextComponent::~TextComponent(void)
{
	delete _pRenderedText;
}

void Arc::TextComponent::render( const RenderTarget* pTarget )
{
	const Unit* parent = getUnit();

	if (parent == nullptr)
        return;

	pTarget->drawText(parent->getPos() + getOffset(), _pRenderedText, getBlendColor(), getRotation(), getScale(), getOrigin());
}
