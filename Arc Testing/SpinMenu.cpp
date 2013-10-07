#include "SpinMenu.h"
#include <Arc/Program.h>
#include "ResourceManager.h"

SpinMenu::SpinMenu( Point pos, Font *pFont )
	: Unit(pos, 0.0f),
	  _pFont(pFont),
	  _pCurrLevel(nullptr),
	  _pPrevLevel(nullptr),
	  _pNextLevel(nullptr),
	  _trans(false),
	  _transDir(),
	  _transSpeed(),
	  _transSpeedMax(),
	  _transAmount()
{
	_transSpeedMax = 300.0f;
	_transSpeed    = 0.0f;
	_transAmount   = 0.0f;
}

SpinMenu::~SpinMenu( void )
{
	for (auto it = _levels.begin(); it != _levels.end(); ++it)
		delete (*it);
}

void SpinMenu::update( const FrameData* data )
{
	if (_pCurrLevel == nullptr)
		return;

	if (_trans)
	{
		_transSpeed -= data->getElapsedMilliseconds();
		_transAmount = clamp(_transSpeed / _transSpeedMax, 0.0f, 1.0f);

		if (_transDir == Direction::DIR_SOUTH)
			_transAmount = 1.0f - _transAmount;
		
		if (_transSpeed <= 0.0f)
			_trans = false;
	}

	_pCurrLevel->update(data);
}

void SpinMenu::render( const RenderData* data )
{
	if (_trans)
	{
		if (_pPrevLevel != nullptr)
			_pPrevLevel->render(data->getRenderTarget(), Vector2::lerp(getPos() + Vector2(0.0f, -150.0f), getPos(), _transAmount), _transAmount);

		if (_pNextLevel != nullptr)
			_pNextLevel->render(data->getRenderTarget(), Vector2::lerp(getPos() + Vector2(0.0f, 150.0f), getPos(), 1.0f - _transAmount), 1.0f - _transAmount);
	}
	else
	{
		_pCurrLevel->render(data->getRenderTarget(), getPos(), 1.0f);
	}
}

void SpinMenu::keyPressed( const Event& event )
{
	if (_pCurrLevel == nullptr)
		return;

	const KeyData* data = event.dataAs<KeyData>();

	switch (data->Key)
	{
	case KeyboardKey::KEY_LEFT:

		gpResourceManager->getSound(0)->play();
		_pCurrLevel->tickLeft();

		break;
	case KeyboardKey::KEY_RIGHT:

		gpResourceManager->getSound(0)->play();
		_pCurrLevel->tickRight();

		break;
	case KeyboardKey::KEY_ENTER:

		gpResourceManager->getSound(1)->play();
		_pCurrLevel->select();

		break;
	}
}

void SpinMenu::switchLevel( MenuLevel* pLevel, Direction dir /*= Direction::DIR_NORTH*/ )
{
	if (dir == DIR_NORTH)
	{
		_pPrevLevel = _pCurrLevel;
		_pNextLevel = pLevel;
		_pCurrLevel = pLevel;
	}
	else if (dir == DIR_SOUTH)
	{
		_pNextLevel = _pCurrLevel;
		_pPrevLevel = pLevel;
		_pCurrLevel = pLevel;
	}

	_trans = true;
	_transSpeed = _transSpeedMax;
	_transDir = dir;
}
