#include "parser.h"

#include <iostream>
#include <fstream>

Options::Options(int argc, const char **argv) {

    std::ifstream config_file("../config.txt");

    std::string word;
    std::string name;
    Option option;

    while (!config_file.eof()) {
        config_file >> word;
        if (word[word.size() - 1] == ':') {
            name = word.substr(0, word.size() - 1);
            option = {};
            p1.insert(map_str_option::value_type(name, option));
        } else if (word == "!") {
            p1[name].important = true;
        } else if (word[0] == '-') {
            p1[name].names.insert(word);
        } else {
            p1[name].type_name = word;
        }
    }

    std::string name_type;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            name = getNameByOpt(argv[i]);

            if (p1[name].type_name == "bool") {
                p2.insert(map_str_vector::value_type(name, true));
                name = "other";
            }
        } else if (p1[name].type_name == "string") {
            p2.insert(map_str_vector::value_type(name, std::string(argv[i])));
            name = "other";
        } else if (p1[name].type_name == "stringList") {
            if (p2.find(name) == p2.end()) {
                p2.insert(map_str_vector::value_type(name, std::vector<std::string>{argv[i]}));
            } else {
                std::get<std::vector<std::string>>(p2[name]).emplace_back(argv[i]);
            }
        } else {
            auto d = 0;

            if (p1[name].type_name == "short") {
                d = static_cast<short>(std::strtol(argv[i], nullptr, 10));
            } else if (p1[name].type_name == "uint64_t") {
                d = static_cast<uint64_t>(std::strtol(argv[i], nullptr, 10));
            } else {
                d = static_cast<int>(std::strtol(argv[i], nullptr, 10));
            }
            p2.insert(map_str_vector::value_type(name, d));
            name = "other";
        }
    }

    for (std::pair<std::string, Option> i: p1) {
        if (i.second.important && (p2.find(i.first) == p2.end())) {
            std::cout << i.first << " is must arg" << std::endl;
            exit(2022);
        }
    }
}

std::string Options::getNameByOpt(const std::string &opt) {
    for (std::pair<std::string, Options::Option> i: p1) {
        for (const std::string &y: i.second.names) {
            if (y == opt) {
                return i.first;
            }
        }
    }

    return "";
}

Options::types Options::getCheck(const std::string &name) {
    if (p2.find(name) == p2.end()) {
        return false;
    } else {
        return p2[name];
    }
}

int Options::getInt(const std::string &name) {
    return std::get<int>(getCheck(name));
}

short Options::getShort(const std::string &name) {
    return std::get<short>(getCheck(name));
}

uint64_t Options::getUint64_t(const std::string &name) {
    return std::get<uint64_t>(getCheck(name));
}

bool Options::getBool(const std::string &name) {
    return std::get<bool>(getCheck(name));
}

std::string Options::getString(const std::string &name) {
    return std::get<std::string>(getCheck(name));
}

std::vector<std::string> Options::getStringList(const std::string &name) {
    return std::get<std::vector<std::string>>(getCheck(name));
}

void Options::set(const std::string &name, int val) {
    if (p2.find(name) != p2.end()) {
        p2[name] = std::to_string(val);
    }
}

void Options::set(const std::string &name, std::string val) {
    if (p2.find(name) != p2.end()) {
        p2[name] = val;
    }
}

void Options::set(const std::string &name, short val) {
    if (p2.find(name) != p2.end()) {
        p2[name] = val;
    }
}

void Options::set(const std::string &name, uint64_t val) {
    if (p2.find(name) != p2.end()) {
        p2[name] = val;
    }
}

void Options::set(const std::string &name, bool val) {
    if (p2.find(name) != p2.end()) {
        p2[name] = val;
    }
}

void Options::set(const std::string &name, std::vector<std::string> val) {
    if (p2.find(name) != p2.end()) {
        p2[name] = val;
    }
}
