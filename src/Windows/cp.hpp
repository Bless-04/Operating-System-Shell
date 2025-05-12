
// 17. Copy Files (cp)

void Shell::Copy(vector<string> files) {
    if (files.size() == 0 || files[0].empty()) {
        fprintf(stderr, "Not enough argument given\n");
        cout << "cp <files> <destination>" << endl;
        cout << "cp <file> <copied_file>" << endl;
        return;
    }

    const char* dest = files.back().c_str();
    files.pop_back();

    for (const string& file : files)
        if (!CopyFileA(file.c_str(), dest, false))
            fprintf(stderr, "Failed to copy '%s' into '%s'\n", file.c_str(),
                    dest);
}
