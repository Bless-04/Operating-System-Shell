#include <sstream>

#include "src/shell_headers.h"

using std::getline;
using std::stringstream;

vector<string> SplitString(const string&, char);
void TryExecute(const string&, Shell&, CommandInfo&);
int main() {
    cout << "COSC 439 Shell (" << OS << ")";
    CommandInfo cmd;
    string input;
    Shell shell;

    while (cmd.Type != QUIT) {
        cout << endl << ">> ";
        getline(cin, input);

        if (input.empty()) continue;  // skip empty

        TryExecute(input, shell, cmd);
    }
    // shell.Help(CommandType::cd, "help <command>");
}

/*stuff under here could be moved to a separate file */

/// @brief Splits string by delimiter
/// @param str
/// @param delimiter
/// @return vector of strings
vector<string> SplitString(const string& input, char delimiter = ' ') {
    vector<string> args;
    stringstream ss(input);
    string arg;
    while (getline(ss, arg, delimiter)) args.push_back(arg);

    return args;
}

/// @brief Deletes spaces before [0] index
/// @note this exists so commands commands like "     echo text1 text2 " can
/// still work like the normal echo cmd
/// @param args
void DeleteStartingSpaces(vector<string>& args) {
    while (args.size() > 0 && (args[0].empty() || args[0] == " "))
        args.erase(args.begin());
}

void TryExecute(const string& input, Shell& shell, CommandInfo& cmd_info) {
    vector<string> args = SplitString(input, ' ');

    DeleteStartingSpaces(args);
    args.shrink_to_fit();

    string text;
    cmd_info = shell.GetCommandType(Shell::SanitizeString(args[0]));

    switch (cmd_info.Type) {
        case CD:
            break;
        case CLR:
            shell.Clear_Screen();
            break;
        case DIR:
            // shell.List_Directory_Contents(input.substr(4));
            break;
        case ENVIRON:
            shell.Environment_Variables();
            break;
        case ECHO:
            text.clear();
            for (size_t i = 1; i < args.size(); ++i) text.append(args[i] + ' ');
            shell.Echo(text);
            break;
        case HELP:
            shell.Help();
            break;
        case PAUSE:
            shell.Pause();
            break;
        case QUIT:
            shell.Quit();
            break;
        case CHMOD:
            // shell.File_Permissions(input.substr(7));
            break;
        case CHOWN:
            // shell.File_Permissions();
            break;
        case LS:
            //  shell.List_Files();
            break;
        case PWD:
            //   shell.Print_Working_Directory();
            break;
        case CAT:
            // shell.Concatenate_File(input.substr(4));
            break;
        case MKDIR:
            // shell.Create_Directories();
            break;
        case RMDIR:
            // shell.Remove_Directories(args[1]);
            break;
        case RM:
            // shell.Remove_Files(args[1]);
            break;

        default:
        case INVALID:

            int pid = shell.Execute(input);
            if (pid == -1)

                cerr << "'" << args[0]
                     << "' is not a valid command or executable" << endl;
            else
                cout << "Process started with PID: " << pid << endl;

            break;
    }
}
