/* 21. dir*/

void Shell::Word_Count(const string& file) {
    HANDLE hFile = CreateFileA(file.c_str(),           // File name
                               GENERIC_READ,           // Read access
                               FILE_SHARE_READ,        // Allow other reads
                               NULL,                   // Default security
                               OPEN_EXISTING,          // Open only if it exists
                               FILE_ATTRIBUTE_NORMAL,  // Normal file
                               NULL);                  // No template

    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to open '%s'\n", file.c_str());
        return;
    }

    char buffer[1024];
    unsigned long bytes = 0;
    string text;
    size_t lines = 1, words = 0, chars = 0;

    while (ReadFile(hFile, buffer, sizeof(buffer), &bytes, NULL) && bytes > 0) {
        text.append(buffer, bytes);
    }

    CloseHandle(hFile);

    // number of characters is how ever long the text is
    chars = text.length();

    for (char c : text)
        if (c == '\n') lines++;

    istringstream ss(text);
    string word;
    while (ss >> word) words++;

    cout << "Characters: " << chars << endl;
    cout << "Words: " << words << endl;
    cout << "Lines: " << lines << endl;
}