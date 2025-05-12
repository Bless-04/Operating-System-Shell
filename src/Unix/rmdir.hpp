// 15. rmdir

void Shell::Remove_Directories(const vector<string> &directories)
{
    if (directories[0].empty())
    {
        fprintf(stderr, "No directories were given\n");
        return;
    }

    for (const string &dir : directories)
        if (rmdir(dir.c_str()) != 0) fprintf(stderr, "Failed to remove directory '%s' : %s\n", dir.c_str(), strerror(errno));
}