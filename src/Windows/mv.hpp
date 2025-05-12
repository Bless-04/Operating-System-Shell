// 18. Move Files (mv)

void Shell::Move(vector<string> files) {
    if (files.size() < 2 || files[0].empty()) {
        fprintf(stderr, "Not enough argument given\n");
        cout << "mv <source> <destination>" << endl;
        return;
    }

    const string dest = files.back();
    files.pop_back();

    for (const string& file : files)
        if (!MoveFileA(file.c_str(), (dest + "/" + file).c_str()))
            perror(("Failed to move " + file).c_str());
}
