#include <process.h>
#include <windows.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Function to split a string into a vector of strings based on a delimiter
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to execute a command
void executeCommand(const string& command) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Use CreateProcess to execute the command
    if (!CreateProcess(NULL,  // No module name (use command line)
                       (LPSTR)command.c_str(),  // Command line
                       NULL,   // Process handle not inheritable
                       NULL,   // Thread handle not inheritable
                       FALSE,  // Set handle inheritance to FALSE
                       0,      // No creation flags
                       NULL,   // Use parent's environment block
                       NULL,   // Use parent's starting directory
                       &si,    // Pointer to STARTUPINFO structure
                       &pi)    // Pointer to PROCESS_INFORMATION structure
    ) {
        cerr << "Error executing command: " << command << endl;
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    string command;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "exit") {
            break;
        } else if (!command.empty()) {
            executeCommand(command);
        }
    }
    return 0;
}
