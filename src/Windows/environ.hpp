/** 4. environ */

void Shell::Environment_Variables() {
    wchar_t* envs = (wchar_t*)GetEnvironmentStringsW();
    if (envs == NULL) {
        perror("Failed to Get Environment Strings.");
        return;
    }

    for (wchar_t* e = envs; *e; e += wcslen(e) + 1) std::wcout << e << endl;

    FreeEnvironmentStringsW(envs);
}