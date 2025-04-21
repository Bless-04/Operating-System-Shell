#include <string>
#include <unordered_set>

using std::pair;
using std::string;
using std::unordered_set;

/**
 * CommandSet class representing a set of commands with their names and a
 * description for the command
 * @note The command names are stored in lowercase and without spaces and its
 * just a unordered_set at the base
 **
 */
class CommandSet {
   private:
    /// @brief command aliases
    unordered_set<string> _names;

   public:
    /// @return The string as a lowercase string with no spaces
    string CleanCommand(const string&);

    /// @brief description of the command
    /// @note Should be in the format 'COMMAND' '\t ' 'DESCRIPTION'
    const string Description;

    CommandSet(string, const unordered_set<string>&);

    /// @return True if the command was erased from the set
    bool EraseCommand(const string&);

    /// @return True if the command exists in the set
    bool ContainsCommand(const string&);

    /// @return True if any of the commands in the other set exist in this set
    bool ContainsAny(const CommandSet&);
#pragma region For Looping
    auto cbegin() const { return _names.cbegin(); }
    auto begin() const { return _names.begin(); }
    auto end() const { return _names.end(); }
    auto cend() const { return _names.cend(); }
#pragma endregion
};