#include "SpinMenu.h"
#include <Arc/Program.h>
#include "ResourceManager.h"

SpinMenu::SpinMenu( Point pos, Font *pFont )
	: Unit(pos, 0.0f),
	  _pFont(pFont),
	  _pCurrLevel(nullptr),
	  _pPrevLevel(nullptr)
{
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

	_pCurrLevel->update(data);
}

void SpinMenu::render( const RenderData* data )
{
	if (_pCurrLevel == nullptr)
		return;

	_pCurrLevel->render(data->getRenderTarget(), getPos());
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

void SpinMenu::switchLevel( MenuLevel* pLevel )
{
	_pCurrLevel = pLevel;
}
