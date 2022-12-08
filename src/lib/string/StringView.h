#ifndef C_OS_STRINGVIEW_H
#define C_OS_STRINGVIEW_H

#include "String.h"
#include "lib/container/Iterator.h"
#include <utility>

namespace String {

// TODO: Investigate this class

/**
 * This class implements a simple wrapper for usual string literals.
 */
class StringView {
    using iterator = Container::ContinuousIterator<char>;

public:
    StringView() = default;

    // Important that char* and string& can be implicitly converted: Only have to provide one
    // implementation using stringview for everything (OutStream only uses StringView for example)
    StringView(const char *str) : len(strlen(str)), buf(str) {} // NOLINT(google-explicit-constructor)

    StringView(const String &str) : len(str.size()), // NOLINT(google-explicit-constructor)
                                    buf(static_cast<char *>(str)) {}

    [[nodiscard]] iterator begin() const { return {buf}; }

    [[nodiscard]] iterator end() const { return {&buf[len]}; }

    explicit operator const char *() const { return buf; }

    char operator[](std::size_t pos) const { return buf[pos]; }

    bool operator==(const StringView &other) const { return buf == other.buf; }

    bool operator!=(const StringView &other) const { return buf != other.buf; }

    [[nodiscard]] std::size_t size() const { return len; }

    [[nodiscard]] StringView substring(std::size_t first, std::size_t last) const;

private:
    std::size_t len = 0;
    const char *buf = nullptr;
};

} // namespace bse

#endif //C_OS_STRINGVIEW_H
