#ifdef _WIN32
#include "src/windows_Shell.h"
#else
#include "src/ubuntu_Shell.h"
#endif

int main() {
    CommandInfo info;
    string command;
    Shell shell;

    // shell.Help();

    while (true) {
        cout << "<< ";
        getline(cin, command);

        if (command.empty()) continue;  // skip empty

        info = shell.GetCommandInfo(command);

        cout << endl << "Command: " << info.Type << endl;
        cout << "Description: " << info.Description << endl;
    }
    // shell.Help(CommandType::cd, "help <command>");
}
