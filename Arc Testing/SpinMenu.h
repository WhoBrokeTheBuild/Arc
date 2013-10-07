#pragma once

#ifndef __SPIN_MENU_H__
#define __SPIN_MENU_H__

#include "Common.h"
#include <Arc/Unit.h>

enum MenuActions
{
	MENU_ACT_NONE,
	MENU_ACT_MENU,
	MENU_ACT_EXIT
};

class SpinMenu :
	public Unit
{
protected:

	SpinMenu
		*_pParentMenu;

	Font
		*_pFont;

	ArrayList<Angle>
		_textRotations;

	Map<unsigned int, SpinMenu*>
		_subMenus;

	Map<unsigned int, MenuActions>
		_actions;

	ArrayList<RenderedText*>
		_menuItems;

	float 
		_turnSpeed,
		_toMove;

	int
		_optionIndex;

	bool 
		_active;

	float 
		_darkOffset;

public:

	SpinMenu( Point pos, Font *pFont );
	virtual ~SpinMenu( void );

	virtual inline string toString( void ) const { return "Spin Menu"; }

	void addItem( string text, MenuActions action = MENU_ACT_NONE, SpinMenu* pSubMenu = nullptr );

	virtual void update( const FrameData* data );
	virtual void render( const RenderData* data );

	inline SpinMenu* getParentMenu( void ) const { return _pParentMenu; }
	inline void setParentMenu( SpinMenu* pParent ) { _pParentMenu = pParent; }

	void tickLeft ( void );
	void tickRight( void );
	SpinMenu* select( void );

	inline void activate( void ) { _active = true; }
	inline void deactivate( void ) { _active = false; _darkOffset = 0.0f; }
	inline bool isActive( void ) { return _active; }

}; // class SpinMenu

#endif // __SPIN_MENU_H__