#ifdef _WIN32
#include "src/Shells/Windows.h"
#else
#include "src/Shells/Ubuntu.h"
#endif

int main() {
    Shell shell;

    shell.Help();

    // shell.Help(CommandType::cd, "help <command>");
}
