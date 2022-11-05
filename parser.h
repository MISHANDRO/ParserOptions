#pragma once

#include <set>
#include <string>
#include <map>
#include <vector>
#include <variant>

struct Options {

private:

    struct Option {
        bool important = false;
        std::set<std::string> names;
        std::string type_name = "list_string";
    };

    typedef std::variant<
            std::vector<std::string>, std::string, bool,
            short, int, long, long long,
            uint8_t, uint16_t, uint32_t, uint64_t> types;
    typedef std::map <std::string, Option> map_str_option;
    typedef std::map <std::string, types> map_str_vector;

    map_str_option p1;
    map_str_vector p2;

public:
    Options(int argc, const char **argv);

    std::string getNameByOpt(const std::string &opt);

    types getCheck(const std::string &name);

    int getInt(const std::string &name);
    short getShort(const std::string &name);
    uint64_t getUint64_t(const std::string &name);
    bool getBool(const std::string &name);
    std::string getString(const std::string &name);
    std::vector <std::string> getStringList(const std::string &name);

    void set(const std::string &name, std::string val);
    void set(const std::string &name, int val);
    void set(const std::string &name, short val);
    void set(const std::string &name, uint64_t val);
    void set(const std::string &name, bool val);
    void set(const std::string &name, std::vector<std::string> val);
};
