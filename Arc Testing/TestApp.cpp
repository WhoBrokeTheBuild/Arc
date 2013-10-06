#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>
#include <Arc/ShapeComponent.h>
#include <Arc/PhysicsComponent.h>
#include <Arc/TextComponent.h>

TestApp::TestApp( void )
    : Program()
{
    initAll(Size(610.0f), "Testing");

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(20, 20, 20));

	_pFont = New Font("assets/ds-digital.ttf", 20);
	_pFPSText = New RenderedText("0", _pFont);

	_texts.add(New RenderedText("Start", _pFont))
		 ->add(New RenderedText("Options", _pFont))
		 ->add(New RenderedText("Controls", _pFont))
		 ->add(New RenderedText("Save", _pFont))
		 ->add(New RenderedText("Load", _pFont))
		 ->add(New RenderedText("Quit", _pFont));

	float size = 360.0f / (float)_texts.size();

	for (int i = 0; i < _texts.size(); ++i)
	{
		_rots.add(Angle(90.0f + i * size, ANGLE_TYPE_DEG));
	}

	_optionIndex = 0;
	_toMove = 0.0f;
	_turnSpeed = 3.0f;

    pScene = New Scene();
	pResourceManager = New ResourceManager();
}

TestApp::~TestApp( void )
{
    delete pScene;

	delete pResourceManager;

    delete _pFont;
    delete _pFPSText;

	while ( ! _texts.empty())
		delete _texts.popBack();
}

void TestApp::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

	if (between(_toMove, -_turnSpeed, _turnSpeed))
	{
		for (unsigned int i = 0; i < _rots.size(); ++i)
			_rots[i] += Angle(_toMove, ANGLE_TYPE_DEG);

		_toMove = 0.0f;
	}
	else
	{
		for (unsigned int i = 0; i < _rots.size(); ++i)
			_rots[i] += Angle(_turnSpeed * sign(_toMove), ANGLE_TYPE_DEG);

		_toMove -= _turnSpeed * sign(_toMove);

	}
	
    stringstream ss;
    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    _pFPSText->setText(ss.str());
}

void TestApp::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->getRenderTarget();

	for (unsigned int i = 0; i < _texts.size(); ++i)
	{
		float dist = abs((_rots[i] + Angle(270.0f, ANGLE_TYPE_DEG)).getDeg() - 180.0f) / 180.0f;

		Vector2 backScale(1.1f), frontScale(2.0f);
		Color backColor(Color::STORM), frontColor(61, 204, 139);

		Vector2 scale = Vector2::lerp(backScale, frontScale, dist);
		Color color = Color::lerp(backColor, frontColor, dist);

		renderTarget->drawText(Point(250.0f, 250.0f) + Point(250.0f * _rots[i].getCos(), 30.0f * _rots[i].getSin()), _texts[i], color, Angle::ZERO, scale);
	}
}

void TestApp::renderEnd( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->getRenderTarget();
	
    renderTarget->drawText(Point(25), _pFPSText, Color::BLACK);
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

	float size = 360.0f / (float)_rots.size();

	switch (data->Key)
	{
	case KeyboardKey::KEY_LEFT:

		_toMove -= size;
		_optionIndex++;
		if (_optionIndex >= _texts.size())
			_optionIndex = 0;

		break;
	case KeyboardKey::KEY_RIGHT:

		_toMove += size;
		_optionIndex--;
		if (_optionIndex < 0)
			_optionIndex = _texts.size() - 1;

		break;
	case KeyboardKey::KEY_ENTER:

		switch (_optionIndex)
		{
		case 4:

			gpEventDispatcher->dispatchEvent(Event(EVENT_EXIT));

			break;
		}

		break;
	}
}