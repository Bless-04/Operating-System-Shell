/** For Defining Shell Functions that are windows specific */
#include "../Models/Shell.cpp"

#include <windows.system.h>
#include <winternl.h>

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
#include "rm.hpp"     // 16.
#include "rmdir.hpp"  // 15.
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

#pragma region 18. Move Files (mv)
void Shell::Move(vector<string> files) { cout << "Windows Moved file" << endl; }
#pragma endregion

#pragma region 19. Create (touch)
void Shell::Create_Empty_Files(const vector<string>& files) {
    if (files.size() == 0 || files[0].empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "touch <files>" << endl;
        return;
    }

    for (const string& file : files)
        if (!CreateFileA(file.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
                         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL))
            perror(("Failed to create " + file).c_str());
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
    buffer.resize(this->BUFFER_SIZE);  // buffer size
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
