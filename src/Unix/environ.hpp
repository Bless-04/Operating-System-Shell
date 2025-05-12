/** 4. environ */

void Shell::Environment_Variables()
{
    extern char **environ;
    for (int i = 0; environ[i]; ++i)
    {
        cout << environ[i] << endl;
    }
}