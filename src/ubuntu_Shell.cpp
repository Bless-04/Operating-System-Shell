#include <sys/types.h>
#include <sys/wait.h>

#include "Models/Shell.h"

#pragma region 1. cd.
void Shell::Change_Directory(string path) {
    cout << "Unix Changed directory to " << path << endl;
}
#pragma endregion

#pragma region 2. clr
void Shell::Clear_Screen() { cout << "\033[2J\033[H"; }
#pragma endregion