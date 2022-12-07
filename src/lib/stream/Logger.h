#ifndef Logger_Include_H_
#define Logger_Include_H_

#include "OutStream.h"
#include "device/graphics/CGA.h"
#include "lib/async/SpinLock.h"
#include "lib/string/String.h"
#include "lib/string/StringView.h"

class Logger : public OutStream {
    friend class NamedLogger;  // Allow NamedLogger to lock/unlock

public:
    static Logger &instance() {
        static Logger log;
        return log;
    }

private:
    Logger() = default;

    static bool serial_enabled;

    void log(String::string_view message, Device::CGA::color col) const;

    Async::SpinLock sem;              // Semaphore would be a cyclic include, also there is just one logger...
    static void lock() { Logger::instance().sem.acquire(); }

    static void unlock() { Logger::instance().sem.release(); }

public:
//    ~Logger() override = default;

    Logger(const Logger &copy) = delete;

    void operator=(const Logger &copy) = delete;

    enum LogLevel {
        TRACE,
        DEBUG,
        ERROR,
        INFO
    };
    static LogLevel level;
    LogLevel current_message_level = Logger::INFO;  // Use this to log with manipulators

    void flush() override;

    void trace(String::string_view message) const;

    void debug(String::string_view message) const;

    void error(String::string_view message) const;

    void info(String::string_view message) const;

    // TODO: Make lvl change accessible over menu
    static void set_level(LogLevel lvl) {
        Logger::level = lvl;
    }

    static String::string_view level_to_string(LogLevel lvl) {
        switch (lvl) {
            case Logger::TRACE:
                return "TRC";
            case Logger::DEBUG:
                return "DBG";
            case Logger::ERROR:
                return "ERR";
            case Logger::INFO:
                return "INF";
        }
    }

    static void enable_serial() {
        Logger::serial_enabled = true;
    }

    static void disable_serial() {
        Logger::serial_enabled = false;
    }
};

// Manipulatoren
Logger &TRACE(Logger &log);

Logger &DEBUG(Logger &log);

Logger &ERROR(Logger &log);

Logger &INFO(Logger &log);

class NamedLogger {
private:
    const char *name;

public:
    explicit NamedLogger(const char *name) : name(name) {}

    Logger &trace() {
        Logger::lock();
        return Logger::instance() << TRACE << name << " :: ";
    }

    Logger &debug() {
        Logger::lock();
        return Logger::instance() << DEBUG << name << " :: ";
    }

    Logger &error() {
        Logger::lock();
        return Logger::instance() << ERROR << name << " :: ";
    }

    Logger &info() {
        Logger::lock();
        return Logger::instance() << INFO << name << " :: ";
    }
};

#endif
