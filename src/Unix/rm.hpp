// 16. Remove Files (rm)

void Shell::Remove(const vector<string> &files)
{
    if (files[0].empty())
    {
        fprintf(stderr, "No files were given\n");
        return;
    }

    for (const string &file : files)
        if (remove(file.c_str()) != 0) //unlink also works
           fprintf(stderr, "Failed to remove file '%s' : %s\n", file.c_str(), strerror(errno));    
}
