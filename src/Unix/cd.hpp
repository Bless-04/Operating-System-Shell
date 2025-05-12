// 1. cd

void Shell::Change_Directory(const string &path)
{
    if (path.empty())
    {
        cout << this->_directory << endl;
        return;
    }
    if (chdir(path.c_str()) != 0)
        perror("Failed to change directory");

    this->Update_Directory();
}