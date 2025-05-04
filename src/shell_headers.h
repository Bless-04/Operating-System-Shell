// for non windows
#if defined(__APPLE__) || defined(__MACH__)
#define OS "Apple Based OS"
#elif defined(__unix__) || defined(__unix)
#define OS "Unix Based OS"
#endif

// shell include
#if defined(_WIN32) || defined(_WIN64)
#define OS "Windows OS"
#include "windows_Shell.cpp"
#else
#include "ubuntu_Shell.cpp"
#endif