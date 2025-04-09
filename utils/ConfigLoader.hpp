#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

class ConfigLoader {
public:
    static void load(const std::string& path = "config.json");
    static std::string get(const std::string& key);

private:
    static inline nlohmann::json configData;
};

#endif // CONFIG_LOADER_HPP