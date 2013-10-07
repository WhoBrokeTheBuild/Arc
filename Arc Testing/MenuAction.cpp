#include "MenuAction.h"
#include "MenuLevel.h"
#include "MenuItem.h"
#include "SpinMenu.h"
#include <Arc/Program.h>

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

MenuAction::MenuAction( MenuItem *pParent, MenuActionType type )
	: _pParentItem(pParent),
	  _pLevel(nullptr),
	  _type(type),
	  _varName()
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
	case MENU_ACTION_BACK:

		getParentItem()->getParentLevel()->getParentMenu()->switchLevel(getParentItem()->getParentLevel()->getBackLevel(), Direction::DIR_SOUTH);

		break;
	case MENU_ACTION_EXIT:
		
		gpEventDispatcher->dispatchEvent(Event(Program::EVENT_EXIT));

		break;
	}
}
