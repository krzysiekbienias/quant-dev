#include "Logger.hpp"
#include <filesystem>

std::shared_ptr<spdlog::logger> Logger::logger = nullptr;

std::shared_ptr<spdlog::logger>& Logger::get() {
    if (!logger) {
        std::string log_dir = "/Users/krzysztofbienias/Documents/logs";
        std::filesystem::create_directories(log_dir);
        std::string log_file = log_dir + "/numeraire_cpp.log";

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            log_file, 1024 * 1024, 5);
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        file_sink->set_level(spdlog::level::debug);
        console_sink->set_level(spdlog::level::info);

        logger = std::make_shared<spdlog::logger>("numeraire_cpp_logger",
                                                  spdlog::sinks_init_list{file_sink, console_sink});

        logger->set_level(spdlog::level::debug);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
        spdlog::register_logger(logger);
    }
    return logger;
}