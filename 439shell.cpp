#include <sstream> 

#include "src/shell_type.h"

using std::getline;
using std::stringstream;

vector<string> SplitString(const string&, char);
CommandInfo TryExecute(const string&, Shell&);
CommandInfo TryExecute(vector<string>&, Shell&);
CommandInfo TryExecute(char**, const int, Shell&);

/// @brief takes command line args
int main(int argc, char** argv) {
    CommandInfo cmd;
    string input;
    Shell shell;  // default is 1024

    // TryExecute("wc test.txt", shell);
    cout << "COSC 439 Shell (" << OS << ")" << endl;

    // if run from command line with args
    if (argc > 1) {
        if (argc == 2)
            cmd = TryExecute(argv[1], shell);
        else
            cmd = TryExecute(argv, argc, shell);

        if (cmd.Type == INVALID) exit(1);

        exit(0);
    }

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

/// @brief try execute with vector
/// @param args raw args
/// @param shell
/// @return command info
CommandInfo TryExecute(vector<string>& args, Shell& shell) {
    CommandInfo cmd_info = shell.GetCommandType(Shell::SanitizeString(args[0]));
    /// @note to guarantee no segfault for things that need arg[1]
    if (args.size() < 2)
        while (args.size() < 2) args.push_back(string());

    string text;  // for anything that need specific formatted text ; string
                  // dummy var
    switch (cmd_info.Type) {
        case CD:
            shell.Change_Directory(args[1]);
            break;
        case CLR:
            shell.Clear_Screen();
            break;
        case LIST_DIR:
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
            shell.Change_Mode(args[1]);
            break;
        case CHOWN:
            shell.Change_Ownership(args[1], vector<string>(args.begin() + 2, args.end()));
            break;
        case LS:
            shell.List();
            break;
        case PWD:
            shell.Print_Working_Directory();
            break;
        case CAT:
            shell.Concatenate(vector<string>(args.begin() + 1, args.end()));
            break;
        case MKDIR:
            shell.Make_Directories(
                vector<string>(args.begin() + 1, args.end()));
            break;
        case RMDIR:
            shell.Remove_Directories(
                vector<string>(args.begin() + 1, args.end()));
            break;
        case RM:
            shell.Remove(vector<string>(args.begin() + 1, args.end()));
            break;
        case CP:
            shell.Copy(vector<string>(args.begin() + 1, args.end() - 1),
                       args.back());
            break;
        case MV:
            shell.Move(vector<string>(args.begin() + 1, args.end() - 1),
                       args.back());
            break;
        case TOUCH:
            shell.Create_Empty_Files(
                vector<string>(args.begin() + 1, args.end()));
            break;
        case GREP:

            if (args.size() < 3) {
                fprintf(stderr, "Not enough arguments given\n");
                return INVALID;
            }
            shell.Search_Text_Patterns(args[1], args[2]);
            break;
        case WC:
            shell.Word_Count(args[1]);
            break;

        default:
            return INVALID;
    }

    return cmd_info;
}

/// @brief
/// @param c_args // command line args
/// @param argc
/// @param shell
/// @note exists to make running from command line easier
/// @return
CommandInfo TryExecute(char** c_args, const int argc, Shell& shell) {
    vector<string> v_args = vector<string>(argc);

    for (int i = 1; i < argc; ++i) v_args[i - 1] = string(c_args[i]);

    return TryExecute(v_args, shell);
}

/// @brief trys to run a shell command
/// @param input string input
/// @param shell the shell to use
/// @return CommandInfo of the command executed
CommandInfo TryExecute(const string& input, Shell& shell) {
    vector<string> args = SplitString(input, ' ');

    DeleteStartingSpaces(args);

    const CommandInfo& info = TryExecute(args, shell);

    if (info.Type == INVALID) {
        pid_t pid = shell.Execute(input);
        if (pid == -1)
            fprintf(stderr,
                    "'%s' is not an existing command, operable program or "
                    "batch file\n",
                    args[0].c_str());
        else
            printf("Finished Process '%s' with PID: %lld\n", args[0].c_str(),
                   pid);
    }
    return info;
}