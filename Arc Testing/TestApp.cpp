#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>
#include "Arc/ShapeComponent.h"
#include "Arc/PhysicsComponent.h"

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

	pResourceManager = New ResourceManager();
	pResourceManager->init();

    Unit* unit = New Unit();
    unit->init(Vector2(100.0f));

    Texture* tex = New Texture();
    tex->init("assets/test.png");

	pResourceManager->addTexture(tex);

	ShapeComponent *cmp = New ShapeComponent();
	cmp->init(Vector2::ZERO, Angle::ZERO, Color::BLUE);
	cmp->setCircle(1.0f);

	unit->addComponent(cmp);

	cmp = New ShapeComponent();
	cmp->init(Vector2::ZERO, Angle::ZERO, Color::RED, 100.0f);
	cmp->setCircle(100.0f);

	unit->addComponent(cmp);

	cmp = New ShapeComponent();
	cmp->init(Vector2::ZERO, Angle(randFloat(0.0f, (float)PI2), ANGLE_TYPE_RAD), Color::GREEN);
	cmp->setRectangle(Size(50.0f));

	unit->addComponent(cmp);

	PhysicsComponent* phys = New PhysicsComponent();
	phys->init(Vector2(randFloat(-2.0f, 2.0f), randFloat(-2.0f, 2.0f)), Vector2(randFloat(-0.1f, 0.1f), randFloat(-0.1f, 0.1f)));

	unit->addComponent(phys);

    pScene->addUnit(unit, 0);

    pFont = New Font();
    pFont->init("assets/ds-digital.ttf", 20);

    pFPSText = New RenderedText();
    pFPSText->init("0", pFont);
}

void TestApp::term( void )
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
