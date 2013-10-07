#include "MenuItem.h"
#include "MenuLevel.h"
#include "MenuAction.h"

MenuItem::MenuItem( MenuLevel *pParentLevel, string text, Font *pFont, MenuLevel *pLevel )
	: _pParentLevel(pParentLevel),
	  _action(this, pLevel),
	  _pFont(pFont),
	  _pLabel(nullptr)
{
	_pLabel = New RenderedText(text, pFont);
}

MenuItem::MenuItem( MenuLevel *pParentLevel, string text, Font *pFont, string variable )
	: _pParentLevel(pParentLevel),
	  _action(this, variable),
	  _pFont(pFont),
	  _pLabel(nullptr)
{
	_pLabel = New RenderedText(text, pFont);
}

MenuItem::MenuItem( MenuLevel *pParentLevel, string text, Font *pFont, MenuActionType type )
	: _pParentLevel(pParentLevel),
	  _action(this, type),
	  _pFont(pFont),
	  _pLabel(nullptr)
{
	_pLabel = New RenderedText(text, pFont);
}

MenuItem::~MenuItem( void )
{
	delete _pLabel;
}
