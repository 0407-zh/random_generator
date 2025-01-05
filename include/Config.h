#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct Config {
    int min_val;
    int max_val;
    int count;
    std::string label;
};

enum CommandType {
    generate,
    list,
    deleteLabel,
    resetAll,
};

class ConfigParser {
public:
    static bool parseArguments(int argc, char* argv[], CommandType& command, Config& config);
    static void printUsage(const std::string& program_name);
    static CommandType stringToCommand(const std::string& str);
};

#endif // CONFIG_H