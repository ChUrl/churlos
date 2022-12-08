#ifndef ARRAY_INCLUDE_H
#define ARRAY_INCLUDE_H

#include "Iterator.h"
#include <utility>

namespace Container {

/**
 * This class implements a stack allocated array with bounds checking
 * and iterator support.
 *
 * @tparam T The type of the objects
 * @tparam N The number of elements the array can store
 */
template<typename T, const std::size_t N>
class Array {
public:
    using iterator = ContinuousIterator<T>;

private:
    T buf[N];

public:
    Array() = default;  // If i write default something like Container::Array<int, 10> arr; is not initialized...

    // TODO: This doesn't account for initializer lists of the wrong length, last value should be repeated
    //       Only increment iterator when it < list.end() - 1?
    // Construct like this: bse::array<int, 5> {1, 2, 3, 4, 5};
    Array(std::initializer_list<T> list) {
        typename std::initializer_list<T>::iterator it = list.begin();
        for (unsigned int i = 0; i < N; ++i) {
            buf[i] = *it;
            ++it;
        }
    }

    // TODO: Rest of constructors

    iterator begin() { return iterator(&buf[0]); }

    iterator begin() const { return iterator(&buf[0]); }

    iterator end() { return iterator(&buf[N]); }

    iterator end() const { return iterator(&buf[N]); }

    constexpr T &operator[](std::size_t i) { return buf[i]; }

    constexpr const T &operator[](std::size_t i) const { return buf[i]; }

    T *data() { return &buf[0]; }

    const T *data() const { return &buf[0]; }

    void swap(Array<T, N> &other) {
        for (std::size_t i = 0; i < N; ++i) {
            std::swap(buf[i], other[i]);
        }
    }

    // Array& other has to have size n:
    // arr1.swap_n<5>(arr2) => arr2 has size 5, arr1 has size >= 5
    template<std::size_t n>
    void swap_n(Array<T, n> &other) {
        for (std::size_t i = 0; i < n; ++i) {
            std::swap(buf[i], other[i]);
        }
    }

    [[nodiscard]] constexpr std::size_t size() const {
        return N;
    }
};

}  // namespace Container

#endif
