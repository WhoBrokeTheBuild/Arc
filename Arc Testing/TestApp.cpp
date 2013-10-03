#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>
#include "Arc/ShapeComponent.h"
#include "Arc/PhysicsComponent.h"

TestApp::TestApp( void )
    : Program()
{
    initAll(Size(610, 610), "Testing");

	//Socket* pSock = getNetworkSystem()->connect("localhost", 8080, SocketType::SOCKET_TYPE_TCP);
	//
	//pSock->sendString("GET / HTTP/1.0\n\n");
	//cout << pSock->readString(2000);
	//pSock->sendString("\n\n");
	//cout << pSock->readString(2000);
	//
	//die();

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(150, 150, 150));

    pFont = New Font("assets/ds-digital.ttf", 20);
    pFPSText = New RenderedText("0", pFont);

	_dirs.add(Vector2(0.0f, -1.0f))->add(Vector2(0.0f, 1.0f))->add(Vector2(-1.0f, 0.0f))->add(Vector2(1.0f, 0.0f));
	_obstacles.add(Vector2(5.0f, 3.0f));

    pScene = New Scene();
	pResourceManager = New ResourceManager();

    pPlayer = New Duck(Vector2(1.0f), 3);

    //Texture* tex = New Texture("assets/test.png");
	//pResourceManager->addTexture(tex);
	//
	//pPlayer->addNewImageComponent(tex);

	pPlayer->addNewTextComponent(pFont, "Hello");
	
	pScene->addUnit(pPlayer, 0);
	pScene->addUnitTag(pPlayer, "duck");
}

TestApp::~TestApp( void )
{
    delete pScene;

	delete pResourceManager;

    delete pFont;
    delete pFPSText;
}

void TestApp::update( const Event& event )
{
    //const FrameData* data = event.dataAs<FrameData>();

    stringstream ss;

    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    pFPSText->setText(ss.str());
}

void TestApp::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->renderTarget();

	Size winSize = getGraphicsSystem()->getWindowSize();
	
	for (float i = 0; i < winSize.width(); i += GRID_SIZE)
	{
		renderTarget->drawLine(i, 0.0f, i, winSize.height(), Color::BLACK);
	}
	for (float j = 0; j < winSize.height(); j += GRID_SIZE)
	{
		renderTarget->drawLine(0.0f, j, winSize.width(), j, Color::BLACK);
	}
	
	ArrayList<Unit*> ducks = pScene->getUnitsByTag("duck");
	
	Duck* duck;
	auto end = ducks.end();
	for (auto it = ducks.begin(); it != end; ++it)
	{
		duck = (Duck*)(*it);
		ArrayList<Vector2> spaces = getValidMoveSpaces(duck);
	
		for (unsigned int i = 0; i < spaces.size(); ++i)
		{
			renderTarget->fillRect(spaces[i], Vector2(GRID_SIZE) - Vector2::ONE, Color::BLUE);
		}
	}
	
	for (unsigned int i = 0; i < _obstacles.size(); ++i)
	{
		renderTarget->fillRect(_obstacles[i] * GRID_SIZE, Vector2(GRID_SIZE) - Vector2::ONE, Color::RED);
	}
}

void TestApp::renderEnd( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->renderTarget();
	
    renderTarget->drawText(Point(25), pFPSText, Color::BLACK);
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

	switch (data->Key)
	{
	case KEY_ESCAPE:

        gpEventDispatcher->dispatchEvent(Event(EVENT_EXIT));

		break;
	}
}

void TestApp::mousePressed( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();
	
	ArrayList<Unit*> ducks = pScene->getUnitsByTag("duck");
	
	Duck* duck;
	auto end = ducks.end();
	for (auto it = ducks.begin(); it != end; ++it)
	{
		duck = (Duck*)(*it);
		ArrayList<Vector2> spaces = getValidMoveSpaces(duck);
	
		for (unsigned int i = 0; i < spaces.size(); ++i)
		{
			if (Rect(spaces[i], Vector2(GRID_SIZE) - Vector2::ONE).containsPoint(data->Pos))
			{
				int gX = (int)(spaces[i].X / GRID_SIZE),
					gY = (int)(spaces[i].Y / GRID_SIZE);
				duck->setPos(Point(gX, gY));
				break;
			}
		}
	}
}

ArrayList<Vector2> TestApp::getValidMoveSpaces( Duck* duck )
{
	Size winSize = getGraphicsSystem()->getWindowSize();
	
	ArrayList<Vector2> spaces;
	
	Point pos;
	Point gridPos;
	Vector2 dir;
	for (int d = 0; d < _dirs.size(); ++d)
	{
		dir = _dirs[d];
		pos = duck->getPos();
		for (int i = 0; i < duck->getSpeed(); ++i)
		{
			pos += dir * GRID_SIZE;
			gridPos.X = (int)(pos.X / GRID_SIZE);
			gridPos.Y = (int)(pos.Y / GRID_SIZE);
	
			if (pos.X < 0 || pos.Y < 0 || pos.X > winSize.width() || pos.Y > winSize.height())
				break;
	
			bool obstacle = false;
			for (unsigned int j = 0; j < _obstacles.size(); ++j)
			{
				if (gridPos == _obstacles[j])
				{
					obstacle = true;
					break;
				}
			}
	
			if (obstacle)
				break;
	
			spaces.add(pos);
		}
	}

	return spaces;
}
