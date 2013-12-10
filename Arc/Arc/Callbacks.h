#pragma once

#ifndef __ARC_CALLBACKS_H__
#define __ARC_CALLBACKS_H__

#include "Common.h"
#include "ManagedObject.h"

namespace Arc
{
	/** A base class for callbacks used by events
	  */
    template <typename ReturnType, typename Param = void>
    class Callback
        : public ManagedObject
    {

        friend bool operator==( const Callback<ReturnType, Param>& lhs, const Callback<ReturnType, Param>& rhs ) { return lhs.equalTo(rhs); };
        friend bool operator!=( const Callback<ReturnType, Param>& lhs, const Callback<ReturnType, Param>& rhs ) { return !lhs.equalTo(rhs); };

    protected:

        inline virtual bool equalTo( const Callback<ReturnType, Param>& rhs ) const { return false; };

    public:

        virtual inline ~Callback( void ) { }

        virtual ReturnType invoke( Param param ) = 0;
        virtual Callback*  clone ( void )        = 0;
        virtual bool isMethodOf  ( void* object) = 0;

    }; // class Callback

	/** A static function stored as a callback for events
	  */
    template <typename ReturnType, typename Param = void>
    class StaticFunctionCallback
        : public Callback<ReturnType, Param>
    {
    protected:

        virtual bool equalTo( const Callback<ReturnType, Param>& rhs ) const
        {
            if ( const StaticFunctionCallback<ReturnType, Param>* convert = dynamic_cast<const StaticFunctionCallback<ReturnType, Param>*>(&rhs) )
            {
                return ( _function == convert->_function );
            }
            return false;
        }

    private:

		// Pointer to the static function
        ReturnType
            (*_function)(Param);

    public:

        StaticFunctionCallback(ReturnType (*function)(Param))
        {
            _function = function;
        }

		// Call the function with the (const Event& event) parameter
        inline virtual ReturnType invoke( Param param )      { return (*_function)(param); }

		// Clone the callback, preserving the data
        inline virtual StaticFunctionCallback* clone( void ) { return New StaticFunctionCallback(_function); }
        inline virtual bool isMethodOf( void* object )       { return false; }

        inline virtual string toString( void ) const { return "Static Function Callback"; };

    }; // class StaticFunctionCallback

	/** A method function and object stored as a callback for events
	  */
    template <typename ReturnType, typename Param = void, typename ObjectType = void, typename Method = void>
    class MethodCallback
        : public Callback<ReturnType, Param>
    {
    protected:

        virtual bool equalTo( const Callback<ReturnType, Param>& rhs ) const
        {
            if ( const MethodCallback<ReturnType, Param, ObjectType, Method>* convert = dynamic_cast<const MethodCallback<ReturnType, Param, ObjectType, Method>*>(&rhs) )
            {
                return ( _object == convert->_object && _method == convert->_method );
            }
            return false;
        }

    private:

		// The object to call the method on
        void*
            _object;

		// The method to call on the object
        Method
            _method;

    public:

        MethodCallback( void* object, Method method )
        {
            _object = object;
            _method = method;
        }

		// Call the function with the (const Event& event) parameter
        inline virtual ReturnType invoke( Param param ) { return (static_cast<ObjectType*>(_object)->*_method)(param); }

		// Clone the callback, preserving the data
        inline virtual MethodCallback* clone( void )    { return New MethodCallback(_object, _method); }

		// Check if the method stored belongs to the specified object
        inline virtual bool isMethodOf( void* object )  { return _object == object; }

        inline virtual string toString( void ) const { return "Method Callback"; };

    }; // class MethodCallback

} // namespace Arc

#endif // __ARC_CALLBACKS_H__
