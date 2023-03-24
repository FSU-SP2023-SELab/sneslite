#include "Logger.hpp"

namespace sneslite {

    Logger::Logger() : _level(LogLevel::Info), logStream(&std::clog), cpuTrace(nullptr) {}

    Logger::~Logger() {}

    Logger& Logger::setLogStream(std::ostream& stream) {
        logStream = &stream;
        return *this;
    }

    Logger& Logger::setCpuTraceStream(std::ostream& stream) {
        cpuTrace = &stream;
        return *this;
    }

    Logger& Logger::setLogLevel(LogLevel level) {
        _level = level;
        return *this;
    }

    LogLevel Logger::getLogLevel() const {
        return _level;
    }

    std::ostream& Logger::getLogStream() const {
        return *logStream;
    }

    std::ostream& Logger::getCpuTraceStream() const {
        if (cpuTrace) {
            return *cpuTrace;
        }
        return *logStream;
    }

    Logger& Logger::instance() {
        static Logger logger;
        return logger;
    }

    //Stream buffer class to separate buffers into two
    class Logger::DualStreamBuffer : public std::streambuf {
    public:
        DualStreamBuffer(std::streambuf* buf1, std::streambuf* buf2) : buf1(buf1), buf2(buf2) {}

        int overflow(int c) override {
            int r1 = buf1->sputc(c);
            int r2 = buf2->sputc(c);
            return (r1 == EOF || r2 == EOF) ? EOF : c;
        }

        int sync() override {
        int r1 = buf1->pubsync();
        int r2 = buf2->pubsync();
        return (r1 == 0 && r2 == 0) ? 0 : -1;
        }   

    private:
        std::streambuf* buf1;
        std::streambuf* buf2;
    };

    class Logger::DualOstream : public std::ostream {
    public:
        DualOstream(std::ostream& os1, std::ostream& os2) : std::ostream(&buf), buf(os1.rdbuf(), os2.rdbuf()) {}

    private:
        DualStreamBuffer buf;
    };


}
