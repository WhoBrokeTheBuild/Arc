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
			_pUnit;

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

        virtual void update( const FrameData* data )  { };
		virtual void render( const RenderData* data ) { };

		bool removeSelf( void );

		inline Unit* getUnit( void ) const { return _pUnit; }
		inline void setUnit( Unit* unit ) { _pUnit = unit; }

	}; // class Component

} // namespace Arc

#endif // __ARC_COMPONENT_H__
