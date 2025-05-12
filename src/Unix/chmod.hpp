//9. chmod

void Shell::Change_Mode(vector<string> files)
{
    //0664

    if (files.size() == 0 ||  files[0].empty()){
        fprintf(stderr, "No files were given\n");
        cout << "chmod <permissions> <files>" << endl;
        return;
    }

    const string permissions = files[0];
    files.erase(files.begin());

    try {
        mode_t mode = strtol(permissions.c_str(), nullptr, 8);

        for (const string& file : files)
        if (chmod(file.c_str(), mode) == -1) 
            perror(("Failed to change permissions of file " + file).c_str());
    }catch(const std::invalid_argument &e){
        fprintf(stderr,"%s' are not valid permisions\n",permissions.c_str());
        return;
    }
   
        
}
