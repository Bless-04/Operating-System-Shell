#include "src/Shells/Windows.h"

string FormatInput(const string& input);

int main() {
    Shell shell;
    shell.Help();
}

string FormatInput(const string& input) {
    string lower_name = "";
    lower_name.reserve(input.size());

    // Remove spaces and lowercase
    for (const char& c : input)
        if (c != _SPACE || c != ' ') lower_name.push_back(tolower(c));

    return lower_name;
}