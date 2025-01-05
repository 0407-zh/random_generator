#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <map>
#include <set>

class Storage {
public:
    Storage(const std::string& filename);
    bool read(std::map<std::string, std::set<int>>& label_to_numbers, std::string& last_label);
    bool append(const std::string& label, const std::set<int>& numbers);
    bool writeAll(const std::map<std::string, std::set<int>>& label_to_numbers);
private:
    std::string filename_;
};

#endif // STORAGE_H