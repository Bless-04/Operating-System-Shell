
/* 3. dir*/

void Shell::List_Directory(const string& PATH) {
    _WIN32_FIND_DATAA data;
    HANDLE hFind;

    string path = (PATH.empty() ? this->_directory : PATH);
    path.append("\\*");

    hFind = FindFirstFileA(path.c_str(), &data);

    const char* TAB2 = "\t\t";
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, ("Failed to read data in directory: %s\n"),
                path.c_str());
        return;
    }

    do {
        const unsigned long& flags = data.dwFileAttributes;

        cout << ((flags & FILE_ATTRIBUTE_DIRECTORY) ? "<DIR>\t" : "\t");

        cout << data.nFileSizeLow << "\tbytes";
        cout << TAB2 << data.cFileName << endl;
    } while (FindNextFileA(hFind, &data) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES)
        perror("Failed to get the next file");

    FindClose(hFind);
}
