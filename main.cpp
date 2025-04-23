#ifdef _WIN32
#include "src/windows_Shell.cpp"
#else
#include "src/ubuntu_Shell.cpp"
#endif
#include <sstream>
using std::stringstream;

vector<string> SplitString(const string&, char);

int main() {
    CommandInfo cmd;
    string input;
    Shell shell;

    // shell.Help();
    while (cmd.Type != CommandType::quit) {
        cout << endl << "<< ";
        getline(cin, input);

        if (input.empty()) continue;  // skip empty

        cmd = shell.GetCommandInfo(Shell::SanitizeInput(input));

        cout << "Command: " << cmd.Type << endl;
        cout << "Description: " << cmd.Description << endl;

        /*if (shell.Execute(input) == -1)
            std::cerr << "Failed to start process " << input << endl;*/
    }
    // shell.Help(CommandType::cd, "help <command>");
}

/// @brief Splits string by delimiter
/// @param str
/// @param delimiter
/// @return vector of strings
vector<string> SplitString(const string& input, char delimiter) {
    vector<string> args;
    stringstream ss(input);
    string arg;
    while (getline(ss, arg, delimiter)) args.push_back(arg);

    return args;
}
