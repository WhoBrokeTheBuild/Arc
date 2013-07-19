#pragma once

#ifndef __ARC_DEFINES_H__
#define __ARC_DEFINES_H__

#ifdef _DEBUG
    #define DEBUG
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#define WINDOWS
#define NOGDI

#else

#define LINUX

#endif

#define OPENGL_INVALID_TEXTURE 0

#endif
