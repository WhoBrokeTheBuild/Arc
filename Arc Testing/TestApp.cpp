#include "TestApp.h"

TestApp::TestApp(void)
{
}

TestApp::~TestApp(void)
{
    term();
}

void TestApp::init( void )
{
    ArcApp::init(Size(600), "Test Arc");
    IKeyboardListener::init();

    scene = New Scene();
    scene->init();

    tex  = New Texture();
    anim = New Animation();

    sprites = ArrayList<Sprite*>();

    Rect source = Rect(0, 0, 255, 255);
    for (unsigned int i = 0; i < 8; ++i)
    {
        sprites.add(New Sprite());
        sprites.back()->init(tex, source);
        source.X += source.Width;
    }

    tex->init("assets/test.png");
    anim->init(sprites, 100);

    pTest = New Test();
    pTest->init(anim);
    pTest->BlendColor = Color::BLUE;
    pTest->Pos = Vector2::ZERO;
    pTest->Depth = 1.0f;

    pTest2 = New Test();
    pTest2->init(anim);
    pTest2->BlendColor = Color::RED;
    pTest2->Pos = Vector2(100, 0);
    pTest2->Depth = 1.0f;

    pTest3 = New Test();
    pTest3->init(anim);
    pTest3->BlendColor = Color::GREEN;
    pTest3->Pos = Vector2(0, 300);
    pTest3->Depth = 1.0f;

    pTest4 = New Test();
    pTest4->init(anim);
    pTest4->BlendColor = Color::BLACK;
    pTest4->Pos = Vector2(100, 300);

    scene->addUnit(pTest,  1);
    scene->addUnit(pTest2, 1);
    scene->addUnit(pTest3, 0);
    scene->addUnit(pTest4, 0);
}

void TestApp::term( void )
{
    delete scene;

    delete anim;

    for (unsigned int i = 0; i < sprites.size(); ++i)
    {
        delete sprites[i];
    }
    sprites.clear();

    delete tex;
}

void TestApp::update( const Event& event )
{
    //const FrameData* data = event.dataAs<FrameData>();
}

void TestApp::render( const Event& event )
{
}

void TestApp::keyPressed( const Event& event )
{
    const KeyData* data = event.dataAs<KeyData>();

    switch (data->Key)
    {
    case KEY_ENTER:

        scene->toggleLayerVisible(0);

        break;
    case KEY_SPACE:

        scene->toggleLayerEnabled(0);

        break;
    default:
        break;
    }
}
