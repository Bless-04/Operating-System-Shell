// 15. rmdir

void Shell::Remove_Directories(const vector<string>& directories) {
    if (directories.size() == 0 || directories[0].empty()) {
        fprintf(stderr, "No directories were given\n");
        cout << "rmdir <directories>" << endl;
        return;
    }

    for (const string& dir : directories)
        if (!RemoveDirectoryA(dir.c_str()))
            perror(("Failed to remove directory " + dir).c_str());
}
