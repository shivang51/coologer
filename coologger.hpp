#pragma  once

#include <iostream>
#include <format>
#include <string>
#include <chrono>

namespace Coolog{
    enum class LogLevel{
        info,
        error,
        warning
    };

    namespace  Modifier {

        enum class ColorCode{
            FG_RED = 31,
            FG_GREEN = 32,
            FG_YELLOW = 33,
            FG_BLUE = 34,
            FG_DEFAULT = 39,
            BG_RED = 41,
            BG_GREEN = 42,
            BG_YELLOW = 43,
            BG_BLUE = 44,
            BG_DEFAULT = 49
        };

        const std::string red("\033[0;31m");

        std::string create(const int fgColor, const bool bold){
            return std::format("\033[{};{}m", (const int)bold, fgColor);
        }

        std::string fromLogLevel(LogLevel level, const bool bold){
            switch (level) {
                case LogLevel::error:{
                    return create((const int) ColorCode::FG_RED, bold);
                }break;
                case LogLevel::warning:{
                    return create((const int) ColorCode::FG_YELLOW, bold);
                }break;
                default:
                    return "";
                    break;
            }
        }

        std::string reset("\033[0m");
    }

    class Logger {
    public:
        Logger() = default;

        explicit Logger(const std::string& name){
            m_name = name;
        }

        template<typename... Args>
        void log(LogLevel level, const std::string_view &message, Args&&... args) {
            auto time = getCurrentTime("%a %d-%m %X");

            std::cout << Modifier::fromLogLevel(level, false);
            std::cout << "[";
            if(!m_name.empty()) std::cout << m_name << " | ";
            std::cout << time << "] ";
            std::cout << std::vformat(message, std::make_format_args(args...));
            std::cout << Modifier::reset;
        }

        template<typename... Args>
        void logln(LogLevel level, const std::string_view &message, Args&&... args) {
            log(level, message, args...);
            std::cout << std::endl;
        }


        template<typename... Args>
        void logBold(LogLevel level, const std::string_view &message, Args&&... args) {
            auto time = getCurrentTime("%a %d-%m %X");
            std::cout << Modifier::fromLogLevel(level, true);
            std::cout << "[";
            if(!m_name.empty()) std::cout << m_name << " | ";
            std::cout << time << "] ";
            std::cout << std::vformat(message, std::make_format_args(args...));
            std::cout << Modifier::reset << std::endl;
        }

        static std::string getCurrentTime(const std::string& format){
            std::time_t timer = std::time(nullptr);
            std::tm* localTime = std::localtime(&timer);
            char s[100];
            std::strftime(s, sizeof s, format.data(), localTime);
            return s;
        }

        static std::string logLevelToStr(LogLevel level){
            switch (level) {
                case LogLevel::warning:{
                    return "Warning";
                }break;
                case LogLevel::error:{
                    return "Error";
                }break;
                case LogLevel::info:{
                    return "Info";
                }break;
            }
        }

    private:
        std::string m_name;
    };


    template<typename... Args>
    void quickLog(const std::string_view &message, Args&&... args) {
        auto time = Logger::getCurrentTime("%a %d-%m %X");
        std::cout << "[";
        std::cout << Logger::logLevelToStr(LogLevel::info) << " | ";
        std::cout << time;
        std::cout << "] ";
        std::cout << std::vformat(message, std::make_format_args(args...));
        std::cout << Modifier::reset;
    }
}

