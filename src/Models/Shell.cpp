#ifndef Shell_CPP
#define Shell_CPP
/* For Defining Functions that are simple enough to not have to use OS specific
 * functions
 */
#include "Shell.hpp"

#include <algorithm>
#include <iostream>
#include <regex>

using std::cin;
using std::cout;
using std::endl;
#pragma region Command Mappings

/// @brief maps text to a command safely
/// @note exists for no accidental overwrites
/// @throws if the command already mapped
void Shell::MapCommand(CommandInfo* ptr, const vector<string>& commands) {
    for (const string& cmd : commands) {
        if (this->_commands.find(cmd) != this->_commands.end() ||
            Shell::COMMANDS.find(cmd) != Shell::COMMANDS.end())
            throw std::runtime_error(cmd + " is already mapped to a command");
        this->_commands[cmd] = ptr;
    }
}

Shell::Shell(unsigned int buffer) : BUFFER_SIZE(buffer) {
    Update_Directory();

    // extra mappings
    // MapCommand(&COMMANDS.at("cd"), {"chdir"});
    MapCommand(&COMMANDS.at("clr"), {"clear", "cls"});
    // dir
    MapCommand(&COMMANDS.at("environ"), {"env"});
    MapCommand(&COMMANDS.at("echo"), {"print", "show", "display"});
    MapCommand(&COMMANDS.at("help"), {"?", "info", "cmds", "commands"});
    // pause
    MapCommand(&COMMANDS.at("quit"),
               {"exit", "q", "leave", "close", "end", "stop"});
    // chmod
    // chown
    // ls
    // pwd
    // cat
    // mkdir
    // rmdir
    MapCommand(&COMMANDS.at("rm"), {"remove", "delete", "del"});
    // cp

    MapCommand(&COMMANDS.at("mv"), {"move", "copy"});
    // touch
    // grep
    // wc
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
    vector<std::pair<string, CommandInfo> >
        sorted;  // commands sorted by commandtype
    sorted.reserve(Shell::COMMANDS.size());

    cout << "Default Commands:" << endl;
    for (const auto& cmd : Shell::COMMANDS) sorted.push_back(cmd);

    // auto isnt allowed in lambdas for cpp 11
    sort(sorted.begin(), sorted.end(),
         [](std::pair<string, CommandInfo>& a,
            std::pair<string, CommandInfo>& b) {
             return a.second.Type < b.second.Type;
         });

    for (const auto& cmd : sorted)
        cout << cmd.first << "\t\t" << cmd.second.Description << endl;

    /*
cout << endl << "Extra Command Mappings:" << endl;
for (auto& cmd : _commands)
    cout << cmd.first << "\t\t" << cmd.second->Description << endl;
    */
}

/*
void Shell::Help(const CommandType& type, const string& example) {}
*/
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

#pragma region 11. ls just uses List_directory
void Shell::List() { this->List_Directory(this->_directory); }
#pragma endregion

#pragma region 12. pwd
void Shell::Print_Working_Directory() { cout << this->_directory << endl; }
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

string Util::ToString(const wchar_t* widechar) noexcept {
    if (widechar == NULL || widechar == nullptr) return string();
    std::wstring wstr(widechar, widechar + wcslen(widechar) + 1);
    return string(wstr.begin(), wstr.end());
}
