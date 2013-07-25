#include "TestApp.h"

void TestApp::init( void )
{
    Program::init(Size(600), "Test Arc");
    IKeyboardListener::init();

    _pGraphicsSystem->setClearColor(Color::PEACH);
    _targetFPS = 10000.0f;

    pScene = New Scene();
    pScene->init();

    pTestUnit = New TestUnit();
    pTestUnit->init(Point(100), New RectCollider(Point(-120.0f), Size(240.0f)), 0.0f, false);

    pTestUnit2 = New TestUnit();
    pTestUnit2->init(Point(300), New CircleCollider(Point::ZERO, 120.0f));

    pScene->addUnit(pTestUnit, 0);
    pScene->addUnit(pTestUnit2, 0);

    pScene->addUnitTag(pTestUnit,  "test");
    pScene->addUnitTag(pTestUnit2, "test");

    pFont = New Font();
    pFont->init("assets/action-is.ttf", 20);

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
    
    data->renderTarget()->drawText(Point(10), pFPSText, Color::BLACK);
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    if (data->Key == KEY_ESCAPE)
    {
        gpEventDispatcher->dispatchEvent(Event(EVENT_EXIT));
    }
}
