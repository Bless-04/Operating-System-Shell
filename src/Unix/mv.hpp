//18. Move Files (mv)

void Shell::Move(vector<string> files)
{
    if (files.size() < 2 || files[0].empty() ) {
        fprintf(stderr, "Not enough argument given\n");
        cout << "mv <source> <destination>" << endl;
        return;
    }
    
    const string destination = files.back();
    files.pop_back();

    
    struct stat data;
    if (stat(destination.c_str(), &data) == 0 && S_ISDIR(data.st_mode)) {
        // Destination is a directory, move files into it
        for (const string& file : files) 
            if (rename(file.c_str(), (destination + '/' + file).c_str()) != 0) 
                perror(("Failed to move " + file).c_str());
        
    } else {
        
        if (files.size() > 2) {
            fprintf(stderr, "Too many files passed\n");
            return;
        }

        //basic move
        if (rename(files[0].c_str(), destination.c_str()) != 0) 
            perror(("Failed to move " + files[0]).c_str());
    }
}