#include "Logger.h"
#include "kernel/system/Globals.h"

bool Logger::serial_enabled = false;

Logger::LogLevel Logger::level = Logger::ERROR;

constexpr const char *ansi_red = "\033[1;31m";
constexpr const char *ansi_green = "\033[1;32m";
constexpr const char *ansi_yellow = "\033[1;33m";
constexpr const char *ansi_blue = "\033[1;34m";
constexpr const char *ansi_magenta = "\033[1;35m";
constexpr const char *ansi_cyan = "\033[1;36m";
constexpr const char *ansi_white = "\033[1;37m";
constexpr const char *ansi_default = "\033[0;39m ";

void Logger::log(const String::string_view message, Device::CGA::color col) const {
    if (!Logger::serial_enabled) {
        return;
    }

    switch (col) {
        case Device::CGA::WHITE:
            Device::SerialOut::write(ansi_white);
            break;
        case Device::CGA::LIGHT_MAGENTA:
            Device::SerialOut::write(ansi_magenta);
            break;
        case Device::CGA::LIGHT_RED:
            Device::SerialOut::write(ansi_red);
            break;
        case Device::CGA::LIGHT_BLUE:
            Device::SerialOut::write(ansi_blue);
            break;
        default:
            Device::SerialOut::write(ansi_default);
    }
    Device::SerialOut::write("[");
    Device::SerialOut::write(Logger::level_to_string(current_message_level));
    Device::SerialOut::write("] ");
    Device::SerialOut::write(message);
    Device::SerialOut::write('\r');
    // serial.write("\r\n");
}

void Logger::flush() {
    buffer[pos] = '\0';

    switch (current_message_level) {
        case Logger::TRACE:
            trace(buffer.data());
            break;
        case Logger::DEBUG:
            debug(buffer.data());
            break;
        case Logger::ERROR:
            error(buffer.data());
            break;
        case Logger::INFO:
            info(buffer.data());
            break;
    }

    current_message_level = Logger::INFO;
    pos = 0;
    Logger::unlock();
}

void Logger::trace(const String::string_view message) const {
    if (Logger::level <= Logger::TRACE) {
        log(message, Device::CGA::WHITE);
    }
}

void Logger::debug(const String::string_view message) const {
    if (Logger::level <= Logger::DEBUG) {
        log(message, Device::CGA::LIGHT_MAGENTA);
    }
}

void Logger::error(const String::string_view message) const {
    if (Logger::level <= Logger::ERROR) {
        log(message, Device::CGA::LIGHT_RED);
    }
}

void Logger::info(const String::string_view message) const {
    if (Logger::level <= Logger::INFO) {
        log(message, Device::CGA::LIGHT_BLUE);
    }
}

// Manipulatoren
Logger &TRACE(Logger &log) {
    log.current_message_level = Logger::TRACE;
    return log;
}

Logger &DEBUG(Logger &log) {
    log.current_message_level = Logger::DEBUG;
    return log;
}

Logger &ERROR(Logger &log) {
    log.current_message_level = Logger::ERROR;
    return log;
}

Logger &INFO(Logger &log) {
    log.current_message_level = Logger::INFO;
    return log;
}
