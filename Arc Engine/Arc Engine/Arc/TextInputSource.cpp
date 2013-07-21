#include "TextInputSource.h"
#include "Program.h"

const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_CHAR      = "textInputChar";
const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_NEWLINE   = "textInputNewline";
const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_BACKSPACE = "textInputBackspace";
const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_DELETE    = "textInputDelete";
const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_TAB       = "textInputTab";
const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_ARROWS    = "textInputArrows";
const Arc::EventType Arc::TextInputSource::EVENT_TEXT_INPUT_HOME_END  = "textInputHomeEnd";

Arc::TextInputSource::TextInputSource( void )
{
    _shiftDown    = false;
    _capsLockDown = false;
    _validInputs  = ArrayList<KeyboardKey>();
}

void Arc::TextInputSource::init( void )
{
    IKeyboardListener::init();

    _shiftDown = false;
    _capsLockDown = false;

    _validInputs.add(KEY_BACKSPACE);
    _validInputs.add(KEY_ENTER);
    _validInputs.add(KEY_TAB);

    _validInputs.add(KEY_LSHIFT);
    _validInputs.add(KEY_RSHIFT);
    _validInputs.add(KEY_CAPS_LOCK);

    _validInputs.add(KEY_SPACE);
    _validInputs.add(KEY_GRAVE);
    _validInputs.add(KEY_SEMICOLON);
    _validInputs.add(KEY_QUOTE);
    _validInputs.add(KEY_BRACKET_OPEN);
    _validInputs.add(KEY_BRACKET_CLOSE);
    _validInputs.add(KEY_COMMA);
    _validInputs.add(KEY_PERIOD);
    _validInputs.add(KEY_DASH);
    _validInputs.add(KEY_EQUALS);
    _validInputs.add(KEY_SLASH);
    _validInputs.add(KEY_BACKSLASH);

    for (int i = 0; i < 10; ++i)
    {
        _validInputs.add((KeyboardKey)(KEY_0 + i))->add((KeyboardKey)(KEY_PAD_0 + i));
    }

    for (int i = 0; i < 26; ++i)
    {
        _validInputs.add((KeyboardKey)(KEY_A + i));
    }

    _validInputs.add(KEY_UP);
    _validInputs.add(KEY_DOWN);
    _validInputs.add(KEY_LEFT);
    _validInputs.add(KEY_RIGHT);

    _validInputs.add(KEY_HOME);
    _validInputs.add(KEY_END);

    gpEventDispatcher->addEventListener(Program::EVENT_UPDATE, this, &TextInputSource::update);
}

void Arc::TextInputSource::term( void )
{
    gpEventDispatcher->removeEventListener(Program::EVENT_UPDATE, this, &TextInputSource::update);
}

void Arc::TextInputSource::update( const Event& event )
{

}

void Arc::TextInputSource::keyPressed( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();

    KeyboardKey key = data->Key;

    if (_validInputs.contains(key))
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
                default:
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

void Arc::TextInputSource::keyReleased( const Event& event )
{
    const KeyData *data = event.dataAs<KeyData>();

    if (_validInputs.contains(data->Key))
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

void Arc::TextInputSource::keyHeld( const Event& event )
{
    //const KeyData *data = event.dataAs<KeyData>();
}
