cmake_minimum_required(VERSION 3.28)
project(quant-dev)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/opt/homebrew/include)
include_directories(/opt/homebrew/opt/sqlite/include)

# Link libraries dynamically
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpr REQUIRED)
find_library(SQLITE3_LIBRARY sqlite3 PATHS /opt/homebrew/lib REQUIRED)
find_library(QUANTLIB_LIBRARY QuantLib PATHS /opt/homebrew/lib REQUIRED)

# Source files
add_executable(quant-dev
        main.cpp
        src/QuantLibToolKit.cpp
        include/TradeCalendarSchedule.hpp
        src/TradeCalendarSchedule.cpp
        include/Trade.hpp
        include/TradeRepository.hpp
        src/TradeRepository.cpp
        utils/ConfigLoader.hpp
        utils/ConfigLoader.cpp
        utils/Logger.cpp
)

# Link libraries
target_link_libraries(quant-dev
        ${SQLITE3_LIBRARY}
        ${QUANTLIB_LIBRARY}
        cpr::cpr
        nlohmann_json::nlohmann_json
        fmt::fmt
        spdlog::spdlog
)