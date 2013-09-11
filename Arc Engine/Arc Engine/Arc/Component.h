#pragma once

#ifndef __ARC_COMPONENT_H__
#define __ARC_COMPONENT_H__

#include "Common.h"
#include "EventDispatcher.h"

namespace Arc
{
	class Unit;

	class Component :
        public EventDispatcher
	{
	protected:

		Unit*
			_pParent;

		void setParentUnit( Unit* unit ) { _pParent = unit; }

	public:

		bool
			Enabled,
			Visible;

		static const EventType
			EVENT_UNIT_CHANGED;

		Component( void );
		virtual ~Component() { term(); }

		virtual void init( Unit* parent );
		virtual void term( void );

		virtual inline string toString( void ) const { return "Component"; }

		virtual void update( const Event& event );
        virtual void render( const Event& event );

        virtual void update( const FrameData* data )  { };
		virtual void render( const RenderData* data ) { };

		bool removeSelf();

		inline Unit* getParentUnit( void ) const { return _pParent; }

	}; // class Component

} // namespace Arc

#endif // __ARC_COMPONENT_H__
