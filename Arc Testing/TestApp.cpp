#include "TestApp.h"
#include <Arc/Socket.h>
#include "Arc/ServerSocket.h"

TestApp::TestApp( void )
    : Program()
{
	initCore();
	initRandom();
	initScripting();
	initNetworking();

	_targetFPS = -1;
}

TestApp::~TestApp( void )
{
}

void TestApp::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

	pause();
	dispatchEvent(Event(EVENT_EXIT));
}