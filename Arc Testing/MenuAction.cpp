#include "MenuAction.h"
#include "MenuLevel.h"
#include "MenuItem.h"
#include "SpinMenu.h"

MenuAction::MenuAction( MenuItem *pParent, MenuLevel *pLevel )
	: _pParentItem(pParent),
	  _pLevel(pLevel),
	  _type(MENU_ACTION_SWITCH_LEVEL),
	  _varName()
{
}

MenuAction::MenuAction( MenuItem *pParent, string variable )
	: _pParentItem(pParent),
	  _pLevel(nullptr),
	  _type(MENU_ACTION_TOGGLE_VAR),
	  _varName(variable)
{
}

MenuAction::~MenuAction( void )
{
}

void MenuAction::select( void )
{
	switch (_type)
	{
	case MENU_ACTION_SWITCH_LEVEL:

		getParentItem()->getParentLevel()->getParentMenu()->switchLevel(_pLevel);

		break;
	}
}
