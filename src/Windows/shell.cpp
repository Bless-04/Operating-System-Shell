/** For Defining Shell Functions that are windows specific */
#include "../Models/Shell.cpp"

#include <windows.system.h>
#include <winternl.h>

// formatter keeps reordering this

#include "cd.hpp"  // 1.
// 2. clear
#include "dir.hpp"      // 3.
#include "environ.hpp"  // 4.
// 5. echo
// 6. help
// 7. pause
// 8. quit
// 11. ls depends on dir
// 12. pwd
#include "cat.hpp"    // 13.
#include "cp.hpp"     // 17
#include "mkdir.hpp"  // 14.
#include "mv.hpp"     // 18.
#include "rm.hpp"     // 16.
#include "rmdir.hpp"  // 15.
#include "touch.hpp"  // 19.
#include "wc.hpp"     // 21.

bool Shell::Update_Directory() noexcept {
    const unsigned long length = GetCurrentDirectoryA(0, NULL);
    if (length == 0) {
        perror("Failed to get current directory.");
        return false;
    }

    char DIRECTORY[length];
    GetCurrentDirectoryA(length, DIRECTORY);

    this->_directory = DIRECTORY;

    return true;
}

#pragma region 9. chmod

void Shell::Change_Mode(vector<string> files) {
    if (files.size() < 2 || files[0].empty()) {
        fprintf(stderr, "Not enough parameters\n");
        cout << "chmod <permissions> <files>" << endl;
        return;
    }

    const char* perms = files[0].c_str();
    files.erase(files.begin());

    for (const string& file : files)
        if (!SetFileAttributesA(file.c_str(), atoi(perms)))
            perror(("Failed to change permissions of file " + file).c_str());
}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(vector<string> paths) {}
#pragma endregion

#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string& pattern, const string& file) {
    if (file.empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "grep <pattern> <file>" << endl;
        return;
    }

    HANDLE hFile = CreateFileA(file.c_str(),           // File name
                               GENERIC_READ,           // Read access
                               FILE_SHARE_READ,        // Allow other reads
                               NULL,                   // Default security
                               OPEN_EXISTING,          // if exists
                               FILE_ATTRIBUTE_NORMAL,  // Normal file
                               NULL);                  // No template

    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to open '%s'\n", file.c_str());
        return;
    }

    char buffer[BUFFER_SIZE];
    unsigned long bytes = 0;  // readfile doesnt allow size_t??
    string text;

    while (ReadFile(hFile, buffer, sizeof(buffer), &bytes, NULL) && bytes > 0) {
        string text(buffer, bytes);
        if (text.find(pattern) != string::npos)
            cout << file << ":" << endl << text << endl;
    }

    CloseHandle(hFile);
}
#pragma endregion

#pragma region Execution / Starting Process
pid_t Shell::Execute(const string& name) {
    STARTUPINFOA s_info = STARTUPINFOA();
    PROCESS_INFORMATION p_info = PROCESS_INFORMATION();

    if (!CreateProcessA(nullptr, (char*)name.c_str(), nullptr, nullptr, FALSE,
                        0, nullptr, nullptr, &s_info, &p_info))
        return -1;

    pid_t pid = p_info.dwProcessId;
    printf("Started Process '%s' with PID: %lld\n", name.c_str(), pid);

    WaitForSingleObject(p_info.hProcess, INFINITE);

    CloseHandle(p_info.hProcess);
    CloseHandle(p_info.hThread);

    return pid;
}
#pragma endregion
