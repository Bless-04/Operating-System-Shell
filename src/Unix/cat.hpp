// 13. cat

void Shell::Concatenate(const vector<string> &files)
{
    if (files.size() == 0 ||files[0].empty())
    {
        fprintf(stderr, "No files were given\n");
        cout << "cat <files>" << endl;
        return;
    }

    for (const string &file : files)
    {
        int fd = open(file.c_str(), O_RDONLY);
        if (fd == -1)
        {
            perror(("failed to read " + file).c_str());
            continue;
        }

        char buffer[this->BUFFER_SIZE];
        size_t bytesRead;
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
            write(STDOUT_FILENO, buffer, bytesRead);

        close(fd);
    }
}
