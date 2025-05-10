// 1. cd

void Shell::Change_Directory(const string& path) {
    if (path.empty()) {
        cout << this->_directory << endl;
        return;
    }

    if (!SetCurrentDirectoryA(path.c_str()))
        perror("Failed to change directory.");

    this->Update_Directory();
}
