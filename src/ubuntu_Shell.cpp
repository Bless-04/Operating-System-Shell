/** For Defining Shell Functions that are unix/ubuntu specific */
#include <fcntl.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Models/Shell.cpp"

bool Shell::Update_Directory() noexcept {
    char buffer[1024];
    if (getcwd(buffer, sizeof(buffer)) == NULL) return false;

    this->_directory = buffer;

    return true
}

#pragma region 1. cd
void Shell::Change_Directory(const string& path) {
    if (chdir(path.c_str()) != 0) perror("Failed to change directory");
}
#pragma endregion

// 2. clear

#pragma region 3. dir

#pragma endregion

#pragma region 4. env
void Shell::Environment_Variables() {
    extern char** environ;
    for (int i = 0; environ[i]; ++i) {
        cout << environ[i] << endl;
    }
}
#pragma endregion

#pragma region 9. chmod
void Shell::File_Permissions(const string& perms) {}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(const string& owner) {
    struct passwd* pw = getpwnam(args[1].c_str());
    if (!pw) {
        perror("Failed to change ownership");
        return;
    }
    for (size_t i = 2; i < args.size(); ++i) {
        if (chown(args[i].c_str(), pw->pw_uid, pw->pw_gid) != 0) {
            perror("chown failed");
        }
    }
}
#pragma endregion

#pragma region 11. ls
void Shell::List_Files() {}
#pragma endregion

#pragma region 12. pwd
void Shell::Print_Working_Directory() {
    cout << this->Current_Directory() << endl;
}
#pragma endregion

#pragma region 13. cat
void Shell::Concatenate_and_Display_Files(const vector<string>& files) {}
#pragma endregion

#pragma region 14. mkdir

void Shell::Create_Directories(const vector<string>& directories) {
    cout << "Windows Created directory" << directories[0] << endl;
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(const vector<string>& directories) {}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove_Files(const vector<string>& files) {}
#pragma endregion

#pragma region 17. Copy Files (cp)
void Shell::Copy_Files(const vector<string>& files, const string& dest) {}
#pragma endregion

#pragma region 18. Move Files (mv)
void Shell::Move_Files(const vector<string>& files) {}
#pragma endregion

#pragma region 19. Create (touch)
void Shell::Create_Empty_Files(const string& file) {}
#pragma endregion

#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string& pattern, const string& file) {}
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
    /** chapter 3 */

    /** Fork A child process */
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {  // child process
        execlp("/bin/ls", "ls", NULL);
    } else { /** parent process */
        wait(NULL);
        cout << "Child Process Complete" << endl;
    }

    return 0;
}
#pragma endregion
