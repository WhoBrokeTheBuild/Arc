#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>
#include <Arc/ShapeComponent.h>
#include <Arc/PhysicsComponent.h>
#include <Arc/TextComponent.h>

TestApp::TestApp( void )
    : Program()
{
    initAll(Size(610.0f), "Testing");

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(20, 20, 20));

	_pFont = New Font("assets/ds-digital.ttf", 20);
	_pFPSText = New RenderedText("0", _pFont);

	_pRootMenu = New SpinMenu(Point(250.0f), _pFont);
	_pCurrMenu = _pRootMenu;

	SpinMenu* optionsMenu = New SpinMenu(Point(250.0f), _pFont);

	_pRootMenu->addItem("Start");
	_pRootMenu->addItem("Options", MenuActions::MENU_ACT_MENU, optionsMenu);
	_pRootMenu->addItem("Save");
	_pRootMenu->addItem("Load");
	_pRootMenu->addItem("Quit", MenuActions::MENU_ACT_EXIT);

	optionsMenu->addItem("Something");
	optionsMenu->addItem("Back", MenuActions::MENU_ACT_MENU, _pRootMenu);

	optionsMenu->setParentMenu(_pRootMenu);

	_pRootMenu->activate();

    pScene = New Scene();
	pResourceManager = New ResourceManager();

	pResourceManager->addSound(New Sound("assets/menu-moved.wav"));
	pResourceManager->addSound(New Sound("assets/menu-selected.wav"));

	pScene->addUnit(_pRootMenu, 0);
	pScene->addUnit(optionsMenu, 0);
}

TestApp::~TestApp( void )
{
    delete pScene;

	delete pResourceManager;

    delete _pFont;
    delete _pFPSText;
}

void TestApp::update( const Event& event )
{
    const FrameData* data = event.dataAs<FrameData>();
	
    stringstream ss;
    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    _pFPSText->setText(ss.str());
}

void TestApp::render( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->getRenderTarget();
}

void TestApp::renderEnd( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->getRenderTarget();
	
    renderTarget->drawText(Point(25), _pFPSText, Color::BLACK);
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

	switch (data->Key)
	{
	case KeyboardKey::KEY_LEFT:

		pResourceManager->getSound(0)->play();
		_pCurrMenu->tickLeft();

		break;
	case KeyboardKey::KEY_RIGHT:

		pResourceManager->getSound(0)->play();
		_pCurrMenu->tickRight();

		break;
	case KeyboardKey::KEY_ENTER:

		pResourceManager->getSound(1)->play();
		SpinMenu* menu = _pCurrMenu->select();

		if (menu != nullptr)
		{
			_pCurrMenu->deactivate();
			_pCurrMenu = menu;
			_pCurrMenu->activate();
		}

		break;
	}
}