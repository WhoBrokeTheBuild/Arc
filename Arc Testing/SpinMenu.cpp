#include "SpinMenu.h"
#include "Arc\Program.h"

SpinMenu::SpinMenu( Point pos, Font *pFont )
	: Unit(pos, 0.0f),
	_pParentMenu(nullptr),
	  _pFont(pFont),
	  _active()
{
	_optionIndex = 0;
	_toMove      = 0.0f;
	_turnSpeed   = 3.0f;
}

SpinMenu::~SpinMenu( void )
{
	while ( ! _menuItems.isEmpty())
		delete _menuItems.popBack();

	_subMenus.clear();
}

void SpinMenu::addItem( string text, MenuActions action, SpinMenu* pSubMenu /*= nullptr */ )
{
	_menuItems.add(New RenderedText(text, _pFont));

	float size = 360.0f / (float)_menuItems.getSize();

	_textRotations.clear();
	for (unsigned int i = 0; i < _menuItems.getSize(); ++i)
		_textRotations.add(Angle(90.0f + i * size, ANGLE_TYPE_DEG));

	_actions.add(_menuItems.getSize() - 1, action);

	if (action == MENU_ACT_MENU && pSubMenu != nullptr)
		_subMenus.add(_menuItems.getSize() - 1, pSubMenu);
}

void SpinMenu::update( const FrameData* data )
{
	bool dark = false;

	if ( ! _active)
	{
		if (getParentMenu() != nullptr && getParentMenu()->isActive())
			return;

		_darkOffset += 0.04f;
		if (_darkOffset >= 1.0f)
			_darkOffset = 1.0f;

		return;
	}

	if (between(_toMove, -_turnSpeed, _turnSpeed))
	{
		for (unsigned int i = 0; i < _textRotations.getSize(); ++i)
			_textRotations[i] += Angle(_toMove, ANGLE_TYPE_DEG);

		_toMove = 0.0f;
	}
	else
	{
		for (unsigned int i = 0; i < _textRotations.getSize(); ++i)
			_textRotations[i] += Angle(_turnSpeed * sign(_toMove), ANGLE_TYPE_DEG);

		_toMove -= _turnSpeed * sign(_toMove);

	}
}

void SpinMenu::render( const RenderData* data )
{
	bool dark = false;

	if ( ! _active)
	{
		if (getParentMenu() != nullptr && getParentMenu()->isActive())
			return;

		dark = true;
	}

	const RenderTarget* renderTarget = data->getRenderTarget();

	for (unsigned int i = 0; i < _menuItems.getSize(); ++i)
	{
		float dist = abs((_textRotations[i] + Angle(270.0f, ANGLE_TYPE_DEG)).getDeg() - 180.0f) / 180.0f;

		Vector2 backScale(1.1f), frontScale(2.0f);
		Color backColor(Color::STORM), frontColor(61, 204, 139);

		Vector2 scale = Vector2::lerp(backScale, frontScale, dist);
		Color color = Color::lerp(backColor, frontColor, dist);

		if (dark)
		{
			renderTarget->drawText(getPos() - Point(0.0f, lerpNumber(20.0f, 150.0f, _darkOffset)) + Point(250.0f * _textRotations[i].getCos(), 30.0f * _textRotations[i].getSin()), _menuItems[i], Color(color.byteR(), color.byteG(), color.byteB(), lerpNumber(255, 40, _darkOffset)), Angle::ZERO, scale);
		}
		else
		{
			renderTarget->drawText(getPos() + Point(250.0f * _textRotations[i].getCos(), 30.0f * _textRotations[i].getSin()), _menuItems[i], color, Angle::ZERO, scale);
		}
	}
}

void SpinMenu::tickLeft( void )
{
	float size = 360.0f / (float)_textRotations.getSize();

	_toMove -= size;
	_optionIndex++;
	if (unsigned(_optionIndex) >= _menuItems.getSize())
		_optionIndex = 0;
}

void SpinMenu::tickRight( void )
{
	float size = 360.0f / (float)_textRotations.getSize();

	_toMove += size;
	_optionIndex--;
	if (_optionIndex < 0)
		_optionIndex = _menuItems.getSize() - 1;
}

SpinMenu* SpinMenu::select( void )
{
	MenuActions action = _actions[_optionIndex];

	switch (action)
	{
	case MENU_ACT_MENU:

		return _subMenus[_optionIndex];

		break;
	case MENU_ACT_EXIT:

		gpEventDispatcher->dispatchEvent(Event(Program::EVENT_EXIT));

		break;
	}

	return nullptr;
}
