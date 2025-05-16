//3. dir

void Shell::List_Directory(const string &path)
{
    const char* dir = path.empty() ? "." : path.c_str();
    int fd = syscall(SYS_open, dir, O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open directory");
        return;
    }

    /**
        @brief Directory data
        @note the names of the properties cant be changed or bad things happen
    */
    struct data {
        unsigned long d_ino;
        off_t d_off;
        unsigned short d_reclen;
        char d_name[];
    };

    char buffer[this->BUFFER_SIZE];
    int nread;
    
    while ((nread = syscall(SYS_getdents, fd, buffer, sizeof(buffer))) > 0)
    {
        for (char *d = buffer; d < buffer + nread;) {
            struct data *de = (struct data *)d;
            cout << ((de->d_ino != 0) ? "<DIR>\t" : "\t");
            cout << de->d_name << endl;
            d += de->d_reclen;
        }
    }
    
    if (nread == -1)
        perror("Failed to read directory");

    syscall(SYS_close, fd);
}
