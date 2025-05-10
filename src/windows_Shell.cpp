/** For Defining Shell Functions that are windows specific */
#include <direct.h>
#include <windows.system.h>
#include <winternl.h>

#include "Models/Shell.cpp"
#include "Windows/cd.hpp"       // 1.
#include "Windows/dir.hpp"      // 3.
#include "Windows/environ.hpp"  // 4.
#include "Windows/wc.hpp"       // 21.

using std::istringstream;

// 2. clear

// 5. echo
// 6. help
// 7. pause
// 8. quit

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
void Shell::Change_Mode(const string& perms) {
    cout << "Windows Displayed file permissions" << perms << endl;
}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(const string& owner, const vector<string>& paths) {
    cout << "Windows Displayed file owner" << owner << endl;
}
#pragma endregion

// 11. ls
// 12. pwd

#pragma region 13. cat
void Shell::Concatenate(const vector<string>& files) {
    cout << "Windows Displayed file" << files[0] << endl;
}
#pragma endregion

#pragma region 14. mkdir

void Shell::Make_Directories(const vector<string>& directories) {
    cout << "Windows Created directory" << directories[0] << endl;
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(const vector<string>& directories) {
    cout << "Windows Removed directory" << directories[0] << endl;
}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove(const vector<string>& files) {
    cout << "Windows Removed file" << files[0] << endl;
}
#pragma endregion

#pragma region 17. Copy Files (cp)
void Shell::Copy(const vector<string>& files, const string& dest) {
    cout << "Windows Copied file" << files[0] << " to " << dest << endl;
}
#pragma endregion

#pragma region 18. Move Files (mv)
void Shell::Move(const vector<string>& files, const string& dest) {
    cout << "Windows Moved file" << endl;
}
#pragma endregion

#pragma region 19. Create (touch)
void Shell::Create_Empty_Files(const vector<string>& files) {
    cout << "Windows Created file" << endl;
}
#pragma endregion

#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string& pattern, const string& file) {
    cout << "Windows Opened file" << endl;
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
