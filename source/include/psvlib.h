#ifndef PSVLIB_H
#define PSVLIB_H

#if defined(WIN32) && !defined(_PSV_TEST)
    #if !defined(_PSVLIB_DLL)
        #define PSVLIB_API   __declspec( dllimport )
    #else
        #define PSVLIB_API   __declspec( dllexport )
    #endif
#else
    #define PSVLIB_API
#endif


#endif // PSVLIB_H
