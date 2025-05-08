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

    return true;
}

#pragma region 1. cd
void Shell::Change_Directory(const string& path) {
    if (chdir(path.c_str()) != 0) perror("Failed to change directory");
}
#pragma endregion

// 2. clear

#pragma region 3. dir
void Shell::List_Directory(const string&) {}

#pragma endregion

#pragma region 4. env
void Shell::Environment_Variables() {
    extern char** environ;
    for (int i = 0; environ[i]; ++i) {
        cout << environ[i] << endl;
    }
}
#pragma endregion

// 5. echo
// 6. help
// 7. pause
// 8. quit

#pragma region 9. chmod
void Shell::Change_Mode(const string& perms) {}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(const string& owner, const vector<string>& paths) {
    // todo: chown
    struct passwd* pw = getpwnam(owner.c_str());
    if (!pw) {
        perror("Failed to change ownership");
        return;
    }

    for (const string& path : paths)
        if (chown(path.c_str(), pw->pw_uid, pw->pw_gid) != 0)
            perror("chown failed");
}
#pragma endregion

// 11. ls
// 12. pwd

#pragma region 13. cat
void Shell::Concatenate(const vector<string>& files) {}
#pragma endregion

#pragma region 14. mkdir

void Shell::Make_Directories(const vector<string>& directories) {
    cout << "Windows Created directory" << directories[0] << endl;
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(const vector<string>& directories) {}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove(const vector<string>& files) {}
#pragma endregion

#pragma region 17. Copy Files (cp)
void Shell::Copy(const vector<string>& files, const string& dest) {}
#pragma endregion

#pragma region 18. Move Files (mv)
void Shell::Move(const vector<string>& files) {}
#pragma endregion

#pragma region 19. Create (touch)
void Shell::Create_Empty_Files(const vector<string>& files) {
    for (size_t i = 1; i < files.size(); ++i) {
        int fd = open(files[i].c_str(), O_CREAT | O_WRONLY, 0644);
        if (fd == -1)
            perror("touch failed");
        else
            close(fd);
    }
}
#pragma endregion

#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string& pattern, const string& file) {}
#pragma endregion

#pragma region 21. word count (wc)
void Shell::Word_Count(const string& file) {
    size_t lines = 0, words = 0, chars = 0;

    int fd = open(file.c_str(), O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
        for (const char& c : buffer) {
            if (c == '\n') ++lines;
            if (c == ' ') ++words;
            ++chars;
        }
    }
    close(fd);

    cout << file << endl;
    cout << "lines: " << lines << endl;
    cout << "words: " << words << endl;
    cout << "chararacters: " << chars << endl;
}
#pragma endregion

#pragma region Execution / Starting Process
pid_t Shell::Execute(string name) {
    /** chapter 3 */

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return -1;
    } else if (pid == 0) {
        // Child process
        execlp(name.c_str(), name.c_str(), NULL);

        fprintf(stderr, "Failed to execute %s\n", name.c_str());
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        cout << "Child process complete" << endl;
        return pid;
    }
}
#pragma endregion
