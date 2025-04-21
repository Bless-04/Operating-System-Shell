// fixes  multiple includes problem
#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "CommandInfo.h"
#include "CommandSet.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::unordered_map;
using std::vector;

/**
 * @author Blessing Abumere
 * @brief Shell object For COSC 439 Project
 */

class Shell {
   private:
#pragma region Command Mappings

    /// @brief Default Commands; command names to the commandinfo
    /// @note everything is lowercase
    static unordered_map<string, CommandInfo> COMMANDS;

    /// @brief for extra naming
    unordered_map<string, CommandInfo*> _commands;
#pragma endregion

   public:
    /// @brief Default Shell constructor
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
    void Change_Directory(string path);

    /** (cls)
     * clears the display screen. */
    void Clear_Screen();

    /** (dir)
     * the contents of a specified directory.
     * @param directory The specified directory
     * */
    void List_Directory_Contents(string directory);

    /** (environ)
     * displays all environment strings. */
    void Environment_Variables();

    /** (echo)
     * displays a comment on the screen, followed by a new line.
     * @note Reduces multiple spaces/tabs to a single space.
     */
    void Echo(string comment);

    /** (help)
     *  Displays the user manual using the more filter. */
    void Help();

    /** (pause)
     * pause shell operations until 'Enter' is pressed. */
    void Pause();

    /** (quit)
     *
     * exit the shell.
     * @note Its just a destructor
     * */
    void Quit();

    /** (chmod)
     * modifies file permissions for users, groups, and others. */
    void File_Permissions(string);

    /** (chown)
     * Changes the ownership of a file or directory, allowing a user to
     * specify the new owner and/or group. */
    void Change_Ownership(string);

    /** (ls)
     * Display a list of files and directories in the current directory. */
    void List_Files(string);

    /** (pwd)
     * Print the current working directory to the standard output.  */
    void Print_Working_Directory();

    /** (cat)
     * Read files sequentially and output their contents to the standard
     * output.
     */
    void Concatenate_and_Display_Files(string);

    /** (mkdir)
     * Create one or more directories specified by the user. */
    void Create_Directories(string);

    /** (rmdir)
     * Remove one or more directories specified by the user */
    void Remove_Directories(string);

    /** (rm)
     * Delete specified files or directories. */
    void Remove_Files(vector<string>);

    /** (cp)
     * copies files or directories from one location to another */
    void Copy_Files(string);

    /** (mv)
     * moves files or directories from one location to another */
    void Move_Files(string);

    /** (touch)
     * creates empty files or updates access/modification times */
    void Create_Empty_Files(string);

    /** (grep)
     * Search for specified patterns in files or input and display matching
     * lines. */
    void Search_Text_Patterns(string);

    /** (wc)
     * counts the number of lines, words, and characters in a file */
    void Word_Count(string);
#pragma endregion
};

#pragma region default commands
unordered_map<string, CommandInfo> Shell::COMMANDS = {
    {"cd", CommandInfo{cd, "Changes current directory"}},
    {"clr", CommandInfo{clr, "Clears the display screen."}},
    {"dir", CommandInfo{dir, "Lists the directory contents."}},
    {"environ", CommandInfo{env, "Lists the environment variables."}},
    {"echo", CommandInfo{echo, "Displays a comment."}},
    {"help", CommandInfo{help, "Displays help."}},
    {"pause", CommandInfo{pause, "Pauses the shell."}},
    {"quit", CommandInfo{quit, "Quits the shell."}},
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

#endif