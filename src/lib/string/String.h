#ifndef String_Include_H_
#define String_Include_H_

#include "lib/container/Array.h"
#include "lib/container/Iterator.h"

namespace String {

// Utility functions
unsigned int strlen(const char *str);

void strncpy(char *destination, unsigned int n, const char *source);

int strcmp(const char *a, const char *b);

/**
 * This class implements a simple heap allocated string.
 */
class String {
    using iterator = Container::ContinuousIterator<char>;

public:
    String() = default;

    /**
     * Constructor. Implicitly convert string literal to dynamic string.
     *
     * @param str The string literal to convert
     */
    String(const char *str) : len(strlen(str)), buf(new char[len + 1]) { // NOLINT(google-explicit-constructor)
        strncpy(buf, len + 1, str);
    }

    /**
     * Constructor. Convert a char array to a dynamic string.
     *
     * @tparam N The size of the char array
     * @param arr The char array
     */
    template<std::size_t N>
    explicit String(const Container::Array<char, N> &arr) : len(N), buf(new char[len + 1]) {
        for (std::size_t i = 0; i < N; ++i) {
            buf[i] = arr[i];
        }
        buf[N] = '\0';
    }

    String(const String &copy) : len(copy.len), buf(new char[len + 1]) {
        strncpy(buf, len + 1, copy.buf);
    }

    String &operator=(const String &copy) {
        if (&copy != this) {
            len = copy.len;
            buf = new char[len + 1];
            strncpy(buf, len + 1, copy.buf);
        }

        return *this;
    }

    String(String &&move) noexcept: len(move.len), buf(move.buf) {
        move.len = 0;
        move.buf = nullptr;
    }

    String &operator=(String &&move) noexcept {
        if (&move != this) {
            len = move.len;
            buf = move.buf;

            move.len = 0;
            move.buf = nullptr;
        }

        return *this;
    }

    ~String() {
        delete[] buf;
    }

    iterator begin() { return {buf}; }

    [[nodiscard]] iterator begin() const { return {buf}; }

    iterator end() { return {&buf[len]}; }

    [[nodiscard]] iterator end() const { return {&buf[len]}; }

    explicit operator char *() { return buf; }

    explicit operator char *() const { return buf; }

    char operator[](std::size_t pos) { return buf[pos]; }

    char operator[](std::size_t pos) const { return buf[pos]; }

    String operator+(const String &other) const {
        String new_str;
        new_str.len = len + other.len;
        new_str.buf = new char[new_str.len + 1];

        strncpy(new_str.buf, len, buf);                        // Copy this content
        strncpy(&new_str.buf[len], other.len + 1, other.buf);  // Copy other content

        return new_str;
    }

    String operator+(const char *other) const {
        std::size_t other_len = strlen(other);

        String new_str;
        new_str.len = len + other_len;
        new_str.buf = new char[new_str.len + 1];

        strncpy(new_str.buf, len, buf);
        strncpy(&new_str.buf[len], other_len + 1, other);

        return new_str;
    }

    String &operator+=(const String &other) {
        unsigned int new_len = len + other.size();
        char *new_buf = new char[new_len + 1];

        strncpy(new_buf, len, buf);
        strncpy(&new_buf[len], other.size() + 1, other.buf);

        delete[] buf;
        buf = new_buf;
        len = new_len;

        return *this;
    }

    String &operator+=(const char *other) {
        unsigned int other_len = strlen(other);
        unsigned int new_len = len + other_len;
        char *new_buf = new char[new_len + 1];

        strncpy(new_buf, len, buf);
        strncpy(&new_buf[len], other_len + 1, other);

        delete[] buf;
        buf = new_buf;
        len = new_len;

        return *this;
    }

    String operator*(unsigned int n) const {
        String new_str;
        new_str.len = len * n;
        new_str.buf = new char[new_str.len];

        for (unsigned int i = 0; i < n; ++i) {
            strncpy(&new_str.buf[i * len], len, buf);
        }

        return new_str;
    }

    String &operator*=(unsigned int n) {
        unsigned int new_len = len * n;
        char *new_buf = new char[new_len];

        for (unsigned int i = 0; i < n; ++i) {
            strncpy(&new_buf[i * len], len, buf);
        }

        delete[] buf;
        buf = new_buf;
        len = new_len;
        return *this;
    }

    bool operator==(const String &other) const {
        return strcmp(buf, other.buf) == 0;
    }

    bool operator!=(const String &other) const {
        return strcmp(buf, other.buf) != 0;
    }

    [[nodiscard]] std::size_t size() const {
        return len;
    }

private:
    std::size_t len = 0;
    char *buf = nullptr;
};

}  // namespace bse

#endif
