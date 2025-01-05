#include "Storage.h"
#include <fstream>
#include <iostream>

Storage::Storage(const std::string& filename) : filename_(filename) {}

bool Storage::read(std::map<std::string, std::set<int>>& label_to_numbers, std::string& last_label) {
    std::ifstream infile(filename_);
    if (!infile.is_open()) {
        // 文件不存在时，不视为错误，返回空映射
        return true;
    }

    std::string label;
    int num;
    while (infile >> label >> num) {
        label_to_numbers[label].insert(num);
        last_label = label; // 更新最后一个标签
    }

    infile.close();
    return true;
}

bool Storage::append(const std::string& label, const std::set<int>& numbers) {
    std::ofstream outfile(filename_, std::ios::app);
    if (!outfile.is_open()) {
        return false;
    }

    for (const auto& num : numbers) {
        outfile << label << " " << num << "\n";
    }

    outfile.close();
    return true;
}

bool Storage::writeAll(const std::map<std::string, std::set<int>>& label_to_numbers) {
    std::ofstream outfile(filename_, std::ios::trunc);
    if (!outfile.is_open()) {
        return false;
    }

    for (const auto& pair : label_to_numbers) {
        for (const auto& num : pair.second) {
            outfile << pair.first << " " << num << "\n";
        }
    }

    outfile.close();
    return true;
}