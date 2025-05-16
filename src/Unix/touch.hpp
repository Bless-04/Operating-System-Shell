//19. Create (touch)

void Shell::Create_Empty_Files(const vector<string> &files)
{
    for (const string& file : files){
        int f = syscall(SYS_open, file.c_str(), O_CREAT | O_WRONLY, 0644);
        if (f == -1)
            perror(("touch failed for " + file).c_str());
        else 
            syscall(SYS_close, f);
        
    }
}
