#pragma once

#ifndef __ARC_SOCKET_TYPE_H__
#define __ARC_SOCKET_TYPE_H__

#include <string>

using std::string;

namespace Arc
{
    enum SocketType
    {
        INVALID_SOCKET_TYPE = -1,

        SOCKET_TYPE_TCP,
        SOCKET_TYPE_UDP,

        NUM_SOCKET_TYPES
    };

    const string SOCKET_TYPE_NAMES[NUM_SOCKET_TYPES] = 
    {
        "TCP",
        "UDP"
    };

} // namespace Arc

#endif // __ARC_SOCKET_TYPE_H__