#ifndef COMMANDTYPE_H
#define COMMANDTYPE_H
/**
 *Enumeration of command types
 * Maps each command given in the Proj2.pdf to an integer
 */
enum CommandType {
    /// @brief Invalid Command
    /// @note For when command doesnt exist
    INVALID = false,

    /// @brief Change Directory
    CD = 1,

    /// @brief Clear Screen
    CLR = 2,

    /// @brief List Directory Contents
    LIST_DIR = 3,

    /// @brief  Environment Variables
    ENVIRON = 4,

    /// @brief Echo Command
    ECHO = 5,

    /// @brief Help Manual
    HELP = 6,

    /// @brief Pause Operation
    PAUSE = 7,

    /// @brief Quit Command
    QUIT = 8,

    /// @brief File Permissions
    CHMOD = 9,

    /// @brief Change Ownership
    CHOWN = 10,

    /// @brief List Files
    LS = 11,

    /// @brief Print Working Directory
    PWD = 12,

    /// @brief Concatenate and Display Files
    CAT = 13,

    /// @brief Create Directories
    MKDIR = 14,

    /// @brief Remove Directories
    RMDIR = 15,

    /// @brief Remove Files
    RM = 16,

    /// @brief Copy Files
    CP = 17,

    /// @brief Move Files
    MV = 18,

    /// @brief Create Empty Files
    TOUCH = 19,

    /// @brief Search Text Patterns
    GREP = 20,

    /// @brief Word Count
    WC = 21
};
#endif
