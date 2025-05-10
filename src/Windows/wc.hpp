/* 21. wc*/

void Shell::Word_Count(const string& file) {
    size_t lines = 1, words = 0;

    const string& text = Shell::Read_File(file);
    if (text.empty()) return;

    // number of characters is how ever long the text is
    const size_t chars = text.length();

    for (const char& c : text)
        if (c == '\n') lines++;

    istringstream ss(text);  // input only stream
    string word;
    while (ss >> word) words++;

    cout << file << endl;
    cout << "Characters: " << chars << endl;
    cout << "Words: " << words << endl;
    cout << "Lines: " << lines << endl;
}