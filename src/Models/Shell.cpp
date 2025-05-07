#ifndef Shell_CPP
#define Shell_CPP
/* For Defining Functions that are simple enough to not have to use OS specific
 * functions
 */
#include "Shell.h"

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::wcout;
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

Shell::~Shell() { _commands.clear(); }
// 1. cd probably depends on platform
//
void Shell::Clear_Screen() { cout << "\033[2J"; }
// 3. dir definitely depends on platform
// 4. environ probably depends on platform
#pragma endregion

// 5. basic echo is just cout
#pragma region 5. echo

void Shell::Echo(const string& text) {
    /// reduces multiple spaces to a single space
    cout << std::regex_replace(text, std::regex("[ \t]+"), " ");
}
#pragma endregion

#pragma region 6. help
void Shell::Help() {
    vector<pair<string, CommandInfo>> sorted;  // commands sorted by commandtype
    sorted.reserve(Shell::COMMANDS.size());

    cout << "Default Commands:" << endl;
    for (pair<const string, CommandInfo>& cmd : Shell::COMMANDS)
        sorted.push_back(cmd);

    sort(sorted.begin(), sorted.end(),
         [](auto& a, auto& b) { return a.second.Type < b.second.Type; });

    for (pair<string, CommandInfo>& cmd : sorted)
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
    {"cd", CommandInfo{CD, "Changes current directory"}},
    {"clr", CommandInfo{CLR, "Clears the display screen."}},
    {"dir", CommandInfo{DIR, "Lists the directory contents."}},
    {"environ", CommandInfo{ENVIRON, "Lists the environment variables."}},
    {"echo", CommandInfo{ECHO, "Displays text."}},
    {"help", CommandInfo{HELP, "Displays help."}},
    {"pause", CommandInfo{PAUSE, "Pauses the shell."}},
    {"quit", CommandInfo{QUIT, "Quits the shell process."}},
    {"chmod", CommandInfo{CHMOD, "Displays file permissions."}},
    {"chown", CommandInfo{CHOWN, "Displays file ownership."}},
    {"ls", CommandInfo{LS, "Lists Files."}},
    {"pwd", CommandInfo{PWD, "Prints the working directory."}},
    {"cat", CommandInfo{CAT, "Concatenates and prints file contents."}},
    {"mkdir", CommandInfo{MKDIR, "Creates a new directory."}},
    {"rmdir", CommandInfo{RMDIR, "Removes a directory."}},
    {"rm", CommandInfo{RM, "Removes a file."}},
    {"cp", CommandInfo{CP, "Copies a file."}},
    {"mv", CommandInfo{MV, "Moves a file."}},
    {"touch", CommandInfo{TOUCH, "Creates an empty file."}},
    {"grep", CommandInfo{GREP, "Searches for text patterns."}},
    {"wc", CommandInfo{WC, "Counts lines, words, and bytes."}}};

string Shell::SanitizeString(const string& input,
                             const unordered_set<char>& blacklist = {'\t', '\n',
                                                                     '\r'}) {
    if (input.empty()) return input;
    string sanitize;
    sanitize.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        if (isspace(input[i]) || blacklist.find(input[i]) != blacklist.end())
            continue;
        else
            sanitize.push_back(tolower(input[i]));
    }

    sanitize.shrink_to_fit();
    return sanitize;
}

#pragma endregion

std::string Util::ToString(const wstring& widestring) noexcept(true) {
    if (widestring.empty()) return string();
    return string(widestring.begin(), widestring.end());
}

std::string Util::ToString(const wchar_t* widechar) noexcept(true) {
    if (widechar == NULL || widechar == nullptr) return string();
    return ToString(wstring(widechar, wcslen(widechar)));
}