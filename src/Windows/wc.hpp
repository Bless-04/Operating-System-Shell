/* 21. wc*/

void Shell::Word_Count(const string& file) {
    size_t lines = 1, words = 0;

    if (file.empty()) {
        fprintf(stderr, "No files were given\n");
        cout << "wc <files>" << endl;
        return;
    }
    HANDLE hFile = CreateFileA(file.c_str(),           // File name
                               GENERIC_READ,           // Read access
                               FILE_SHARE_READ,        // Allow other reads
                               NULL,                   // Default security
                               OPEN_EXISTING,          // if exists
                               FILE_ATTRIBUTE_NORMAL,  // Normal file
                               NULL);                  // No template

    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to open '%s'\n", file.c_str());
        return;
    }

    char buffer[BUFFER_SIZE];
    unsigned long bytes = 0;  // readfile doesnt allow size_t??
    string text;

    while (ReadFile(hFile, buffer, sizeof(buffer), &bytes, NULL) && bytes > 0)
        text.append(buffer, bytes);

    CloseHandle(hFile);

    for (const char& c : text)
        if (c == '\n') lines++;

    istringstream ss(text);  // input only stream
    string word;
    while (ss >> word) words++;

    cout << file << endl;
    cout << "Characters: " << text.length() << endl;
    cout << "Words: " << words << endl;
    cout << "Lines: " << lines << endl;
}