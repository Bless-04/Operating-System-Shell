// 14. mkdir


void Shell::Make_Directories(const vector<string> &directories)
{
    if (directories.size() == 0 || directories[0].empty())
    {
        fprintf(stderr, "No directories were given\n");
        return;
    }

    for (const string &dir : directories)
    {
        if (syscall(SYS_mkdir, dir.c_str(), 0755) != 0)
        {
            perror(("Failed to create directory " + dir).c_str());
        }
    }

           
}