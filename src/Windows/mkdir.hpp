// 14. mkdir

void Shell::Make_Directories(const vector<string>& directories) {
    if (directories.size() == 0 || directories[0].empty()) {
        fprintf(stderr, "No directories were given\n");
        cout << "mkdir <directories>" << endl;
        return;
    }

    for (const string& dir : directories)
        if (!CreateDirectoryA(dir.c_str(), NULL))
            fprintf(stderr, "Failed to create directory '%s'\n", dir.c_str());
}
