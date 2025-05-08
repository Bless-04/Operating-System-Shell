#include <sstream>

#include "src/shell_type.h"

using std::cerr;
using std::getline;
using std::stringstream;

vector<string> SplitString(const string&, char);
CommandInfo TryExecute(const string&, Shell&);

int main() {
    CommandInfo cmd;
    string input;
    Shell shell;

    cout << "COSC 439 Shell (" << OS << ")" << endl;

    while (cmd.Type != QUIT) {
        cout << endl;
        shell.Print_Working_Directory();
        cout << ">> ";
        getline(cin, input);

        if (input.empty()) continue;  // skip empty

        cmd = TryExecute(input, shell);
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

/// @brief trys to run a shell command
/// @param input string input
/// @param shell the shell to use
/// @return CommandInfo of the command executed
CommandInfo TryExecute(const string& input, Shell& shell) {
    vector<string> args = SplitString(input, ' ');

    DeleteStartingSpaces(args);

    string text;
    CommandInfo cmd_info = shell.GetCommandType(Shell::SanitizeString(args[0]));

    /// @note to guarantee no segfault for things that need arg[1]
    if (args.size() == 1) args.push_back(string());

    switch (cmd_info.Type) {
        case CD:
            shell.Change_Directory(args[1]);
            break;
        case CLR:
            shell.Clear_Screen();
            break;
        case DIR:
            shell.List_Directory(args[1]);
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
            shell.Change_Mode(input.substr(7));
            break;
        case CHOWN:
            // shell.Change_Ownership();
            break;
        case LS:
            shell.List();
            break;
        case PWD:
            shell.Print_Working_Directory();
            break;
        case CAT:
            //  shell.Concatenate(input.substr(4));
            break;
        case MKDIR:
            shell.Make_Directories(
                vector<string>(args.begin() + 1, args.end()));
            break;
        case RMDIR:

            // shell.Remove_Directories();
            break;
        case RM:
            // shell.Remove(args[1]);
            break;
        case CP:
            // shell.Copy_File(args[1], args[2]);
            break;
        case MV:
            // shell.Move_File(args[1], args[2]);
            break;
        case TOUCH:
            // shell.Create_Empty_File(args[1]);
            break;
        case GREP:
            // shell.Search_File(args[1], args[2]);
            break;
        case WC:
            shell.Word_Count(args[1]);
            break;

        default:
        case INVALID:

            pid_t pid = shell.Execute(input);
            if (pid == -1)
                fprintf(stderr,
                        "'%s' is not an existing command, operable program or "
                        "batch file\n",
                        args[0].c_str());
            else
                cout << "Process started with PID: " << pid << endl;
            break;
    }

    return cmd_info;
}
