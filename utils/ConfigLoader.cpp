#include "ConfigLoader.hpp"
#include "Logger.hpp"  // Optional: your logger
#include <fstream>
#include <stdexcept>

void ConfigLoader::load(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        Logger::get()->error("Configuration file not found: {}", path);
        throw std::runtime_error("Configuration file not found: " + path);
    }

    try {
        file >> configData;
        Logger::get()->info("Loaded config from {}", path);
    } catch (const nlohmann::json::parse_error& e) {
        Logger::get()->error("JSON parsing error: {}", e.what());
        throw std::runtime_error("Invalid JSON format in " + path);
    }
}

std::string ConfigLoader::get(const std::string& key) {
    if (configData.contains(key)) {
        return configData[key];
    }
    Logger::get()->warn("Key '{}' not found in config", key);
    return "";
}