#include "Config.h"
#include <iostream>
#include <cstdlib>

CommandType ConfigParser::stringToCommand(const std::string& str) {
    static const std::unordered_map<std::string, CommandType> commandTable {
        {"generate", CommandType::generate},
        {"list", CommandType::list},
        {"delete",  CommandType::deleteLabel}, 
        {"resetAll", CommandType::resetAll},
        {"-g", CommandType::generate},
        {"-l", CommandType::list},
        {"-d", CommandType::deleteLabel},
        {"-re", CommandType::resetAll},
    };
    
    // 查找
    auto it = commandTable.find(str);
    if (it != commandTable.end()) {
        return it->second;
    }
    throw std::invalid_argument("Unknown command: " + str);
}

bool ConfigParser::parseArguments(int argc, char* argv[], CommandType& command, Config& config) {
    if (argc < 2) {
        return false;
    }

    // command = argv[1];

    switch (command) {
        case generate:
            if (argc < 5 || argc > 6) {
                return false;
            }

            try {
                config.min_val = std::stoi(argv[2]);
                config.max_val = std::stoi(argv[3]);
                config.count = std::stoi(argv[4]);

                if (config.count <= 0) {
                    std::cerr << "错误: 数量必须为正整数。" << std::endl;
                    return false;
                }

                if (argc == 6) {
                    config.label = argv[5];
                } else {
                    config.label = ""; // 未提供标签，将在主函数中确定
                }
            } catch (const std::invalid_argument&) {
                std::cerr << "错误: 最小值、最大值和数量必须是整数。" << std::endl;
                return false;
            } catch (const std::out_of_range&) {
                std::cerr << "错误: 参数超出范围。" << std::endl;
                return false;
            }
        case list:
            if (argc != 2) {
                return false;
            }
        case deleteLabel:
            if (argc != 3) {
                return false;
            }
            config.label = argv[2];
        case resetAll:
            return false;
        default:
            return false;
    }

    return true;
}

void ConfigParser::printUsage(const std::string& program_name) {
    std::cerr << "用法:" << std::endl;
    std::cerr << "  生成随机数:" << std::endl;
    std::cerr << "    " << program_name << " generate <最小值> <最大值> <数量> [标签]" << std::endl;
    std::cerr << "  查看所有标签及随机数:" << std::endl;
    std::cerr << "    " << program_name << " list" << std::endl;
    std::cerr << "  删除指定标签及其随机数记录:" << std::endl;
    std::cerr << "    " << program_name << " delete <标签>" << std::endl;
}