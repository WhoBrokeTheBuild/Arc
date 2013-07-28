#include "InputFunc.h"

Arc::KeyboardKey Arc::SDLKeyToKey( SDLKey sdlKey )
{
    KeyboardKey key = INVALID_KEY;;

    switch (sdlKey)
    {
    case SDLK_UNKNOWN:

        key = KEY_UNKNOWN;

        break;
    case SDLK_BACKSPACE:

        key = KEY_BACKSPACE;

        break;
    case SDLK_TAB:

        key = KEY_TAB;

        break;
    case SDLK_ESCAPE:

        key = KEY_ESCAPE;

        break;
    case SDLK_SPACE:

        key = KEY_SPACE;

        break;
    case SDLK_CAPSLOCK:

        key = KEY_CAPS_LOCK;

        break;
    case SDLK_END:

        key = KEY_END;

        break;
    case SDLK_HOME:

        key = KEY_HOME;

        break;
    case SDLK_PAGEUP:

        key = KEY_PAGE_UP;

        break;
    case SDLK_PAGEDOWN:

        key = KEY_PAGE_DOWN;

        break;
    case SDLK_INSERT:

        key = KEY_INSERT;

        break;
    case SDLK_DELETE:

        key = KEY_DELETE;

        break;
    case SDLK_BACKQUOTE:

        key = KEY_GRAVE;

        break;
    case SDLK_SEMICOLON:

        key = KEY_SEMICOLON;

        break;
    case SDLK_QUOTE:

        key = KEY_QUOTE;

        break;
    case SDLK_LEFTBRACKET:

        key = KEY_BRACKET_OPEN;

        break;
    case SDLK_RIGHTBRACKET:

        key = KEY_BRACKET_CLOSE;

        break;
    case SDLK_COMMA:

        key = KEY_COMMA;

        break;
    case SDLK_PERIOD:

        key = KEY_PERIOD;

        break;
    case SDLK_SLASH:

        key = KEY_SLASH;

        break;
    case SDLK_BACKSLASH:

        key = KEY_BACKSLASH;

        break;
    case SDLK_MINUS:

        key = KEY_DASH;

        break;
    case SDLK_EQUALS:

        key = KEY_EQUALS;

        break;
    case SDLK_RETURN:

        key = KEY_ENTER;

        break;
    case SDLK_0:
    case SDLK_1:
    case SDLK_2:
    case SDLK_3:
    case SDLK_4:
    case SDLK_5:
    case SDLK_6:
    case SDLK_7:
    case SDLK_8:
    case SDLK_9:

        key = (KeyboardKey)(KEY_0 + (sdlKey - SDLK_0));

        break;
    case SDLK_KP0:
    case SDLK_KP1:
    case SDLK_KP2:
    case SDLK_KP3:
    case SDLK_KP4:
    case SDLK_KP5:
    case SDLK_KP6:
    case SDLK_KP7:
    case SDLK_KP8:
    case SDLK_KP9:

        key = (KeyboardKey)(KEY_PAD_0 + (sdlKey - SDLK_KP0));

        break;
    case SDLK_LSHIFT:

        key = KEY_LSHIFT;

        break;
    case SDLK_RSHIFT:

        key = KEY_RSHIFT;

        break;
    case SDLK_LCTRL:

        key = KEY_LCONTROL;

        break;
    case SDLK_RCTRL:

        key = KEY_RCONTROL;

        break;
    case SDLK_LALT:

        key = KEY_LALT;

        break;
    case SDLK_RALT:

        key = KEY_RALT;

        break;
    case SDLK_a:
    case SDLK_b:
    case SDLK_c:
    case SDLK_d:
    case SDLK_e:
    case SDLK_f:
    case SDLK_g:
    case SDLK_h:
    case SDLK_i:
    case SDLK_j:
    case SDLK_k:
    case SDLK_l:
    case SDLK_m:
    case SDLK_n:
    case SDLK_o:
    case SDLK_p:
    case SDLK_q:
    case SDLK_r:
    case SDLK_s:
    case SDLK_t:
    case SDLK_u:
    case SDLK_v:
    case SDLK_w:
    case SDLK_x:
    case SDLK_y:
    case SDLK_z:

        key = (KeyboardKey)(KEY_A + (sdlKey - SDLK_a));

        break;
    case SDLK_UP:

        key = KEY_UP;

        break;
    case SDLK_DOWN:

        key = KEY_DOWN;

        break;
    case SDLK_LEFT:

        key = KEY_LEFT;

        break;
    case SDLK_RIGHT:

        key = KEY_RIGHT;

        break;
    case SDLK_F1:
    case SDLK_F2:
    case SDLK_F3:
    case SDLK_F4:
    case SDLK_F5:
    case SDLK_F6:
    case SDLK_F7:
    case SDLK_F8:
    case SDLK_F9:
    case SDLK_F10:
    case SDLK_F11:
    case SDLK_F12:

        key = (KeyboardKey)(KEY_F1 + (SDLK_F1 - sdlKey));

        break;
    default:
        break;
    }

    return key;
}

SDLKey Arc::KeyToSDLKey( KeyboardKey key )
{
    SDLKey sdlKey = SDLK_UNKNOWN;;

    switch (key)
    {
    case KEY_UNKNOWN:

        sdlKey = SDLK_UNKNOWN;

        break;
    case KEY_BACKSPACE:

        sdlKey = SDLK_BACKSPACE;

        break;
    case KEY_TAB:

        sdlKey = SDLK_TAB;

        break;
    case KEY_CAPS_LOCK:

        sdlKey = SDLK_CAPSLOCK;

        break;
    case KEY_ESCAPE:

        sdlKey = SDLK_ESCAPE;

        break;
    case KEY_SPACE:

        sdlKey = SDLK_SPACE;

        break;
    case KEY_END:

        sdlKey = SDLK_END;

        break;
    case KEY_HOME:

        sdlKey = SDLK_HOME;

        break;
    case KEY_PAGE_UP:

        sdlKey = SDLK_PAGEUP;

        break;
    case KEY_PAGE_DOWN:

        sdlKey = SDLK_PAGEDOWN;

        break;
    case KEY_INSERT:

        sdlKey = SDLK_INSERT;

        break;
    case KEY_DELETE:

        sdlKey = SDLK_DELETE;

        break;
    case KEY_GRAVE:

        sdlKey = SDLK_BACKQUOTE;

        break;
    case KEY_SEMICOLON:

        sdlKey = SDLK_SEMICOLON;

        break;
    case KEY_QUOTE:

        sdlKey = SDLK_QUOTE;

        break;
    case KEY_BRACKET_OPEN:

        sdlKey = SDLK_LEFTBRACKET;

        break;
    case KEY_BRACKET_CLOSE:

        sdlKey = SDLK_RIGHTBRACKET;

        break;
    case KEY_COMMA:

        sdlKey = SDLK_COMMA;

        break;
    case KEY_PERIOD:

        sdlKey = SDLK_PERIOD;

        break;
    case KEY_SLASH:

        sdlKey = SDLK_SLASH;

        break;
    case KEY_BACKSLASH:

        sdlKey = SDLK_BACKSLASH;

        break;
    case KEY_DASH:

        sdlKey = SDLK_MINUS;

        break;
    case KEY_EQUALS:

        sdlKey = SDLK_EQUALS;

        break;
    case KEY_ENTER:

        sdlKey = SDLK_RETURN;

        break;
    case KEY_0:
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
    case KEY_9:

        sdlKey = (SDLKey)(SDLK_0 + (key - KEY_0));

        break;
    case KEY_PAD_0:
    case KEY_PAD_1:
    case KEY_PAD_2:
    case KEY_PAD_3:
    case KEY_PAD_4:
    case KEY_PAD_5:
    case KEY_PAD_6:
    case KEY_PAD_7:
    case KEY_PAD_8:
    case KEY_PAD_9:

        sdlKey = (SDLKey)(SDLK_KP0 + (key - KEY_PAD_0));

        break;
    case KEY_LSHIFT:

        sdlKey = SDLK_LSHIFT;

        break;
    case KEY_RSHIFT:

        sdlKey = SDLK_RSHIFT;

        break;
    case KEY_LCONTROL:

        sdlKey = SDLK_LCTRL;

        break;
    case KEY_RCONTROL:

        sdlKey = SDLK_RCTRL;

        break;
    case KEY_LALT:

        sdlKey = SDLK_LALT;

        break;
    case KEY_RALT:

        sdlKey = SDLK_RALT;

        break;
    case KEY_A:
    case KEY_B:
    case KEY_C:
    case KEY_D:
    case KEY_E:
    case KEY_F:
    case KEY_G:
    case KEY_H:
    case KEY_I:
    case KEY_J:
    case KEY_K:
    case KEY_L:
    case KEY_M:
    case KEY_N:
    case KEY_O:
    case KEY_P:
    case KEY_Q:
    case KEY_R:
    case KEY_S:
    case KEY_T:
    case KEY_U:
    case KEY_V:
    case KEY_W:
    case KEY_X:
    case KEY_Y:
    case KEY_Z:

        sdlKey = (SDLKey)(SDLK_a + (key - KEY_A));

        break;
    case KEY_UP:

        sdlKey = SDLK_UP;

        break;
    case KEY_DOWN:

        sdlKey = SDLK_DOWN;

        break;
    case KEY_LEFT:

        sdlKey = SDLK_LEFT;

        break;
    case KEY_RIGHT:

        sdlKey = SDLK_RIGHT;

        break;
    case KEY_F1:
    case KEY_F2:
    case KEY_F3:
    case KEY_F4:
    case KEY_F5:
    case KEY_F6:
    case KEY_F7:
    case KEY_F8:
    case KEY_F9:
    case KEY_F10:
    case KEY_F11:
    case KEY_F12:

        sdlKey = (SDLKey)(SDLK_F1 + (key - KEY_F1));

        break;
    default:
        break;
    }

    return sdlKey;
}

char Arc::KeyToChar( KeyboardKey key, bool shift /*= false */ )
{
    char ch = '\0';

    switch (key)
    {
    case KEY_SPACE:

        ch = ' ';

        break;
    case KEY_GRAVE:

        ch = (shift ? '~' : '`');

        break;
    case KEY_SEMICOLON:

        ch = (shift ? ':' : ';');

        break;
    case KEY_QUOTE:

        ch = (shift ? '"' : '\'');

        break;
    case KEY_BRACKET_OPEN:

        ch = (shift ? '{' : '[');

        break;
    case KEY_BRACKET_CLOSE:

        ch = (shift ? '}' : ']');

        break;
    case KEY_COMMA:

        ch = (shift ? '<' : ',');

        break;
    case KEY_PERIOD:

        ch = (shift ? '>' : '.');

        break;
    case KEY_SLASH:

        ch = (shift ? '?' : '/');

        break;
    case KEY_BACKSLASH:

        ch = (shift ? '|' : '\\');

        break;
    case KEY_DASH:

        ch = (shift ? '_' : '-');

        break;
    case KEY_EQUALS:

        ch = (shift ? '+' : '=');

        break;
    case KEY_0:
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
    case KEY_9:

        if (shift)
        {
            switch (key)
            {
            case KEY_1:

                ch = '!';

                break;
            case KEY_2:

                ch = '@';

                break;
            case KEY_3:

                ch = '#';

                break;
            case KEY_4:

                ch = '$';

                break;
            case KEY_5:

                ch = '%';

                break;
            case KEY_6:

                ch = '^';

                break;
            case KEY_7:

                ch = '&';

                break;
            case KEY_8:

                ch = '*';

                break;
            case KEY_9:

                ch = '(';

                break;
            case KEY_0:

                ch = ')';

                break;
            default:
                break;
            }
        }
        else
        {
            ch = '0' + (key - KEY_0);
        }

        break;
    case KEY_PAD_0:
    case KEY_PAD_1:
    case KEY_PAD_2:
    case KEY_PAD_3:
    case KEY_PAD_4:
    case KEY_PAD_5:
    case KEY_PAD_6:
    case KEY_PAD_7:
    case KEY_PAD_8:
    case KEY_PAD_9:

        ch = '0' + (key - KEY_PAD_0);

        break;
    case KEY_A:
    case KEY_B:
    case KEY_C:
    case KEY_D:
    case KEY_E:
    case KEY_F:
    case KEY_G:
    case KEY_H:
    case KEY_I:
    case KEY_J:
    case KEY_K:
    case KEY_L:
    case KEY_M:
    case KEY_N:
    case KEY_O:
    case KEY_P:
    case KEY_Q:
    case KEY_R:
    case KEY_S:
    case KEY_T:
    case KEY_U:
    case KEY_V:
    case KEY_W:
    case KEY_X:
    case KEY_Y:
    case KEY_Z:

        ch = (shift ? 'A' : 'a') + (key - KEY_A);

        break;
    default:
        break;
    }

    return ch;
}

Arc::MouseButton Arc::SDLMouseToMouse( int sdlButton )
{
    MouseButton button = INVALID_MOUSE_BUTTON;

    switch (sdlButton)
    {
    case SDL_BUTTON_LEFT:

        button = MOUSE_BUTTON_LEFT;

        break;
    case SDL_BUTTON_MIDDLE:

        button = MOUSE_BUTTON_MIDDLE;

        break;
    case SDL_BUTTON_RIGHT:

        button = MOUSE_BUTTON_RIGHT;

        break;
    default:
        break;
    }

    return button;
}

int Arc::MouseToSDLMouse( MouseButton button )
{
    int sdlButton = 0;

    switch (button)
    {
    case MOUSE_BUTTON_LEFT:

        sdlButton = SDL_BUTTON_LEFT;

        break;
    case MOUSE_BUTTON_MIDDLE:

        sdlButton = SDL_BUTTON_MIDDLE;

        break;
    case MOUSE_BUTTON_RIGHT:

        sdlButton = SDL_BUTTON_RIGHT;

        break;
    default:
        break;
    }

    return sdlButton;
}
