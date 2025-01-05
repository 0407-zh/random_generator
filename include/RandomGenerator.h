#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "Config.h"
#include <vector>
#include <map>
#include <set>
#include <string>

class RandomGenerator {
public:
    static bool generate(const Config& config, const std::map<std::string, std::set<int>>& label_to_numbers, std::vector<int>& new_numbers);
};

#endif RANDOMGENERATOR_H