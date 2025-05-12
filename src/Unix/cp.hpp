// 17. Copy Files (cp)

void Shell::Copy(vector<string> files)
{
    const string destination = files.back();

    files.pop_back();
    //if copying single file to another single file
    if (files.size() <= 1){
        if (destination.empty()){
            fprintf(stderr, "Not enough argument given\n");
            cout << "cp <files> <destination>" << endl;
            cout << "cp <file> <copied_file>" << endl;
            return;
        }

        int src_fd = open(files[0].c_str(), O_RDONLY);
        if (src_fd == -1) {
            perror(("Failed to open source file " + files[0]).c_str());
            return;
        }


        int create_fd = open(destination.c_str(), O_WRONLY | O_CREAT, 0644); //6 = read + write;
        if (create_fd == -1) {
            perror(("Failed to create destination file " + destination).c_str());
            close(src_fd);
            return;
        }

        char buffer[this->BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = read(src_fd, buffer, this->BUFFER_SIZE)) > 0) {
            if (write(create_fd, buffer, bytes_read) != bytes_read) {
                perror(("Failed to write to destination file " + destination).c_str());
                break;
            }
        }

        close(src_fd);
        close(create_fd);
        return;
        
    }

    
    DIR* dir = opendir(destination.c_str());
    if (!dir){
        perror(("Failed to open directory " + destination).c_str());
        return;
    }

    //copying to directory
    for (const string& file : files){
        int src_fd = open(file.c_str(), O_RDONLY);
        if (src_fd == -1) {
            perror(("Failed to open source file " + file).c_str());
            closedir(dir);
            return;
        }

        struct dirent* data;
        while ((data = readdir(dir)) != nullptr){
            int dst_fd = open((destination + "/" + data->d_name).c_str(), O_WRONLY | O_CREAT, 0644); //6 = read + write;
            if (dst_fd == -1) {
                perror(("Failed to open destination file " + destination + "/" + data->d_name).c_str());
                close(src_fd);
                closedir(dir);
                return;
            }

            char buffer[this->BUFFER_SIZE];
            ssize_t bytes_read;
            while ((bytes_read = read(src_fd, buffer, this->BUFFER_SIZE)) > 0) {
                if (write(dst_fd, buffer, bytes_read) != bytes_read){
                    perror(("Failed to write to destination file " + destination + "/" + data->d_name).c_str());
                    break;
                }
            }

            close(src_fd);
            close(dst_fd);
        }
        closedir(dir);



    }

    
}