/** For Defining Shell Functions that are windows specific */
#include <direct.h>
#include <ntdef.h>
#include <ntstatus.h>
#include <windows.system.h>
#include <winternl.h>

#include "Models/Shell.cpp"  //shell.cpp later

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

#pragma region 1. cd
void Shell::Change_Directory(const string& path) {
    if (path.empty()) {
        cout << this->_directory << endl;
        return;
    }

    if (!SetCurrentDirectoryA(path.c_str()))
        perror("Failed to change directory.");

    this->Update_Directory();
}
#pragma endregion

// 2. clear

#pragma region 3. dir

#pragma endregion

#pragma region 4. env
void Shell::Environment_Variables() {
    wchar_t* envs = (wchar_t*)GetEnvironmentStringsW();
    if (envs == NULL) {
        perror("Failed to Get Environment Strings.");
        return;
    }

    for (wchar_t* e = envs; *e; e += wcslen(e) + 1) std::wcout << e << endl;

    FreeEnvironmentStringsW(envs);
}
#pragma endregion

// 5. echo
// 6. help
// 7. pause
// 8. quit

#pragma region 9. chmod
void Shell::File_Permissions(const string& perms) {
    cout << "Windows Displayed file permissions" << perms << endl;
}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(const string& owner, const vector<string>& paths) {
    cout << "Windows Displayed file owner" << owner << endl;
}
#pragma endregion

#pragma region 11. ls
void Shell::List_Files() {
    _WIN32_FIND_DATAA data;
    HANDLE hFind;

    string path = this->_directory;

    path.append("\\*");

    hFind = FindFirstFileA(path.c_str(), &data);

    /// @note its char* instead of string so it works with both cout and wcout
    const char* TAB2 = "\t\t";
    if (hFind == INVALID_HANDLE_VALUE) {
        perror("Could Not find files");
        return;
    }

    do {
        const unsigned long& flags = data.dwFileAttributes;

        cout << ((flags & FILE_ATTRIBUTE_DIRECTORY) ? "<DIR>\t" : "\t");

        cout << data.nFileSizeLow << "\tbytes";
        cout << TAB2 << data.cFileName << endl;
    } while (FindNextFileA(hFind, &data) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES)
        perror("Failed to get the next file");

    FindClose(hFind);
}
#pragma endregion

// 12. pwd

#pragma region 13. cat
void Shell::Concatenate_and_Display_Files(const vector<string>& files) {
    cout << "Windows Displayed file" << files[0] << endl;
}
#pragma endregion

#pragma region 14. mkdir

void Shell::Create_Directories(const vector<string>& directories) {
    cout << "Windows Created directory" << directories[0] << endl;
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(const vector<string>& directories) {
    cout << "Windows Removed directory" << directories[0] << endl;
}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove_Files(const vector<string>& files) {
    cout << "Windows Removed file" << files[0] << endl;
}
#pragma endregion

#pragma region 17. Copy Files (cp)
void Shell::Copy_Files(const vector<string>& files, const string& dest) {
    cout << "Windows Copied file" << files[0] << " to " << dest << endl;
}
#pragma endregion

#pragma region 18. Move Files (mv)
void Shell::Move_Files(const vector<string>& files) {
    cout << "Windows Moved file" << endl;
}
#pragma endregion

#pragma region 19. Create (touch)
void Shell::Create_Empty_Files(const string& file) {
    cout << "Windows Created file" << endl;
}
#pragma endregion

#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string& pattern, const string& file) {
    cout << "Windows Opened file" << endl;
}
#pragma endregion

#pragma region 21. word count (wc)
void Shell::Word_Count(const string& file) {
    size_t lines = 0, words = 0, chars = 0;

    cout << file << endl;
    cout << "lines: " << lines << endl;
    cout << "words: " << words << endl;
    cout << "chararacters: " << chars << endl;
}
#pragma endregion

#pragma region Execution / Starting Process
pid_t Shell::Execute(string name) {
    STARTUPINFOA s_info = STARTUPINFOA();
    PROCESS_INFORMATION p_info = PROCESS_INFORMATION();

    if (!CreateProcessA(nullptr, (char*)name.c_str(), nullptr, nullptr, FALSE,
                        0, nullptr, nullptr, &s_info, &p_info))
        return -1;

    WaitForSingleObject(p_info.hProcess, INFINITE);

    CloseHandle(p_info.hProcess);
    CloseHandle(p_info.hThread);

    return p_info.dwProcessId;
}
#pragma endregion
