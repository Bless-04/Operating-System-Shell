/* For Defining Functions that are simple enough to not have to use OS specific
 * functions
 */
#include "Shell.h"

#include <algorithm>
#include <unordered_map>

#pragma region Command Mappings

Shell::Shell() {
    _commands["?"] = &(COMMANDS.at("help"));
    _commands["clear"] = &(COMMANDS.at("clr"));
};

/* Extra mapping; Not needed

_commands["cls"] = _commands.at("clr");
_commands["clear"] = _commands.at("clr");

_commands["move"] = _commands.at("mv");
_commands["copy"] = _commands.at("cp");
_commands["remove"] = _commands.at("rm");
_commands["delete"] = _commands.at("rm");
_commands["print"] = _commands.at("echo");
_commands["show"] = _commands.at("echo");
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

    // sort(sorted.begin(), sorted.end());

    for (const pair<string, CommandInfo>& cmd : sorted)
        cout << cmd.first << "\t\t" << cmd.second.Description << endl;
}
#pragma endregion

#pragma region 7. pause
void Shell::Pause() {
    cout << "Press Enter to continue...";
    std::cin.ignore();
}
#pragma endregion

#pragma region 8. quit
void Shell::Quit() { this->~Shell(); }
#pragma endregion

#pragma region 9. chmod

#pragma endregion

#pragma region Command
CommandType Shell::GetCommandType(const string& cmd) {
    return Shell::COMMANDS.find(cmd) != Shell::COMMANDS.end() ||
                   _commands.find(cmd) != _commands.end()
               ? Shell::COMMANDS.at(cmd).Type
               : CommandType::INVALID;
}

string SanitizeInput(string input) {
    const size_t n = input.size();  // cus size might change
    for (size_t i = 0; i < n; i++) {
        if (isspace(input[i])) input.erase(i--, i);
        input[i] = tolower(input[i]);
    }
    // delete spaces
    input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
    return input;
}