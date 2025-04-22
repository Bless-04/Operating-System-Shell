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
    cd = 1,

    /// @brief Clear Screen
    clr = 2,

    /// @brief List Directory Contents
    dir = 3,

    /// @brief  Environment Variables
    env = 4,

    /// @brief Echo Command
    echo = 5,

    /// @brief Help Manual
    help = 6,

    /// @brief Pause Operation
    pause = 7,

    /// @brief Quit Command
    quit = 8,

    /// @brief File Permissions
    chmod = 9,

    /// @brief Change Ownership
    chown = 10,

    /// @brief List Files
    ls = 11,

    /// @brief Print Working Directory
    pwd = 12,

    /// @brief Concatenate and Display Files
    cat = 13,

    /// @brief Create Directories
    mkdir = 14,

    /// @brief Remove Directories
    rmdir = 15,

    /// @brief Remove Files
    rm = 16,

    /// @brief Copy Files
    cp = 17,

    /// @brief Move Files
    mv = 18,

    /// @brief Create Empty Files
    touch = 19,

    /// @brief Search Text Patterns
    grep = 20,

    /// @brief Word Count
    wc = 21
};
#endif
