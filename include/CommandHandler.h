#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "Storage.h"
#include "RandomGenerator.h"
#include "Config.h"
#include <vector>
#include <set>
#include <map>
#include <string>

class CommandHandler {
public:
    CommandHandler(Storage& storage);
    void handleGenerate(const Config& config);
    void handleList();
    void handleDelete(const std::string& label);
private:
    Storage& storage_;
    std::map<std::string, std::set<int>> label_to_numbers_;
    std::string last_label_;
    void loadData();
};

#endif COMMANDHANDLER_H