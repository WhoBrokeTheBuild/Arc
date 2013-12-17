#pragma once

#ifndef __ARC_ANGLE_H__
#define __ARC_ANGLE_H__

#include "ManagedObject.h"
#include "ISerializable.h"

#include "Functions.h"
#include "Vector2.h"
#include <string>

using std::string;

namespace Arc
{
    enum AngleType
    {
        INVALID_ANGLE_TYPE = -1,

        ANGLE_TYPE_DEG,
        ANGLE_TYPE_RAD,

        NUM_ANGLE_TYPES

    }; // enum AngleType

    const string ANGLE_TYPE_NAMES[NUM_ANGLE_TYPES] =
    {
        "Degrees",
        "Radians"
    };

    class Angle :
        public ManagedObject,
        public ISerializable
    {
    protected:

        float _degrees;

    public:

        static const Angle ZERO;

        static const Angle HALF_CIRCLE;

		static const Angle QUARTER_CIRCLE;

        static const Angle UP;

        static const Angle DOWN;

        static const Angle LEFT;

        static const Angle RIGHT;

        Angle( void ) 
			: _degrees(0.0f)
		{ }

        Angle( float value, AngleType type = ANGLE_TYPE_DEG )
        {
            switch (type)
            {
            case ANGLE_TYPE_DEG:

                setDeg(value);

                break;
            case ANGLE_TYPE_RAD:

                setRad(value);

                break;
            default:
                break;
            }
        }

        virtual inline string toString( void ) const
        {
            stringstream ss;
            ss << "Angle [Deg: " << getDeg() << ", Rad: " << getRad() << "]";
            return ss.str();
        }

		inline static Angle rand( float min, float max, AngleType type = ANGLE_TYPE_DEG )
		{
			return Angle(randFloat(min, max), type);
		}

        virtual int serialize( ostream& stream );
		virtual int deserialize( istream& stream );

		virtual int serialize( Buffer& buffer);
		virtual int deserialize( Buffer& buffer );

        virtual inline float getDeg( void ) const { return _degrees; }
        virtual inline float getRad( void ) const { return AngleHelper::toRad(_degrees); }

        virtual void setDeg( float value );
        virtual inline void setRad( float value ) { setDeg(AngleHelper::toDeg(value)); }

        virtual inline float getCos( void ) const { return cosf(getRad()); }
        virtual inline float getSin( void ) const { return sinf(getRad()); }

		virtual Vector2 getVector2( void ) const { return Vector2(getCos(), getSin()); }

        inline void addAngle( float value, AngleType type ) { Angle other = Angle(value, type); *this += other; }
        inline void subAngle( float value, AngleType type ) { addAngle(-value, type); }

        const Angle operator+( const Angle& rhs ) const;
        const Angle operator-( const Angle& rhs ) const;
        const Angle operator*( float value ) const;
        const Angle operator/( float value ) const;

        Angle& operator+=( const Angle& rhs );
        Angle& operator-=( const Angle& rhs );
        Angle& operator*=( float value );
        Angle& operator/=( float value );
        Angle& operator= ( const Angle& rhs );

        bool operator==( const Angle& rhs ) const;
        bool operator!=( const Angle& rhs ) const;

        bool operator<( const Angle& rhs ) const;
        bool operator>( const Angle& rhs ) const;

        bool operator<=( const Angle& rhs ) const;
        bool operator>=( const Angle& rhs ) const;

    }; // class Angle

} // namespace Arc

#endif // __ARC_ANGLE_H__
