#pragma once

#ifndef __SYSTEM_COMPONENT_H__
#define __SYSTEM_COMPONENT_H__

#include "Common.h"
#include "EventDispatcher.h"

namespace Arc
{
	typedef string SystemComponentType;

	class Program;

	class SystemComponent :
		public EventDispatcher
	{
	protected:

		// The Parent Program
		Program* _pProgram;

		ArrayList<SystemComponentType> _types;

		inline void addType( const SystemComponentType& type ) { if ( ! _types.contains(type)) _types.add(type); }

	public:

		static const SystemComponentType SYS_CMP_TYPE_BASE;

		SystemComponent( Program* pProgram )
			: _pProgram(pProgram)
		{
			addType(SYS_CMP_TYPE_BASE);
		}

		virtual inline ~SystemComponent( void ) { }

		inline bool hasType( const SystemComponentType& type ) { return _types.contains(type); }

		inline ArrayList<SystemComponentType> getTypes( void ) { return _types; }

		Program* getProgram( void );

	}; // class SystemComponent

} // namespace Arc

#endif // __SYSTEM_COMPONENT_H__