// 10. chown

void Shell::Change_Ownership(vector<string> paths)
{
    if (paths.size() == 0 || paths[0].empty()){
        fprintf(stderr, "No files were given\n");
        cout << "chown <owner> <files>" << endl;
        return;
    }
    struct passwd *pw = getpwnam(paths[0].c_str());
    if (!pw)
    {
        perror("Failed to change ownership");
        return;
    }

    paths.erase(paths.begin());

    for (const string &path : paths)
        if (chown(path.c_str(), pw->pw_uid, pw->pw_gid) != 0)
            perror("chown failed");
}
