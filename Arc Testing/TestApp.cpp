#include "TestApp.h"
#include <Arc/Socket.h>
#include "Arc/ServerSocket.h"

TestApp::TestApp( void )
    : Program()
{
	initAll(Size(400, 400), "Face-Lift", Color::WHITE);

	_pFont = New Font("assets/Square.ttf", 20);
	_pFPSText = New RenderedText("0", _pFont);

	_leftEyePos = Vector2(110, 100);
	_rightEyePos = Vector2(290, 100);
	_leftPupilPos = _rightPupilPos = Vector2(0.0f, 10.0f);

	_nosePos = Vector2(200, 190);

	_mouthLeftPos = Vector2(100, 300);
	_mouthCenterPos = Vector2(200, 320);
	_mouthRightPos = Vector2(300, 300);
}

TestApp::~TestApp( void )
{
	delete _pFont;
	delete _pFPSText;
}

void TestApp::update( const Event& event )
{
	const FrameData* pData = event.dataAs<FrameData>();

	stringstream ss;
	ss.str(string());
	ss << "FPS: " << MathHelper::ceil(_currentFPS, 1);
	_pFPSText->setText(ss.str());
}

void TestApp::render( const Event& event )
{
	const RenderData* pData = event.dataAs<RenderData>();
	const RenderTarget* pTarget = pData->getRenderTarget();

	pTarget->drawCircle(Circle(_leftEyePos, 30.0f), Color::BLACK);
	pTarget->drawCircle(Circle(_rightEyePos, 30.0f), Color::BLACK);
	pTarget->fillCircle(Circle(_leftEyePos + _leftPupilPos, 15.0f), Color::BLACK);
	pTarget->fillCircle(Circle(_rightEyePos + _rightPupilPos, 15.0f), Color::BLACK);

	pTarget->drawTriangle(_nosePos + Vector2(0.0f, -20.0f), _nosePos + Vector2(15.0f, 15.0f), _nosePos + Vector2(-15.0f, 15.0f), Color::BLACK);

	ArrayList<Point> mouth;
	mouth.add(_mouthLeftPos);
	mouth.add(_mouthCenterPos + Vector2(0.0f, -30.0f));
	mouth.add(_mouthRightPos);
	mouth.add(_mouthCenterPos + Vector2(0.0f, 30.0f));
	pTarget->drawPolygon(mouth, Color::BLACK);
}

void TestApp::keyPressed( const Event& event )
{
	const KeyData* pData = event.dataAs<KeyData>();

	switch (pData->Key)
	{
	case KEY_1:

		_leftPupilPos.Y -= 2;

		break;
	case KEY_2:

		_leftPupilPos.Y += 2;

		break;
	case KEY_3:

		_rightPupilPos.Y -= 2;

		break;
	case KEY_4:

		_rightPupilPos.Y += 2;

		break;
	}
}
