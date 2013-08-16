#include "TestApp.h"

void TestApp::init( void )
{
    Program::init(Size(600), "Test Arc");
    IKeyboardListener::init();
    IMouseListener::init();

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(150, 150, 150));

    pScene = New Scene();
    pScene->init();

    Wall* wall;

    // Top

    wall = New Wall();
    wall->init(Point::ZERO, Rect(0, 0, 600, 20));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall");

    // Bottom

    wall = New Wall();
    wall->init(Point(0, 580), Rect(0, 0, 600, 20));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall");

    // Left

    wall = New Wall();
    wall->init(Point(580, 0), Rect(0, 0, 20, 600));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall");

    // Right

    wall = New Wall();
    wall->init(Point::ZERO, Rect(0, 0, 20, 600));

    pScene->addUnit(wall, 0);
    pScene->addUnitTag(wall, "wall");

    pBall = New Ball();
    pBall->init(Point(300));

    int startCount = 100;

    Ball *ball;
    for (int i = 0; i < startCount; ++i)
    {
        ball = New Ball();
        ball->init(randFloat(100, 500), randFloat(100, 500));
        ball->Vel.X = randFloat(-5.0f, 5.0f);
        ball->Vel.Y = randFloat(-5.0f, 5.0f);

        pScene->addUnit(ball, 0);
        pScene->addUnitTag(ball, "ball");
    }

    pScene->addUnit(pBall, 0);
    pScene->addUnitTag(pBall, "ball");

    pFont = New Font();
    pFont->init("assets/ds-digital.ttf", 20);

    pFPSText = New RenderedText();
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

    data->renderTarget()->drawLine(300, 0, 300, 600, Color::BLUE);
    data->renderTarget()->drawLine(0, 300, 600, 300, Color::BLUE);
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
        ArrayList<Unit*> balls = pScene->getUnitsByTag("ball");
        for (unsigned int i = 0; i < balls.size(); ++i)
        {
            ((Ball*)balls[i])->setTarget(data->Pos);
        }
    }
    else if (data->Button == MOUSE_BUTTON_RIGHT)
    {
        Ball* ball = New Ball();
        ball->init(data->Pos);

        pScene->addUnit(ball, 0);
        pScene->addUnitTag(ball, "ball");
    }
}
