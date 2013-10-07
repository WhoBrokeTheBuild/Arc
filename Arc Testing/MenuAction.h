#pragma once

#ifndef __MENU_ACTION_DATA_H__
#define __MENU_ACTION_DATA_H__

#include "Common.h"
#include <Arc/ManagedObject.h>

class MenuLevel;
class MenuItem;

enum MenuActionType
{
	INVALID_MENU_ACTION_TYPE = -1,

	MENU_ACTION_SWITCH_LEVEL,
	MENU_ACTION_TOGGLE_VAR,
	MENU_ACTION_BACK,
	MENU_ACTION_EXIT,

	NUM_MENU_ACTION_TYPES
};

class MenuAction :
	public ManagedObject
{
protected:

	MenuItem
		*_pParentItem;

	MenuActionType
		_type;

	MenuLevel
		*_pLevel;

	string
		_varName;

public:

	MenuAction( MenuItem *pParent, MenuLevel *pLevel );
	MenuAction( MenuItem *pParent, string variable );
	MenuAction( MenuItem *pParent, MenuActionType type );
	virtual ~MenuAction( void );

	virtual inline string toString( void ) const { return "Menu Action"; }

	void select( void );

	inline MenuItem *getParentItem( void ) const { return _pParentItem; }

};

#endif // __MENU_ACTION_DATA_H__