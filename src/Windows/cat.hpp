// 13. cat

void Shell::Concatenate(const vector<string>& files) {
    if (files.size() == 0 || files[0].empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "cat <files>" << endl;
        return;
    }

    for (const string& file : files) {
        HANDLE hFile = CreateFileA(file.c_str(),           // File name
                                   GENERIC_READ,           // Read access
                                   FILE_SHARE_READ,        // Allow other reads
                                   NULL,                   // Default security
                                   OPEN_EXISTING,          // if exists
                                   FILE_ATTRIBUTE_NORMAL,  // Normal file
                                   NULL);                  // No template

        if (hFile == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Failed to open '%s'\n", file.c_str());
            continue;
        }

        char buffer[BUFFER_SIZE];
        unsigned long bytes = 0;

        while (ReadFile(hFile, buffer, sizeof(buffer), &bytes, NULL) &&
               bytes > 0)
            cout << buffer << endl;

        CloseHandle(hFile);
    }
}
