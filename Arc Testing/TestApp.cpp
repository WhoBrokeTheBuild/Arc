#include "TestApp.h"
#include <Arc/Socket.h>
#include "Arc/ServerSocket.h"

TestApp::TestApp( void )
    : Program()
{
	initAll(Size(400, 400), "Quacktics", Color::GREEN);

	_pFont = New Font("assets/Square.ttf", 20);
	_pFPSText = New RenderedText("0", _pFont);

    //_pScriptingSystem->executeFile("assets/test.lua");

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

	pTarget->drawText(Point(25), _pFPSText, Color::BLACK);
}
