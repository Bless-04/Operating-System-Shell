#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Models/Shell.cpp"

#pragma region 1. cd.
void Shell::Change_Directory(string path) {
    cout << "Unix Changed directory to " << path << endl;
}
#pragma endregion
