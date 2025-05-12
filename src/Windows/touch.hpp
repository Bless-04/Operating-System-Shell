// 19. Create (touch)

void Shell::Create_Empty_Files(const vector<string>& files) {
    if (files.size() == 0 || files[0].empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "touch <files>" << endl;
        return;
    }

    for (const string& file : files)
        if (!CreateFileA(file.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL,
                         CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL))
            perror(("Failed to create " + file).c_str());
}
