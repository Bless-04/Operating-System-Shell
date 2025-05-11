/** For Defining Shell Functions that are unix/ubu5ntu specific */
#include <dirent.h>
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

string Shell::Read_File(const string& file) {
    int fd = open(file.c_str(), O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open '%s'\n", file.c_str());
        return string();
    }

    char buffer[this->BUFFER_SIZE];
    size_t bytes;
    string text;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
        text.append(buffer, bytes);

    close(fd);

    return text;
}
#pragma region 1. cd
void Shell::Change_Directory(const string& path) {
    if (chdir(path.c_str()) != 0) perror("Failed to change directory");

    this->Update_Directory();
}
#pragma endregion

// 2. clear

#pragma region 3. dir
void Shell::List_Directory(const string& path) {
    DIR* dir = path.empty() ? opendir(".") : opendir(path.c_str());
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << "\t";
    }
    cout << endl;
    closedir(dir);
}

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
void Shell::Concatenate(const vector<string>& files) {
    if (files.empty()) {
        fprintf(stderr, "No files were given\n");
        return;
    }

    for (const string& file : files) {
        int fd = open(file.c_str(), O_RDONLY);
        if (fd == -1) {
            perror(("cat: " + file).c_str());
            continue;
        }

        char buffer[this->BUFFER_SIZE];
        size_t bytesRead;
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
            write(STDOUT_FILENO, buffer, bytesRead);

        close(fd);
    }
}
#pragma endregion

#pragma region 14. mkdir

void Shell::Make_Directories(const vector<string>& directories) {
    if (directories.empty()) {
        fprintf(stderr, "No directories were given\n");
        return;
    }

    for (const string& dir : directories) {
        if (mkdir(dir.c_str(), 0755) == -1) perror(("mkdir: " + dir).c_str());
    }
}
#pragma endregion

#pragma region 15. rmdir
void Shell::Remove_Directories(const vector<string>& directories) {
    if (directories.empty()) {
        fprintf(stderr, "No directories were given\n");
        return;
    }

    for (const string& dir : directories)
        if (rmdir(dir.c_str()) == -1) perror(("rmdir: " + dir).c_str());
}

#pragma endregion

#pragma region 16. Remove Files (rm)
void Shell::Remove(const vector<string>& files) {
    if (files.empty()) {
        fprintf(stderr, "No files were given\n");
        return;
    }

    for (const string& file : files)
        if (unlink(file.c_str()) == -1) perror(("rm: " + file).c_str());
}
#pragma endregion

#pragma region 17. Copy Files (cp)
void Shell::Copy(const vector<string>& files, const string& dest) {}
#pragma endregion

#pragma region 18. Move Files (mv)
void Shell::Move(const vector<string>& files, const string& destination) {
    if (files.empty()) {
        fprintf(stderr, "No files were given\n");
        return;
    }

    for (const string& source : files) {
        string target;

        // If destination is a directory, append source filename to it
        struct stat st;
        if (stat(destination.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            size_t last_slash = source.find_last_of("/\\");
            string filename = (last_slash == string::npos)
                                  ? source
                                  : source.substr(last_slash + 1);
            target = destination + "/" + filename;
        } else {
            target = destination;
        }

        // Trying to rename first
        if (rename(source.c_str(), target.c_str()) == 0) continue;

        // If rename fails, do a copy and delete
        int source_fd = open(source.c_str(), O_RDONLY);
        if (source_fd == -1) {
            perror(("mv: " + source).c_str());
            continue;
        }

        // Getting file permissions from source
        struct stat source_stat;
        if (fstat(source_fd, &source_stat) == -1) {
            perror(("mv: " + source).c_str());
            close(source_fd);
            continue;
        }

        int dest_fd = open(target.c_str(), O_WRONLY | O_CREAT | O_TRUNC,
                           source_stat.st_mode);
        if (dest_fd == -1) {
            perror(("mv: " + target).c_str());
            close(source_fd);
            continue;
        }

        char buffer[this->BUFFER_SIZE];
        ssize_t bytes_read;
        bool copy_success = true;

        while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
            ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror(("mv: " + target).c_str());
                copy_success = false;
                break;
            }
        }

        close(source_fd);
        close(dest_fd);

        // If copy was successful, remove the source file
        if (copy_success && unlink(source.c_str()) == -1)
            perror(("mv: failed to remove " + source).c_str());
    }
}
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
void Shell::Search_Text_Patterns(const string& pattern, const string& file) {
    if (pattern.empty() || file.empty()) {
        std::cerr << "grep: missing pattern or file" << std::endl;
        return;
    }

    // Simple implementation that reads the file line by line
    // and checks if the pattern exists in each line
    std::ifstream input_file(file);
    if (!input_file.is_open()) {
        perror(("grep: " + file).c_str());
        return;
    }

    string line;
    int line_number = 1;
    bool match_found = false;

    while (std::getline(input_file, line)) {
        if (line.find(pattern) != string::npos) {
            std::cout << file << ":" << line_number << ": " << line
                      << std::endl;
            match_found = true;
        }
        line_number++;
    }

    input_file.close();

    if (!match_found) {
        std::cout << "No matches found for pattern: " << pattern << std::endl;
    }
}
#pragma endregion

#pragma region 21. word count (wc)
void Shell::Word_Count(const string& file) {
    size_t lines = 0, words = 0, chars = 0;

    string text = Read_File(file);
    if (text.empty()) return;
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
pid_t Shell::Execute(const string& name) {
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
    } else { /* parent process*/
        int status;
        waitpid(pid, &status, 0);
        return pid;
    }

    return pid;
}
#pragma endregion
