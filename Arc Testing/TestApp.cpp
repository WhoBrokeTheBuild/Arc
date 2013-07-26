#include "TestApp.h"

void TestApp::init( void )
{
    Program::init(Size(600), "Test Arc");
    IKeyboardListener::init();
    IMouseListener::init();

    _pGraphicsSystem->setClearColor(Color(150, 150, 150));

    pScene = New Scene();
    pScene->init();
    pScene->setLayerEnabled(0, false);

    Wall* wall;

    // Top

    wall = New Wall();
    wall->init(Point::ZERO, Rect(0, 0, 600, 20));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall-vert");

    // Bottom

    wall = New Wall();
    wall->init(Point(0, 580), Rect(0, 0, 600, 20));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall-vert");

    // Left

    wall = New Wall();
    wall->init(Point(580, 0), Rect(0, 0, 20, 600));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall-horiz");

    // Right

    wall = New Wall();
    wall->init(Point::ZERO, Rect(0, 0, 20, 600));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall-horiz");

    pBall = New Ball();
    pBall->init(Point(300));

    pScene->addUnit(pBall, 0);
    pScene->addUnitTag(pBall, "ball");

    pFont = New Font();
    pFont->init("assets/ds-digital.ttf", 20);

    pFPSText = New CachedText();
    pFPSText->init("0", pFont);
}

void TestApp::term( void )
{
    delete pScene;

    delete pFont;
    delete pFPSText;
}

void TestApp::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();

    stringstream ss;

    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    pFPSText->setText(ss.str());
}

void TestApp::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
    
    data->renderTarget()->drawText(Point(25), pFPSText, Color::BLACK);
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    if (data->Key == KEY_ESCAPE)
    {
        gpEventDispatcher->dispatchEvent(Event(EVENT_EXIT));
    }
}

void TestApp::mousePressed( const Event& event )
{
    const MouseData* data = event.dataAs<MouseData>();

    if (data->Button == MOUSE_BUTTON_LEFT)
    {
        pBall->setTarget(data->Pos);
        pScene->setLayerEnabled(0, true);
    }
}
