#include "MenuLevel.h"
#include "MenuItem.h"

MenuLevel::MenuLevel( SpinMenu *pParentMenu, Font *pFont )
	: _pParentMenu(pParentMenu),
	  _pFont(pFont),
	  _menuItems(),
	  _toMove(),
	  _turnSpeed(),
	  _index()
{
	_turnSpeed = 3.0f;
}

MenuLevel::~MenuLevel( void )
{
	for (auto it = _menuItems.begin(); it != _menuItems.end(); ++it)
		delete (*it);
}

void MenuLevel::tickLeft( void )
{
	float size = 360.0f / (float)_rotations.getSize();

	_toMove -= size;
	_index++;
	if (_index >= (int)_menuItems.getSize())
		_index = 0;
}

void MenuLevel::tickRight( void )
{
	float size = 360.0f / (float)_rotations.getSize();

	_toMove += size;
	_index--;
	if (_index < 0)
		_index = _menuItems.getSize() - 1;
}

void MenuLevel::select( void )
{
	_menuItems[_index]->select();
}

void MenuLevel::addItem( string text, MenuLevel *pLevel )
{
	_menuItems.add(New MenuItem(this, text, _pFont, pLevel));
	updateRotations();
}

void MenuLevel::addItem( string text, string variable )
{
	_menuItems.add(New MenuItem(this, text, _pFont, variable));
	updateRotations();
}

void MenuLevel::update( const FrameData* data )
{
	if (between(_toMove, -_turnSpeed, _turnSpeed))
	{
		for (unsigned int i = 0; i < _rotations.getSize(); ++i)
			_rotations[i] += Angle(_toMove, ANGLE_TYPE_DEG);

		_toMove = 0.0f;
	}
	else
	{
		for (unsigned int i = 0; i < _rotations.getSize(); ++i)
			_rotations[i] += Angle(_turnSpeed * sign(_toMove), ANGLE_TYPE_DEG);

		_toMove -= _turnSpeed * sign(_toMove);

	}
}

void MenuLevel::render( const RenderTarget* pTarget, const Point pos )
{
	for (unsigned int i = 0; i < _menuItems.getSize(); ++i)
	{
		float dist = abs((_rotations[i] + Angle(270.0f, ANGLE_TYPE_DEG)).getDeg() - 180.0f) / 180.0f;

		Vector2 backScale(1.1f), frontScale(2.0f);
		Color backColor(Color::STORM), frontColor(61, 204, 139);

		Vector2 scale = Vector2::lerp(backScale, frontScale, dist);
		Color color = Color::lerp(backColor, frontColor, dist);

		pTarget->drawText(pos + Point(250.0f * _rotations[i].getCos(), 30.0f * _rotations[i].getSin()), _menuItems[i]->getRenderedText(), color, Angle::ZERO, scale);
	}
}

void MenuLevel::updateRotations( void )
{
	float size = 360.0f / (float)_menuItems.getSize();

	_rotations.clear();
	for (unsigned int i = 0; i < _menuItems.getSize(); ++i)
		_rotations.add(Angle(90.0f + i * size, ANGLE_TYPE_DEG));
}
