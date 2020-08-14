#pragma once

#if defined(_WIN32) || defined(WIN32)
#    if defined(CUELFX_DLL)
#        define CUELFX_EXPORT __declspec(dllexport)
#    else
#        define CUELFX_EXPORT __declspec(dllimport)
#    endif
#else
#    define CUELFX_EXPORT __attribute__((visibility("default")))
#endif // WIN32
