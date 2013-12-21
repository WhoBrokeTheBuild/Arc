#include "TestApp.h"
#include <Arc/Socket.h>
#include <Arc/ServerSocket.h>
#include <Arc/StringHelper.h>
#include <Arc/Date.h>
#include <Arc/Time.h>

TestApp::TestApp( void )
    : GraphicalProgram(Size(800.0f, 600.0f), "Arc Test", Color::WHITE)
{
	initRandom();
	initNetworkSystem();
}

TestApp::~TestApp( void )
{
}

void TestApp::update( const Event& event )
{
	const FrameData* pData = event.dataAs<FrameData>();
}

void TestApp::render( const Event& event )
{
	const RenderData* pData = event.dataAs<RenderData>();
	const RenderTarget* pTarget = pData->getRenderTarget();

    pTarget->drawLine(0, 0, 100, 100, Color::WHITE);
}

void TestApp::keyPressed( const Event& event )
{
	const KeyData* pData = event.dataAs<KeyData>();

}
