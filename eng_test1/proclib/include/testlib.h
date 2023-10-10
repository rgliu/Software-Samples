#pragma once

#if (defined(_MSC_VER))
#define PLATFORM_EXPORT __declspec(dllexport)
#elif defined(__APPLE__) || defined(__clang__) || defined(__GNUC__)
#define PLATFORM_EXPORT __attribute__ ((visibility("default")))
#else
#define PLATFORM_EXPORT
#endif

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

    // The C interface down into a c++ library


    // Create an instance of the Proc and return an ID
    PLATFORM_EXPORT std::size_t CreateProc(const char* name, const char* key, const char* region);

    // Run Proc for the specified ID
    PLATFORM_EXPORT int RunProc(std::size_t pid, int process_length);

    // Print Proc name for the specified ID
    PLATFORM_EXPORT int GetProcName(std::size_t pid);

    // shutdown the proc and free memory
    PLATFORM_EXPORT int DestroyProc(std::size_t pid);




#ifdef __cplusplus
}
#endif
