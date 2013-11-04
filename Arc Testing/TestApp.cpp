#include "TestApp.h"

#include <Arc/Unit.h>
#include <Arc/Texture.h>
#include <Arc/ImageComponent.h>
#include <Arc/ShapeComponent.h>
#include <Arc/PhysicsComponent.h>
#include <Arc/TextComponent.h>

#include "MenuAction.h"

TestApp::TestApp( void )
    : Program()
{
    initAll(Size(610.0f), "Testing");

    _pScriptingSystem->executeFile("assets/test.lua");

    _pGraphicsSystem->setClearColor(Color(20, 20, 20));

	_pFont = New Font("assets/ds-digital.ttf", 20);
	_pFPSText = New RenderedText("0", _pFont);

    pScene = New Scene();
	gpResourceManager = New ResourceManager();

	gpResourceManager->addSound(New Sound("assets/menu-moved.wav"));
	gpResourceManager->addSound(New Sound("assets/menu-selected.wav"));

	Texture *texAnim = New Texture("assets/testanim.png");
	gpResourceManager->addTexture(texAnim);
	Animation *anim = New Animation(100);
	gpResourceManager->addAnimation(anim);
	Sprite *sprite;
	
	sprite = New Sprite(texAnim, Rect(0, 0, 128, 128));
	anim->addFrame(sprite);
	gpResourceManager->addSprite(sprite);

	sprite = New Sprite(texAnim, Rect(128, 0, 128, 128));
	anim->addFrame(sprite);
	gpResourceManager->addSprite(sprite);

	sprite = New Sprite(texAnim, Rect(256, 0, 128, 128));
	anim->addFrame(sprite);
	gpResourceManager->addSprite(sprite);

	sprite = New Sprite(texAnim, Rect(382, 0, 128, 128));
	anim->addFrame(sprite);
	gpResourceManager->addSprite(sprite);

	Unit *testUnit = New Unit(Point(20, 20));
	testUnit->addNewAnimatedComponent(anim);
	pScene->addUnit(testUnit, 0);

	SpinMenu *menu = New SpinMenu(Point(250.0f), _pFont);
	MenuLevel *mainLevel = New MenuLevel(menu, _pFont);
	MenuLevel *optionsLevel = New MenuLevel(menu, _pFont);
	MenuLevel *languageLevel = New MenuLevel(menu, _pFont);

	optionsLevel->setBackLevel(mainLevel);
	languageLevel->setBackLevel(optionsLevel);

	mainLevel->addItem("Start", "Test");
	mainLevel->addItem("Options", optionsLevel);
	mainLevel->addItem("Exit", MenuActionType::MENU_ACTION_EXIT);

	optionsLevel->addItem("Volume", "Test");
	optionsLevel->addItem("SFX", "Test");
	optionsLevel->addItem("Language", languageLevel);
	optionsLevel->addItem("Vasily", "Test");
	optionsLevel->addItem("Vasily", "Test");
	optionsLevel->addItem("Back", MenuActionType::MENU_ACTION_BACK);

	languageLevel->addItem("Vasily", "Test");
	languageLevel->addItem("Vasily", "Test");
	languageLevel->addItem("Vasily", "Test");
	languageLevel->addItem("Vasily", "Test");
	languageLevel->addItem("Vasily", "Test");
	languageLevel->addItem("Back", MenuActionType::MENU_ACTION_BACK);

	menu->addLevel(mainLevel);
	menu->addLevel(optionsLevel);
	menu->addLevel(languageLevel);

	menu->switchLevel(mainLevel);

	pScene->addUnit(menu, 0);
}

TestApp::~TestApp( void )
{
    delete pScene;

	delete gpResourceManager;

    delete _pFont;
    delete _pFPSText;
}

void TestApp::update( const Event& event )
{
    const FrameData* pData = event.dataAs<FrameData>();

	pScene->update(pData);
	
    stringstream ss;
    ss.str(string());
    ss << "FPS: " << ceil(_currentFPS, 1);
    _pFPSText->setText(ss.str());
}

void TestApp::render( const Event& event )
{
    const RenderData* pData = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = pData->getRenderTarget();

	pScene->render(pData);
}

void TestApp::renderEnd( const Event& event )
{
    const RenderData* data = event.dataAs<RenderData>();
	const RenderTarget* renderTarget = data->getRenderTarget();
	
    renderTarget->drawText(Point(25), _pFPSText, Color::WHITE);
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

	switch (data->Key)
	{
	}
}