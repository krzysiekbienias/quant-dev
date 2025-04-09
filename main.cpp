#include <cpr/cpr.h>
#include "utils/ConfigLoader.hpp"
#include <iostream>

int main() {
    try {
        ConfigLoader::load();  // default path: config.json in root
        std::string polygonKey = ConfigLoader::get("POLYGON_IO_API_KEY");
        std::cout << "Polygon API Key: " << polygonKey << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Config load failed: " << e.what() << std::endl;
    }

    return 0;
}