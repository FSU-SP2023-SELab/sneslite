#ifndef SNESLITE_LOGGING_H
#define SNESLITE_LOGGING_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <streambuf>
#include <vector>
#include <cstring>

namespace sneslite {
    //Available logging levels
    enum LogLevel {
        None,
        Error,
        Info,
        CpuTrace
    };

    //Logger class for managing logging
    class Logger {
    public:
        Logger();
        ~Logger();

        Logger& setLogStream(std::ostream& stream);
        Logger& setCpuTraceStream(std::ostream& stream);
        Logger& setLogLevel(LogLevel level);

        LogLevel getLogLevel() const;
        std::ostream& getLogStream() const;
        std::ostream& getCpuTraceStream() const;

        static Logger& instance();

    private:
        LogLevel _level;
        std::ostream* logStream;
        std::ostream* cpuTrace;
    };

}

//Macros for logging and CPU tracing
#define LOG(level) \
    if (level > sneslite::Logger::instance().getLogLevel()); \
    else sneslite::Logger::instance().getLogStream() << '[' << __FILE__ << ":" << std::dec << __LINE__ << "] "

#define LOG_CPU \
    if (sneslite::LogLevel::CpuTrace != sneslite::Logger::instance().getLogLevel()); \
    else sneslite::Logger::instance().getCpuTraceStream()

#endif // SNESLITE_LOGGING_H
