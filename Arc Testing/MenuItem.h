#pragma once

#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include "Common.h"
#include <Arc/ManagedObject.h>
#include <Arc/RenderedText.h>

#include "MenuAction.h"

class MenuLevel;

class MenuItem :
	public ManagedObject
{
protected:

	MenuLevel
		*_pParentLevel;

	Font
		*_pFont;

	RenderedText
		*_pLabel;

	MenuAction
		_action;

public:

	MenuItem( MenuLevel *pParentLevel, string text, Font *pFont, MenuLevel *pLevel );
	MenuItem( MenuLevel *pParentLevel, string text, Font *pFont, string variable );
	virtual ~MenuItem( void );

	virtual inline string toString( void ) const { return "Menu Item"; }

	inline MenuLevel *getParentLevel( void ) const { return _pParentLevel; }
	inline RenderedText *getRenderedText( void ) const { return _pLabel; }

	inline void select( void ) { _action.select(); }

};

#endif // __MENU_ITEM_H__