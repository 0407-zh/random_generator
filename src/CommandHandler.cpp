#include "CommandHandler.h"
#include <iostream>

CommandHandler::CommandHandler(Storage& storage) : storage_(storage), last_label_("default") {
    loadData();
}

void CommandHandler::loadData() {
    storage_.read(label_to_numbers_, last_label_);
}

void CommandHandler::handleGenerate(const Config& config) {
    // 确定当前标签
    std::string current_label = config.label.empty() ? last_label_ : config.label;

    // 更新 config 的标签
    Config updated_config = config;
    updated_config.label = current_label;

    // 检查可用数字数量
    if (updated_config.min_val > updated_config.max_val) {
        std::cerr << "错误: 最小值不能大于最大值。" << std::endl;
        return;
    }

    int total_range = updated_config.max_val - updated_config.min_val + 1;
    int already_generated = label_to_numbers_[current_label].size();
    int available = total_range - already_generated;

    if (available <= 0) {
        std::cerr << "错误: 在标签 \"" << current_label << "\" 下，所有可能的数字都已经生成过了。" << std::endl;
        return;
    }

    if (updated_config.count > available) {
        std::cerr << "错误: 请求的数量超过了在标签 \"" << current_label << "\" 下的可用数字。可用数字数量: " << available << std::endl;
        return;
    }

    // 生成随机数
    std::vector<int> new_numbers;
    if (!RandomGenerator::generate(updated_config, label_to_numbers_, new_numbers)) {
        std::cerr << "错误: 随机数生成失败。" << std::endl;
        return;
    }

    // 输出生成的随机数
    std::cout << "标签 \"" << current_label << "\" 生成的随机数: ";
    for (const auto& num : new_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 更新存储数据
    label_to_numbers_[current_label].insert(new_numbers.begin(), new_numbers.end());

    // 保存生成的随机数
    std::set<int> new_numbers_set(new_numbers.begin(), new_numbers.end());
    if (!storage_.append(current_label, new_numbers_set)) {
        std::cerr << "错误: 无法保存生成的随机数。" << std::endl;
        return;
    }

    // 更新最后一个标签
    last_label_ = current_label;
}

void CommandHandler::handleList() {
    if (label_to_numbers_.empty()) {
        std::cout << "没有任何标签或随机数记录。" << std::endl;
        return;
    }

    for (const auto& pair : label_to_numbers_) {
        std::cout << "标签 \"" << pair.first << "\" 的随机数: ";
        for (const auto& num : pair.second) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

void CommandHandler::handleDelete(const std::string& label) {
    auto it = label_to_numbers_.find(label);
    if (it == label_to_numbers_.end()) {
        std::cerr << "错误: 标签 \"" << label << "\" 不存在。" << std::endl;
        return;
    }

    label_to_numbers_.erase(it);

    if (!storage_.writeAll(label_to_numbers_)) {
        std::cerr << "错误: 无法写入存储文件。" << std::endl;
        return;
    }

    std::cout << "标签 \"" << label << "\" 及其随机数记录已删除。" << std::endl;
}