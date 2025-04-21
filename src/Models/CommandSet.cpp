#include "CommandSet.h"

CommandSet::CommandSet(string description, const unordered_set<string>& names)
    : Description(description) {
    for (const string& name : names) _names.insert(CleanCommand(name));
}

bool CommandSet::ContainsCommand(const string& name) {
    return _names.find(name) != _names.end();
}

bool CommandSet::ContainsAny(const CommandSet& other) {
    for (const string& name : other)
        if (ContainsCommand(name)) return true;
    return false;
}

bool CommandSet::EraseCommand(const string& name) { return _names.erase(name); }
