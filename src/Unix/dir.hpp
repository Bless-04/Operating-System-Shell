//3. dir

void Shell::List_Directory(const string &path)
{
    
    DIR *dir = path.empty() ? opendir(".") : opendir(path.c_str());
    if (!dir)
    {
        perror("Failed to open directory");
        return;
    }

    struct dirent *data;
    while ((data = readdir(dir)) != nullptr)
    {
        cout << ((data->d_type == DT_DIR) ? "<DIR>\t" : "\t");

        //cout << data << "\tbytes";
        cout << data->d_name << endl;
        
    }
    cout << endl;
    closedir(dir);
}
