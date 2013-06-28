#include "TextInputSource.h"
#include "ArcApp.h"

const EventType TextInputSource::EVENT_TEXT_INPUT_CHAR      = "textInputChar";
const EventType TextInputSource::EVENT_TEXT_INPUT_NEWLINE   = "textInputNewline";
const EventType TextInputSource::EVENT_TEXT_INPUT_BACKSPACE = "textInputBackspace";
const EventType TextInputSource::EVENT_TEXT_INPUT_DELETE    = "textInputDelete";
const EventType TextInputSource::EVENT_TEXT_INPUT_TAB       = "textInputTab";
const EventType TextInputSource::EVENT_TEXT_INPUT_ARROWS    = "textInputArrows";
const EventType TextInputSource::EVENT_TEXT_INPUT_HOME_END  = "textInputHomeEnd";

TextInputSource::TextInputSource(void)
{
}

TextInputSource::~TextInputSource(void)
{
    term();
}

std::string TextInputSource::toString( void ) const
{
    return "Text Input Source";
}

void TextInputSource::init( void )
{
    IKeyboardListener::init();

    _shiftDown = false;
    _capsLockDown = false;

    _validInputs = vector<KeyboardKey>();

    _validInputs.push_back(KEY_BACKSPACE);
    _validInputs.push_back(KEY_ENTER);
    _validInputs.push_back(KEY_TAB);

    _validInputs.push_back(KEY_LSHIFT);
    _validInputs.push_back(KEY_RSHIFT);
    _validInputs.push_back(KEY_CAPS_LOCK);

    _validInputs.push_back(KEY_SPACE);
    _validInputs.push_back(KEY_GRAVE);
    _validInputs.push_back(KEY_SEMICOLON);
    _validInputs.push_back(KEY_QUOTE);
    _validInputs.push_back(KEY_BRACKET_OPEN);
    _validInputs.push_back(KEY_BRACKET_CLOSE);
    _validInputs.push_back(KEY_COMMA);
    _validInputs.push_back(KEY_PERIOD);
    _validInputs.push_back(KEY_DASH);
    _validInputs.push_back(KEY_EQUALS);
    _validInputs.push_back(KEY_SLASH);
    _validInputs.push_back(KEY_BACKSLASH);

    for (int i = 0; i < 10; ++i)
    {
        _validInputs.push_back((KeyboardKey)(KEY_0     + i));
        _validInputs.push_back((KeyboardKey)(KEY_PAD_0 + i));
    }

    for (int i = 0; i < 26; ++i)
    {
        _validInputs.push_back((KeyboardKey)(KEY_A + i));
    }

    _validInputs.push_back(KEY_UP);
    _validInputs.push_back(KEY_DOWN);
    _validInputs.push_back(KEY_LEFT);
    _validInputs.push_back(KEY_RIGHT);

    _validInputs.push_back(KEY_HOME);
    _validInputs.push_back(KEY_END);

    gpEventDispatcher->addEventListener(ArcApp::EVENT_FRAME, this, &TextInputSource::update);
}

void TextInputSource::term( void )
{
    gpEventDispatcher->removeEventListener(ArcApp::EVENT_FRAME, this, &TextInputSource::update);
}

void TextInputSource::update( const Event& event )
{

}

void TextInputSource::keyPressed( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();

    KeyboardKey key = data->Key;

    if (vectorContains(_validInputs, key))
    {
        switch (key)
        {
        case KEY_LSHIFT:
        case KEY_RSHIFT:

            _shiftDown = true;

            break;
        case KEY_CAPS_LOCK:

            _capsLockDown = true;

            break;
        case KEY_ENTER:

            gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_NEWLINE));

            break;
        case KEY_TAB:

            gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_TAB));

            break;
        case KEY_BACKSPACE:

            gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_BACKSPACE));

            break;
        case KEY_DELETE:

            gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_DELETE));

            break;
        case KEY_HOME:
        case KEY_END:
            {
                Direction dir = INVALID_DIRECTION;

                if (key == KEY_HOME)
                {
                    dir = DIR_WEST;
                }
                else if (key == KEY_END)
                {
                    dir = DIR_EAST;
                }

                gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_HOME_END, TextInputData(dir)));
            }
            break;
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            {
                Direction dir = INVALID_DIRECTION;

                switch (key)
                {
                case KEY_UP:

                    dir = Direction::DIR_NORTH;

                    break;
                case KEY_DOWN:

                    dir = Direction::DIR_SOUTH;

                    break;
                case KEY_LEFT:

                    dir = Direction::DIR_WEST;

                    break;
                case KEY_RIGHT:

                    dir = Direction::DIR_EAST;

                    break;
                }

                gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_ARROWS, TextInputData(dir)));
            }
            break;
        default:
            {
                bool shifted = (!_capsLockDown && _shiftDown) || (_capsLockDown && !_shiftDown);

                gpEventDispatcher->dispatchEvent(Event(EVENT_TEXT_INPUT_CHAR, TextInputData(KeyToChar(key, shifted))));
            }
            break;
        }
    }
}

void TextInputSource::keyReleased( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();

    if (vectorContains(_validInputs, data->Key))
    {
        switch (data->Key)
        {
        case KEY_LSHIFT:
        case KEY_RSHIFT:

            _shiftDown = false;

            break;
        case KEY_CAPS_LOCK:

            _capsLockDown = false;

            break;
        default:
            break;
        }
    }
}

void TextInputSource::keyHeld( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();
}