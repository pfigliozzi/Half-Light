#pragma once

#if defined(_WIN32) || defined(WIN32)
#    if defined(CORSAIRLAYERS_DLL)
#        define CORSAIRLAYERS_EXPORT __declspec(dllexport)
#    else
#        define CORSAIRLAYERS_EXPORT __declspec(dllimport)
#    endif
#else
#    define CORSAIRLAYERS_EXPORT __attribute__((visibility("default")))
#endif // WIN32

