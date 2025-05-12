// 14. mkdir

void Shell::Make_Directories(const vector<string> &directories)
{
    if (directories[0].empty())
    {
        fprintf(stderr, "No directories were given\n");
        return;
    }

    for (const string &dir : directories)
        if (mkdir(dir.c_str(), 0755) != 0)
            fprintf(stderr, "Failed to create directory '%s' : %s\n", dir.c_str(), strerror(errno));
}