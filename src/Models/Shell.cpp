#ifndef Shell_CPP
#define Shell_CPP
/* For Defining Functions that are simple enough to not have to use OS specific
 * functions
 */
#include "Shell.h"

#include <algorithm>

#pragma region Command Mappings

Shell::Shell() {
    // for extra mappings
    CommandInfo* cmd_ptr = &(COMMANDS.at("help"));
    _commands["?"] = cmd_ptr;
    _commands["info"] = cmd_ptr;

    cmd_ptr = &COMMANDS.at("clr");
    _commands["clear"] = cmd_ptr;
    _commands["cls"] = cmd_ptr;

    _commands["env"] = &(COMMANDS.at("environ"));

    cmd_ptr = &COMMANDS.at("mv");
    _commands["move"] = cmd_ptr;
    _commands["copy"] = cmd_ptr;

    cmd_ptr = &COMMANDS.at("rm");
    _commands["remove"] = cmd_ptr;
    _commands["delete"] = cmd_ptr;
    _commands["del"] = cmd_ptr;

    cmd_ptr = &COMMANDS.at("echo");
    _commands["print"] = cmd_ptr;
    _commands["show"] = cmd_ptr;
    _commands["display"] = cmd_ptr;

    cmd_ptr = &COMMANDS.at("quit");
    _commands["exit"] = cmd_ptr;
    _commands["q"] = cmd_ptr;
    _commands["leave"] = cmd_ptr;
    _commands["close"] = cmd_ptr;
    _commands["end"] = cmd_ptr;
    _commands["stop"] = cmd_ptr;
};

// 1. cd probably depends on platform
// 2. clr probably depends on platform
// 3. dir definitely depends on platform
// 4. environ probably depends on platform
#pragma endregion

// 5. basic echo is just cout
#pragma region 5. echo
#include <regex>

void Shell::Echo(const string& text) {
    cout << std::regex_replace(text, std::regex("[ \t]+"), " ");
}
#pragma endregion

#pragma region 6. help
void Shell::Help() {
    vector<pair<string, CommandInfo>> sorted;  // commands sorted by commandtype
    sorted.reserve(Shell::COMMANDS.size());

    cout << "Default Commands:" << endl;
    for (auto& cmd : Shell::COMMANDS) sorted.push_back(cmd);

    sort(sorted.begin(), sorted.end(),
         [](auto& a, auto& b) { return a.second.Type < b.second.Type; });

    for (auto& cmd : sorted)
        cout << cmd.first << "\t\t" << cmd.second.Description << endl;

    /*
cout << endl << "Extra Command Mappings:" << endl;
for (auto& cmd : _commands)
    cout << cmd.first << "\t\t" << cmd.second->Description << endl;
    */
}

void Shell::Help(const CommandType& type, const string& example) {}

#pragma endregion

#pragma region 7. pause
void Shell::Pause() {
    cout << "Press Enter To Unpause...";

    cin.clear();
    cin.get();
}
#pragma endregion

#pragma region 8. quit
void Shell::Quit() { exit(0); }
#pragma endregion

#pragma region 9. chmod

#pragma endregion

#pragma region Command
CommandType Shell::GetCommandType(const string& cmd) {
    return GetCommandInfo(cmd).Type;
}
CommandInfo Shell::GetCommandInfo(const string& cmd) {
    if (Shell::COMMANDS.find(cmd) != Shell::COMMANDS.end())
        return Shell::COMMANDS.at(cmd);
    if (this->_commands.find(cmd) != this->_commands.end())
        return *this->_commands.at(cmd);
    else
        return CommandInfo(CommandType::INVALID,
                           "'" + cmd + "' is not a valid command.");
}
#endif

#pragma region Static Definitions
unordered_map<string, CommandInfo> Shell::COMMANDS = {
    {"cd", CommandInfo{cd, "Changes current directory"}},
    {"clr", CommandInfo{clr, "Clears the display screen."}},
    {"dir", CommandInfo{dir, "Lists the directory contents."}},
    {"environ", CommandInfo{env, "Lists the environment variables."}},
    {"echo", CommandInfo{echo, "Displays text."}},
    {"help", CommandInfo{help, "Displays help."}},
    {"pause", CommandInfo{pause, "Pauses the shell."}},
    {"quit", CommandInfo{quit, "Quits the shell process."}},
    {"chmod", CommandInfo{chmod, "Displays file permissions."}},
    {"chown", CommandInfo{chown, "Displays file ownership."}},
    {"ls", CommandInfo{ls, "Lists Files."}},
    {"pwd", CommandInfo{pwd, "Prints the working directory."}},
    {"cat", CommandInfo{cat, "Concatenates and prints file contents."}},
    {"mkdir", CommandInfo{mkdir, "Creates a new directory."}},
    {"rmdir", CommandInfo{rmdir, "Removes a directory."}},
    {"rm", CommandInfo{rm, "Removes a file."}},
    {"cp", CommandInfo{cp, "Copies a file."}},
    {"mv", CommandInfo{mv, "Moves a file."}},
    {"touch", CommandInfo{touch, "Creates an empty file."}},
    {"grep", CommandInfo{grep, "Searches for text patterns."}},
    {"wc", CommandInfo{wc, "Counts lines, words, and bytes."}}};

string Shell::SanitizeInput(const string& input,
                            const unordered_set<char>& blacklist = {'\t', '\n',
                                                                    '\r'}) {
    if (input.empty()) return input;
    string sanitize;
    sanitize.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        if (isspace(input[i]) || blacklist.find(input[i]) != blacklist.end())
            continue;
        else
            sanitize.push_back(input[i]);
    }

    sanitize.shrink_to_fit();
    return sanitize;
}

#pragma endregion