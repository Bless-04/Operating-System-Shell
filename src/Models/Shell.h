// fixes  multiple includes problem
#ifndef SHELL_H
#define SHELL_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CommandInfo.h"

using std::unordered_map;
using std::unordered_set;
using std::vector;

#ifndef pid_t
#define pid_t long long  // process id
#endif

/**
 * @brief Shell object For COSC 439 Project
 * @note It holds the command mappings and the command definitions/functions
 */
class Shell {
   private:
#pragma region Command Functionality

    /// @brief The current working directory
    string _directory;

    /// @brief Updates the shell directory variable
    /// @return True if the directory was updated
    /// @note use for stuff that change directory
    bool Update_Directory() noexcept;

    /// @brief Default Commands; command names to the commandinfo
    /// @note all commands should be lowercase
    /// @note static because these are defaults
    static unordered_map<string, CommandInfo> COMMANDS;

    /// @brief for extra naming
    /// @note pointer to default commands for no copying
    unordered_map<string, CommandInfo*> _commands;

   public:
    // Shell() = default;

    /// @brief Deletes anything dynamically alloced
    ~Shell();

    /// @brief CommandType using the string
    /// @param string The  command name
    /// @return CommandType The command type of the command if it exists and
    /// Invalid/0/false if it doesnt
    /// @note string should be sanitized
    CommandType GetCommandType(const string&);

    /// @brief CommandInfo using the string
    /// @param string The command name
    /// @return A copy of the command info of the command;
    /// @note if the command doesnt exist is returns CommandInfo with type
    /// @note string should be sanitized
    CommandInfo GetCommandInfo(const string&);
    CommandInfo operator[](const string& cmd) { return GetCommandInfo(cmd); }
    CommandInfo operator[](const CommandType& cmd) {
        for (const auto& command : Shell::COMMANDS)
            if (command.second.Type == cmd) return command.second;
        return CommandInfo(CommandType::INVALID);
    }
    /// @brief sanitizes the input string by removing spaces and converting to
    /// lowercase for easy searching
    /// @param input the sanitized input
    /// @param blacklist characters to remove
    /// @return The sanitized string
    /// @note the unordered_set must have something in it by default or it will
    /// give an out of bounds error. It should have a default value
    static string SanitizeString(const string& input,
                                 const unordered_set<char>& Remove);

#pragma endregion

    /// @brief Default Shell constructor
    /// @note the extra commands are added in here
    Shell();

#pragma region Features To Implement For Project in Order
    /** (cd)
     *
     * switches the default directory to the specified path.
     * @param path The specified path
     * @note if no directory argument is provided, displays the current
     * directory.
     * @note Reports errors for non existing directories and updates the
     * PWD environment variable accordingly.
     * @return true if directory exists
     * */
    void Change_Directory(const string&);

    /** (cls)
     * clears the display screen. */
    void Clear_Screen();

    /** (dir)
     * the contents of a specified directory.
     * @param directory The specified directory
     * */
    void List_Directory_Contents(const string&);

    /** (environ)
     * displays all environment strings. */
    void Environment_Variables();

    /** (echo)
     * displays a comment on the screen, followed by a new line.
     * @note Reduces multiple spaces/tabs to a single space.
     */
    void Echo(const string&);

    /** (help)
     *  Displays the user manual using the more filter. */
    void Help(const CommandType&, const string&);

    /// @brief Displays default commands
    void Help();

    /** (pause)
     * pause shell operations until 'Enter' is pressed. */
    void Pause();

    /** (quit)
     *
     * exit the shell.
     * @note ends program
     * */
    void Quit();

    /** (chmod)
     * modifies file permissions for users, groups, and others. */
    void File_Permissions(const string&);

    /** (chown)
     * Changes the ownership of a file or directory, allowing a user to
     * specify the new owner and/or group. */
    void Change_Ownership(const string&, const vector<string>& paths);

    /** (ls)
     * Display a list of files and directories in the current directory. */
    void List_Files();

    /** (pwd)
     * Print the current working directory to the standard output.  */
    void Print_Working_Directory();

    /** (cat)
     * Read files sequentially and output their contents to the standard
     * output.
     */
    void Concatenate_and_Display_Files(const vector<string>&);

    /** (mkdir)
     * Create one or more directories specified by the user. */
    void Create_Directories(const vector<string>&);

    /** (rmdir)
     * Remove one or more directories specified by the user */
    void Remove_Directories(const vector<string>&);

    /** (rm)
     * Delete specified files or directories. */
    void Remove_Files(const vector<string>&);

    /** (cp)
     * copies files or directories from one location to another */
    void Copy_Files(const vector<string>&, const string&);

    /** (mv)
     * moves files or directories from one location to another */
    void Move_Files(const vector<string>&);

    /** (touch)
     * creates empty files or updates access/modification times */
    void Create_Empty_Files(const string&);

    /** (grep)
     * Search for specified patterns in files or input and display matching
     * lines. */
    void Search_Text_Patterns(const string&, const string&);

    /** (wc)
     * counts the number of lines, words, and characters in a file */
    void Word_Count(const string&);
#pragma endregion

    /** (execute)
     * executes a executable in the shell.
     * @param name the name of the executable to run
     * @example execute("cmd.exe")
     * @example execute("chrome.exe")
     * @returns the process id of whatever process got executed;
     * @returns -1 if failed
     * */
    pid_t Execute(string name);
};

/// @brief Global Util Functions
/// @note they work the same no matter the os
namespace Util {

    /// @param widechar
    /// @returns wide char as a string
    std::string ToString(const wchar_t* widechar) noexcept;

}  // namespace Util

#endif