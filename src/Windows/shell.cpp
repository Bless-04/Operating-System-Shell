/** For Defining Shell Functions that are windows specific */
#include "../Models/Shell.cpp"

#include <windows.system.h>
#include <winternl.h>

#include "cd.hpp"       // 1.
#include "dir.hpp"      // 3.
#include "environ.hpp"  // 4.
#include "wc.hpp"       // 21.

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

// 11. ls depends on dir
// 12. pwd

#pragma region 13. cat
void Shell::Concatenate(const vector<string>& files) {}
#pragma endregion

#pragma region 14. mkdir

void Shell::Make_Directories(const vector<string>& directories) {
    if (directories[0].empty()) {
        fprintf(stderr, "No directories were given\n");
        cout << "mkdir <directories>" << endl;
        return;
    }

    for (const string& dir : directories)
        if (!CreateDirectoryA(dir.c_str(), NULL))
            fprintf(stderr, "Failed to create directory '%s'\n", dir.c_str());
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(const vector<string>& directories) {
    if (directories[0].empty()) {
        fprintf(stderr, "No directories were given\n");
        cout << "rmdir <directories>" << endl;
        return;
    }

    for (const string& dir : directories)
        if (!RemoveDirectoryA(dir.c_str()))
            fprintf(stderr, "Failed to Remove Directory'%s", dir.c_str());
}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove(const vector<string>& files) {
    if (files[0].empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "rm <files>" << endl;
        return;
    }

    for (const string& file : files)
        if (!DeleteFileA(file.c_str()) && !RemoveDirectoryA(file.c_str()))
            fprintf(stderr, "Failed to Remove '%s'\n", file.c_str());
}
#pragma endregion

#pragma region 17. Copy Files (cp)
void Shell::Copy(const vector<string>& files, const string& dest = string()) {
    if (files[0].empty() || dest.empty()) {
        fprintf(stderr, "Not enough argument given\n");
        cout << "cp <files> <destination>" << endl;
        cout << "cp <file> <copied_file>" << endl;
        return;
    }

    for (const string& file : files)
        if (!CopyFileA(file.c_str(), dest.c_str(), false))
            fprintf(stderr, "Failed to copy '%s' into '%s'\n", file.c_str(),
                    dest.c_str());
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
    if (file.empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "grep <pattern> <file>" << endl;
        return;
    }

    std::ifstream ifs(file);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << file << std::endl;
        return;
    }

    std::string buffer;
    buffer.resize(1024);  // buffer size
    std::regex re(pattern);
    int line = 0;

    while (ifs.read(&buffer[0], buffer.size())) {
        std::string text(buffer, 0, ifs.gcount());
        auto words_begin = std::sregex_iterator(text.begin(), text.end(), re);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::cout << file << ":" << line << ": " << match.str(0)
                      << std::endl;
        }
        line++;
    }

    ifs.close();
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
