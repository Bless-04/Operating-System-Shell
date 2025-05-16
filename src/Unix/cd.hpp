// 1. cd

void Shell::Change_Directory(const string &path)
{
    if (path.empty())
    {
        cout << this->_directory << endl;
        return;
    }
    if (syscall(SYS_chdir, path.c_str()) != 0)
        perror(("Failed to change directory to " + path).c_str());

    this->Update_Directory();
}