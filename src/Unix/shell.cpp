/** For Defining Shell Functions that are unix specific */
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../Models/Shell.cpp"

#include "cd.hpp"      // 1.
#include "dir.hpp"     // 3.
#include "environ.hpp" // 4.
#include "mkdir.hpp"   // 14.
#include "rmdir.hpp"   // 15.
#include "rm.hpp"      // 16.
#include "wc.hpp"      // 21.

bool Shell::Update_Directory() noexcept
{
    char buffer[this->BUFFER_SIZE];
    if (getcwd(buffer, sizeof(buffer)) == NULL)
        return false;

    this->_directory = buffer;

    return true;
}

// 2. clear
// 5. echo
// 6. help
// 7. pause
// 8. quit

#pragma region 9. chmod
void Shell::Change_Mode(const string &perms) {}
#pragma endregion

#pragma region 10. chown
void Shell::Change_Ownership(const string &owner, const vector<string> &paths)
{
    // todo: chown
    struct passwd *pw = getpwnam(owner.c_str());
    if (!pw)
    {
        perror("Failed to change ownership");
        return;
    }

    for (const string &path : paths)
        if (chown(path.c_str(), pw->pw_uid, pw->pw_gid) != 0)
            perror("chown failed");
}
#pragma endregion

// 11. ls
// 12. pwd

#pragma region 13. cat
void Shell::Concatenate(const vector<string> &files)
{
    if (files[0].empty())
    {
        fprintf(stderr, "No files were given\n");
        return;
    }

    for (const string &file : files)
    {
        int fd = open(file.c_str(), O_RDONLY);
        if (fd == -1)
        {
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








#pragma region 17. Copy Files (cp)
void Shell::Copy(const vector<string> &files, const string &dest) {




}
#pragma endregion

#pragma region 18. Move Files (mv)
void Shell::Move(const vector<string> &files, const string &destination)
{
    if (files.empty())
    {
        fprintf(stderr, "No files were given\n");
        return;
    }

    for (const string &source : files)
    {
        string target;

        // If destination is a directory, append source filename to it
        struct stat st;
        if (stat(destination.c_str(), &st) == 0 && S_ISDIR(st.st_mode))
        {
            size_t last_slash = source.find_last_of("/\\");
            string filename = (last_slash == string::npos)
                                  ? source
                                  : source.substr(last_slash + 1);
            target = destination + "/" + filename;
        }
        else
        {
            target = destination;
        }

        // Trying to rename first
        if (rename(source.c_str(), target.c_str()) == 0)
            continue;

        // If rename fails, do a copy and delete
        int source_fd = open(source.c_str(), O_RDONLY);
        if (source_fd == -1)
        {
            perror(("mv: " + source).c_str());
            continue;
        }

        // Getting file permissions from source
        struct stat source_stat;
        if (fstat(source_fd, &source_stat) == -1)
        {
            perror(("mv: " + source).c_str());
            close(source_fd);
            continue;
        }

        int dest_fd = open(target.c_str(), O_WRONLY | O_CREAT | O_TRUNC,
                           source_stat.st_mode);
        if (dest_fd == -1)
        {
            perror(("mv: " + target).c_str());
            close(source_fd);
            continue;
        }

        char buffer[this->BUFFER_SIZE];
        ssize_t bytes_read;
        bool copy_success = true;

        while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0)
        {
            ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
            if (bytes_written != bytes_read)
            {
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
void Shell::Create_Empty_Files(const vector<string> &files)
{
    for (const string& file : files){
        int f = open(file.c_str(), O_CREAT | O_WRONLY, 0644);
        if (f == -1)
            perror(("touch failed for " + file).c_str());
        else {
            close(f);
        }
    }
}
#pragma endregion

#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string &pattern, const string &file)
{

    /*
    if (pattern.empty() || file.empty())
    {

        fprintf(stderr, "Not enough argument given\n");
        cout << "grep <pattern> <file>";

        return;
    }

    int fd = open(file.c_str(), O_RDONLY);
    if (fd == -1)
    {
        perror(("grep: " + file).c_str());
        return;
    }

    char buffer[this->BUFFER_SIZE];
    size_t bytes = 0;
    string line;
    while (read(fd, buffer, sizeof(buffer)) > 0)
    {
        if (std::regex(buffer, pattern))
    }

    string line;
    int line_number = 1;
    bool match_found = false;

    while (std::getline(input_file, line))
    {
        if (line.find(pattern) != string::npos)
        {
            std::cout << file << ":" << line_number << ": " << line << std::endl;
            match_found = true;
        }
        line_number++;
    }

    input_file.close();

    if (!match_found)
    {
        std::cout <<
    }
        */
}
#pragma endregion

#pragma region Execution / Starting Process

pid_t Shell::Execute(const string &name)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return -1;
    }
    else if (pid == 0)
    {
        // Child process
        execlp(name.c_str(), name.c_str(), (char *)NULL);
        // If execlp returns, it means an error occurred
        fprintf(stderr, "Failed to execute '%s': %s\n", name.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        printf("Started Process '%s' with PID: %lld\n", name.c_str(), (long long)pid);

        int status;
        waitpid(pid, &status, 0);
        return pid;
    }
}
#pragma endregion
