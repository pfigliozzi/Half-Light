#pragma once

#if defined(_WIN32) || defined(WIN32)
#    if defined(CORSAIRLFX_DLL)
#        define CORSAIRLFX_EXPORT __declspec(dllexport)
#    else
#        define CORSAIRLFX_EXPORT __declspec(dllimport)
#    endif
#else
#    define CORSAIRLFX_EXPORT __attribute__((visibility("default")))
#endif // WIN32
