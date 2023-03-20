#ifndef SNESLITE_LOGGING_H
#define SNESLITE_LOGGING_H

#pragma once

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

#endif // SNESLITE_LOGGING_H
