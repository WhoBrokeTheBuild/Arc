#include "TestApp.h"
#include <Arc/Socket.h>
#include <Arc/ServerSocket.h>
#include <Arc/StringHelper.h>

TestApp::TestApp( void )
    : GraphicalProgram()
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

}

void TestApp::keyPressed( const Event& event )
{
	const KeyData* pData = event.dataAs<KeyData>();

}
