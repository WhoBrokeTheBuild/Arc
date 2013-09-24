#pragma once

#ifndef __ARC_ITEXT_INPUT_LISTENER_H__
#define __ARC_ITEXT_INPUT_LISTENER_H__

#include "Common.h"
#include "TextInputSource.h"

namespace Arc
{
    class ITextInputListener
    {
    public:

        inline ITextInputListener( void )
		{
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_CHAR,      this, &ITextInputListener::textInputChar);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_NEWLINE,   this, &ITextInputListener::textInputNewline);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_BACKSPACE, this, &ITextInputListener::textInputBackspace);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_DELETE,    this, &ITextInputListener::textInputDelete);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_TAB,       this, &ITextInputListener::textInputTab);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_ARROWS,    this, &ITextInputListener::textInputArrows);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_HOME_END,  this, &ITextInputListener::textInputHomeEnd);
		}

        virtual inline ~ITextInputListener( void )
		{
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_HOME_END,  this, &ITextInputListener::textInputHomeEnd);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_ARROWS,    this, &ITextInputListener::textInputArrows);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_TAB,       this, &ITextInputListener::textInputTab);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_DELETE,    this, &ITextInputListener::textInputDelete);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_BACKSPACE, this, &ITextInputListener::textInputBackspace);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_NEWLINE,   this, &ITextInputListener::textInputNewline);
            gpEventDispatcher->addEventListener(TextInputSource::EVENT_TEXT_INPUT_CHAR,      this, &ITextInputListener::textInputChar);
		}

        virtual inline void textInputChar      ( const Event& event) { };
        virtual inline void textInputNewline   ( const Event& event) { };
        virtual inline void textInputBackspace ( const Event& event) { };
        virtual inline void textInputDelete    ( const Event& event) { };
        virtual inline void textInputTab       ( const Event& event) { };
        virtual inline void textInputArrows    ( const Event& event) { };
        virtual inline void textInputHomeEnd   ( const Event& event) { };

    }; // class ITextInputListener

} // namespace Arc

#endif
