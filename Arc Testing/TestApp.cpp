#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>

void TestApp::init( void )
{
    Program::init();
    IKeyboardListener::init();
    IMouseListener::init();

    initAll(Size(600, 600), "Testing");

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(150, 150, 150));

    pScene = New Scene();
    pScene->init();

    Unit* unit = New Unit();
    unit->init(Vector2(100.0f));

    Texture* tex = New Texture();
    tex->init("assets/test.png");

    ImageComponent* imgCmp = New ImageComponent();
    imgCmp->init(tex);

    unit->addComponent(imgCmp);

    pScene->addUnit(unit, 0);

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
    //const FrameData* data = event.dataAs<FrameData>();

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

}
