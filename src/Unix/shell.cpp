/** For Defining Shell Functions that are unix specific */
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "../Models/Shell.cpp"

#include "cd.hpp"      // 1.
// 2. clear
#include "dir.hpp"     // 3.
#include "environ.hpp" // 4.
// 5. echo
// 6. help
// 7. pause
// 8. quit
#include "chmod.hpp"   // 9.
#include "chown.hpp"   // 10.
// 11. ls
// 12. pwd
#include "cat.hpp"     // 13.
#include "mkdir.hpp"   // 14.
#include "rmdir.hpp"   // 15.
#include "rm.hpp"      // 16.
#include "cp.hpp"      // 17.
#include "mv.hpp"
#include "touch.hpp"   // 19.
#include "wc.hpp"      // 21.

bool Shell::Update_Directory() noexcept
{
    char buffer[this->BUFFER_SIZE];
    if (getcwd(buffer, sizeof(buffer)) == NULL)
        return false;

    this->_directory = buffer;

    return true;
}





#pragma region 20. search text patterns (grep)
void Shell::Search_Text_Patterns(const string &pattern, const string &file)
{
    if (file.empty())
    {
        fprintf(stderr, "No files were given\n");
        cout << "grep <pattern> <file>" << endl;
        return;
    }

    int fd = open(file.c_str(), O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Failed to open '%s'\n", file.c_str());
        cout << "grep <pattern> <file>" << endl;
        return;
    }

    char buffer[this->BUFFER_SIZE];
    size_t bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
    {
        string text(buffer, bytes);
        if (text.find(pattern) != string::npos)
            cout << file << ":" << endl << text << endl;
    }
    close(fd);
    
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
        fprintf(stderr, "Failed to execute '%s'\n", name.c_str());
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
