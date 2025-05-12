// 16. Remove Files (rm)

void Shell::Remove(const vector<string>& files) {
    if (files.size() == 0 || files[0].empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "rm <files>" << endl;
        return;
    }

    for (const string& file : files)
        if (!DeleteFileA(file.c_str()))
            if (!RemoveDirectoryA(file.c_str()))
                fprintf(stderr, "Failed to Remove '%s'\n", file.c_str());
}