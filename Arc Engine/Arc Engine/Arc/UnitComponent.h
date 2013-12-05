#pragma once

#ifndef __ARC_COMPONENT_H__
#define __ARC_COMPONENT_H__

#include "Common.h"
#include "EventDispatcher.h"

namespace Arc
{
	class Unit;

	typedef string UnitComponentType;

	class UnitComponent :
        public EventDispatcher
	{
	protected:

		ArrayList<UnitComponentType> _types;

		Unit* _pUnit;

		inline void addType( const UnitComponentType& type ) { if ( ! _types.contains(type)) _types.add(type); }

	public:

		bool Enabled;
		bool Visible;

		static const UnitComponentType UNIT_CMP_TYPE_BASE;

		inline UnitComponent( Unit* pUnit )
			: _pUnit(pUnit)
		{
			addType(UNIT_CMP_TYPE_BASE);
		}

		virtual inline ~UnitComponent() { }

		virtual inline string toString( void ) const { return "Component"; }

		inline bool hasType( const UnitComponentType& type ) { return _types.contains(type); }
		inline ArrayList<UnitComponentType> getTypes( void ) { return _types; }

		bool removeSelf( void );

		inline Unit* getUnit( void ) const { return _pUnit; }
		inline void setUnit( Unit* unit ) { _pUnit = unit; }

		virtual void update( const FrameData* pData ) { };
		virtual void render( const RenderTarget* pTarget ) { };

	}; // class Component

} // namespace Arc

#endif // __ARC_COMPONENT_H__
