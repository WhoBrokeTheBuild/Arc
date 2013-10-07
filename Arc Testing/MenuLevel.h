#pragma once

#ifndef __MENU_LEVEL_H__
#define __MENU_LEVEL_H__

#include "Common.h"
#include <Arc/ManagedObject.h>

#include <Arc/ArrayList.h>
#include <Arc/RenderTarget.h>
#include <Arc/EventData.h>

#include "MenuAction.h"

class SpinMenu;
class MenuItem;

class MenuLevel :
	public ManagedObject
{
protected:

	SpinMenu
		*_pParentMenu;

	MenuLevel
		*_pBackLevel;

	Font
		*_pFont;

	ArrayList<MenuItem*>
		_menuItems;

	ArrayList<Angle>
		_rotations;

	int
		_index;

	float 
		_toMove,
		_turnSpeed;

	void updateRotations( void );

public:

	MenuLevel( SpinMenu *pParentMenu, Font *pFont );
	~MenuLevel( void );

	virtual inline string toString( void ) const { return "Menu Level"; }

	virtual inline SpinMenu *getParentMenu( void ) const { return _pParentMenu; }
	virtual inline MenuLevel *getBackLevel( void ) const { return _pBackLevel; }

	virtual inline void setBackLevel( MenuLevel *pLevel ) { _pBackLevel = pLevel; }

	void addItem( string text, MenuLevel *pLevel );
	void addItem( string text, string variable );
	void addItem( string text, MenuActionType type );

	void tickLeft ( void );
	void tickRight( void );
	void select   ( void );

	void update( const FrameData* data );
	void render( const RenderTarget* pTarget, const Point pos, const float transAmount );

};

#endif // __MENU_LEVEL_H__