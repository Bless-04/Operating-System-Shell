// 21. word count (wc)


void Shell::Word_Count(const string &file)
{
    const int fd = open(file.c_str(), O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Failed to open '%s'\n", file.c_str());
        cout << "wc <files>" << endl;
        return;
    }

    size_t lines = 0, words = 0;
    char buffer[this->BUFFER_SIZE];
    size_t bytes;
    string text;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
        text.append(buffer, bytes);
    close(fd);

    // counting lines
    for (const char &c : text)
        if (c == '\n')
            lines++;

    istringstream ss(text);

    string word;
    while (ss >> word) words++;
    
    cout << file << endl;
    cout << "lines: " << lines << endl;
    cout << "words: " << words << endl;
    cout << "chararacters: " << text.length() << endl;
}