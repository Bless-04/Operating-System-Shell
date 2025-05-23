// 16. Remove Files (rm)

void Shell::Remove(const vector<string>& files)
{
    if (files.size() == 0 ||  files[0].empty())
    {
        fprintf(stderr, "No files were given\n");
        cout << "rm <files>" << endl;
        return;
    }

    for (const string &file : files)
        if (syscall(SYS_unlink, file.c_str()) != 0)
            perror(("Failed to Remove " + file).c_str());
}
