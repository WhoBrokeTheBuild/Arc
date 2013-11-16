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
	initGraphics(Size(400, 400), "Quacktics", Color::WHITE);

	_targetFPS = -1;

    //_pScriptingSystem->executeFile("assets/test.lua");

	//int port = 1234;
	//ServerSocket ss(port);
	//INFOF(toString(), "Server listening on port %i", port);
	//
	//while (true)
	//{
	//	Socket *pS = ss.waitForClient();
	//	INFOF(toString(), "Recieved client from %s", pS->getAddress().toString().c_str());
	//
	//	Buffer buf;
	//	buf.resize(512);
	//	buf.appendBool(false);
	//	buf.appendChar('a');
	//	buf.appendInt(1237);
	//	buf.appendShort(43);
	//	buf.appendLong(21421344);
	//	buf.appendFloat(2.633f);
	//	buf.appendDouble(0.12341423);
	//	buf.appendStringWithLength("Hello, World!");
	//
	//	pS->sendBuffer(buf);
	//
	//	ss.closeClient(pS);
	//}

	//Socket *pS = getNetworkSystem()->connect("127.0.0.1", 1234, SOCKET_TYPE_TCP);
	//
	//Buffer buf = pS->recvBuffer(512);
	//cout << (buf.readNextBool() ? "true" : "false") << endl;
	//cout << buf.readNextChar() << endl;
	//cout << buf.readNextInt() << endl;
	//cout << buf.readNextShort() << endl;
	//cout << buf.readNextLong() << endl;
	//cout << buf.readNextFloat() << endl;
	//cout << buf.readNextDouble() << endl;
	//cout << buf.readNextStringWithLength() << endl;
	//
	//delete pS;
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

	pTarget->drawLine(0, 0, 100, 100, Color::RED);
}
