#ifndef COMMANDINFO_H
#define COMMANDINFO_H
#include <string>

#include "CommandType.h"

using std::string;

struct CommandInfo {
    /// @brief The type of command
    CommandType Type;

    /// @brief The description of the command
    string Description;

    CommandInfo() : Type(CommandType::INVALID) {}

    CommandInfo(CommandType type, string description = string())
        : Type(type), Description(description) {}
};
#endif