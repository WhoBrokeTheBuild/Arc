#pragma once

#ifndef __SPIN_MENU_H__
#define __SPIN_MENU_H__

#include "Common.h"
#include <Arc/Unit.h>
#include <Arc/IKeyboardListener.h>

#include "MenuLevel.h"

class SpinMenu :
	public Unit,
	public IKeyboardListener
{
protected:

	Font
		*_pFont;

	ArrayList<MenuLevel*>
		_levels;

	MenuLevel
		*_pCurrLevel,
		*_pPrevLevel;

	bool
		_trans;

	Direction
		_transDir;

	float 
		_transSpeedMax,
		_transSpeed,
		_transAmount;

public:

	SpinMenu( Point pos, Font *pFont );
	virtual ~SpinMenu( void );

	virtual inline string toString( void ) const { return "Spin Menu"; }

	virtual void update( const FrameData* data );
	virtual void render( const RenderData* data );

	inline void addLevel( MenuLevel* pLevel ) { _levels.add(pLevel); }

	void switchLevel( MenuLevel* pLevel );

	virtual void keyPressed( const Event& event );

}; // class SpinMenu

#endif // __SPIN_MENU_H__