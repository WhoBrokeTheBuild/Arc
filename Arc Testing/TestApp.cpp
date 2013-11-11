#include "TestApp.h"

TestApp::TestApp( void )
    : Program()
{
	initCore();
	initRandom();
	initScripting();
	initNetworking();

	_targetFPS = -1;

    //_pScriptingSystem->executeFile("assets/test.lua");

}

TestApp::~TestApp( void )
{
}

void TestApp::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();
}