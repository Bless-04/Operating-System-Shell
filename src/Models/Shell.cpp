#ifndef Shell_CPP
#define Shell_CPP
/* For Defining Functions that are simple enough to not have to use OS specific
 * functions
 */
#include "Shell.h"

#include <algorithm>
#include <unordered_map>

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
};

/* Extra mapping; Not needed

_commands["cls"] = _commands.at("clr");
_commands["clear"] = _commands.at("clr");


*/

#pragma region 1. cd

#pragma endregion

#pragma region 2. clr
#pragma endregion

#pragma region 3. dir
// void Shell::List_Directory_Contents(string path);
#pragma endregion

#pragma region 4. environ
void Shell::Environment_Variables() {
    cout << "Shell Listed environment variables" << endl;
}
#pragma endregion

#pragma region 5. echo
void Shell::Echo(const string& text) { cout << text << endl; }
#pragma endregion

#pragma region 6. help
void Shell::Help() {
    vector<pair<string, CommandInfo>> sorted;  // commands sorted by commandtype
    sorted.reserve(Shell::COMMANDS.size());

    for (const pair<string, CommandInfo>& cmd : Shell::COMMANDS)
        sorted.push_back(cmd);

    sort(sorted.begin(), sorted.end(),
         [](auto& a, auto& b) { return a.second.Type < b.second.Type; });

    for (const pair<string, CommandInfo>& cmd : sorted)
        cout << cmd.first << "\t\t" << cmd.second.Description << endl;
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
const CommandInfo Shell::GetCommandInfo(const string& cmd) {
    if (Shell::COMMANDS.find(cmd) != Shell::COMMANDS.end())
        return Shell::COMMANDS.at(cmd);
    if (this->_commands.find(cmd) != this->_commands.end())
        return *this->_commands.at(cmd);
    else
        return CommandInfo(CommandType::INVALID,
                           "'" + cmd + "' is not a valid command.");
}
#endif
