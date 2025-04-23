/** For Defining Shell Functions that are windows specific */
#include <ntdef.h>
#include <ntstatus.h>
#include <windows.h>
#include <winternl.h>

#include "Models/Shell.cpp"  //shell.cpp later

#ifndef pid_t
#define pid_t long long  // for process id
#endif

#pragma region 1. cd
void Shell::Change_Directory(string path) {
    cout << "Windows Changed directory to " << path << endl;
}
#pragma endregion

#pragma region 2. clr
void Shell::Clear_Screen() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    cout << "\033[2J\033[H";
}
#pragma endregion

#pragma region 3. dir

#pragma endregion

#pragma region 4. env
void Shell::Environment_Variables() {
    char* envs = (char*)GetEnvironmentStrings();
    if (envs == NULL) {
        cerr << "Failed to Get Environment Strings." << endl;
        return;
    }

    for (char* e = envs; *e; e += strlen(e) + 1) cout << e << endl;

    FreeEnvironmentStringsA(envs);
}

#pragma endregion

#pragma region 9. chmod
void Shell::File_Permissions(string perms) {
    cout << "Windows Displayed file permissions" << perms << endl;
}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(string owner) {
    cout << "Windows Displayed file owner" << owner << endl;
}
#pragma endregion

#pragma region 11. ls
void Shell::List_Files(string path) {
    /*
    cout << "Windows Listed directory" << path << endl;

    HANDLE hDir =
        CreateFileA(path.c_str(), FILE_LIST_DIRECTORY,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    if (hDir == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open directory." << std::endl;
        return;
    }

    typedef struct _FILE_DIRECTORY_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        WCHAR FileName[1];
    } FILE_DIRECTORY_INFORMATION;

    typedef NTSTATUS(NTAPI * NtQueryDirectoryFile_t)(
        HANDLE, HANDLE, PVOID, PVOID, PIO_STATUS_BLOCK, PVOID, ULONG,
        FILE_INFORMATION_CLASS, BOOLEAN, PUNICODE_STRING, BOOLEAN);

    NtQueryDirectoryFile_t NtQueryDirectoryFile =
        (NtQueryDirectoryFile_t)GetProcAddress(GetModuleHandleA("ntdll.dll"),
                                               "NtQueryDirectoryFile");

    if (!NtQueryDirectoryFile) {
        std::cerr << "Failed to get NtQueryDirectoryFile function."
                  << std::endl;
        CloseHandle(hDir);
        return;
    }

    BYTE buffer[1024];
    IO_STATUS_BLOCK ioStatus;
    NTSTATUS status;
    bool restartScan = true;

    do {
        status = NtQueryDirectoryFile(hDir, NULL, NULL, NULL, &ioStatus, buffer,
                                      sizeof(buffer), FileDirectoryInformation,
                                      FALSE, NULL, restartScan);

        if (status == STATUS_NO_MORE_FILES) {
            break;
        }

        if (!NT_SUCCESS(status)) {
            std::cerr << "NtQueryDirectoryFile failed." << std::endl;
            break;
        }

        FILE_DIRECTORY_INFORMATION* info = (FILE_DIRECTORY_INFORMATION*)buffer;
        do {
            std::wstring fileName(info->FileName,
                                  info->FileNameLength / sizeof(WCHAR));
            std::wcout << fileName << std::endl;

            if (info->NextEntryOffset == 0) {
                break;
            }
            info = (FILE_DIRECTORY_INFORMATION*)((BYTE*)info +
                                                 info->NextEntryOffset);
        } while (true);

        restartScan = false;

    } while (true);

    CloseHandle(hDir);
    */
}
#pragma endregion

#pragma region 12. pwd
void Shell::Print_Working_Directory() {
    cout << "Windows Displayed working directory" << environ << endl;
}
#pragma endregion

#pragma region 13. cat
void Shell::Concatenate_and_Display_Files(string file) {
    cout << "Windows Displayed file" << file << endl;
}
#pragma endregion

#pragma region 14. mkdir
void Shell::Create_Directories(string directory) {
    cout << "Windows Created directory" << directory << endl;
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(string directory) {
    cout << "Windows Removed directory" << directory << endl;
}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove_Files(vector<string> files) {
    cout << "Windows Removed file" << files[0] << endl;
}
#pragma endregion

#pragma region Execution / Starting Process
pid_t Shell::Execute(string name) {
    // todo: this probably isnt a syscall; change later
    // syscall is probably nt related

    STARTUPINFOA s_info = STARTUPINFOA();
    PROCESS_INFORMATION p_info = PROCESS_INFORMATION();

    if (!CreateProcessA(nullptr, (char*)name.c_str(), nullptr, nullptr, FALSE,
                        0, nullptr, nullptr, &s_info, &p_info)) {
        return -1;
    }

    WaitForSingleObject(p_info.hProcess, INFINITE);

    CloseHandle(p_info.hProcess);
    CloseHandle(p_info.hThread);

    return p_info.dwProcessId;
}
#pragma endregion
