#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>
#include "Arc/ShapeComponent.h"
#include "Arc/PhysicsComponent.h"

TestApp::TestApp( void )
    : Program()
{
    initAll(Size(600, 600), "Testing");

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(150, 150, 150));

    pScene = New Scene();
	pResourceManager = New ResourceManager();

    Unit* unit = New Unit(Vector2(100.0f));

	pScene->addUnit(unit, 0);

    Texture* tex = New Texture("assets/test.png");
	pResourceManager->addTexture(tex);

    unit->addNewShapeComponent(Vector2::ZERO, Angle::ZERO, Color::BLUE)->setCircle(1.0f);
	unit->addNewShapeComponent(Vector2::ZERO, Angle::ZERO, Color::RED, 100.0f)->setCircle(100.0f);
    unit->addNewShapeComponent(Vector2::ZERO, Angle::rand(0.0f, (float)PI2, ANGLE_TYPE_RAD), Color::GREEN, Vector2(25.0f))->setRectangle(Size(50.0f));
    unit->addNewPhysicsComponent(Vector2::rand(-2.0f, 2.0f, -2.0f, 2.0f), Vector2::rand(-0.1f, 0.1f, -0.1f, 0.1f));

	PhysicsComponent* physicsCmp = unit->getFirstPhysicsComponent();
	if (physicsCmp != nullptr)
	{
	unit->getFirstPhysicsComponent()->Vel = Vector2::ZERO;
	unit->getFirstPhysicsComponent()->Acc = Vector2::ZERO;
	}

    pFont = New Font("assets/ds-digital.ttf", 20);
    pFPSText = New RenderedText("0", pFont);
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
