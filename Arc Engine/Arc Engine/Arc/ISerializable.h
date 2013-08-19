#pragma once

#ifndef __ARC_ISERIALIZABLE_H__
#define __ARC_ISERIALIZABLE_H__

#include <iostream>

using std::ostream;
using std::istream;

namespace Arc
{
    class ISerializable
    {
        protected:

        public:

            virtual int serialize( ostream &stream ) = 0;
            virtual int deserialize( istream &stream ) = 0;

    }; // class ISerializable

} // namespace Arc

#endif // __ARC_ISERIALIZABLE_H__
