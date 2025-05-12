// for non windows
#if defined(__MACH__)
#define OS "Mac OS (Unix)"
#elif defined(__unix__) || defined(__unix)
#define OS "Unix Based OS"
#endif

// shell include
#if defined(_WIN32) || defined(_WIN64)
#define OS "Windows OS"
#include "Windows/shell.cpp"
#else
#include "Unix/shell.cpp"
#endif

// if os not defined
#ifndef OS
#define OS "[OS Undetected]"
#endif