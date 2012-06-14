////////////////////////////////////////////////////////////
//
// Zihm C++ library
// Copyright (C) 2011-2012 Pierre-E. Brian (zinlibs@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef ZIHM_CONFIG_HPP
#define ZIHM_CONFIG_HPP


////////////////////////////////////////////////////////////
// Define the ZIHM version
////////////////////////////////////////////////////////////
#define ZIHM_VERSION_MAJOR 1
#define ZIHM_VERSION_MINOR 0

////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(ZIHM_SYSTEM_WINDOWS) && !defined(ZIHM_STATIC)
    #ifdef ZIHM_EXPORTS

     // From DLL side, we must export
        #define ZIHM_API __declspec(dllexport)

    #else

     // From client application side, we must import
        #define ZIHM_API __declspec(dllimport)

    #endif

 // For Visual C++ compilers, we also need to turn off this annoying C4251 warning.
 // You can read lots ot different things about it, but the point is the code will
 // just work fine, and so the simplest way to get rid of this warning is to disable it
    #ifdef _MSC_VER

        #pragma warning(disable : 4251)

    #endif

#else

    // Other platforms and static build don't need these export macros

    #define ZIHM_API

#endif

#endif // ZIHM_CONFIG_HPP