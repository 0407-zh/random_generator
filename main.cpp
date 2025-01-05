#include "Config.h"
#include "Storage.h"
#include "CommandHandler.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Config config;
    
    std::string commandStr = argv[1];
    CommandType command = ConfigParser::stringToCommand(commandStr);

    bool parseResult = ConfigParser::parseArguments(argc, argv, command, config);

    if (!parseResult) {
        ConfigParser::printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    Storage storage("generated_numbers.txt");

    CommandHandler handler(storage);

    switch (command) {
    case generate:
        handler.handleGenerate(config);
        break;
    case list:
        handler.handleList();
        break;
    case deleteLabel:
        handler.handleDelete(config.label);
        break;
    case resetAll:
        break;
    default:
        std::cerr << "错误: 未知的命令 \"" << command << "\"。" << std::endl;
        ConfigParser::printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}