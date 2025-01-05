#include "RandomGenerator.h"
#include <algorithm>
#include <random>

bool RandomGenerator::generate(const Config& config, const std::map<std::string, std::set<int>>& label_to_numbers, std::vector<int>& new_numbers) {
    std::set<int> generated_numbers;
    auto it = label_to_numbers.find(config.label);
    if (it != label_to_numbers.end()) {
        generated_numbers = it->second;
    }

    // 构建可用数字列表
    std::vector<int> available_numbers;
    for (int num = config.min_val; num <= config.max_val; ++num) {
        if (generated_numbers.find(num) == generated_numbers.end()) {
            available_numbers.push_back(num);
        }
    }

    if (available_numbers.size() < static_cast<size_t>(config.count)) {
        return false;
    }

    // 随机打乱可用数字列表
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_numbers.begin(), available_numbers.end(), gen);

    // 选择前 `count` 个数字
    new_numbers.assign(available_numbers.begin(), available_numbers.begin() + config.count);

    return true;
}