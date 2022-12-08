#ifndef ARRAY_INCLUDE_H
#define ARRAY_INCLUDE_H

#include "Iterator.h"
#include <utility>

namespace Container {

/**
 * This class implements a stack allocated array with runtime bounds checking
 * and iterator support.
 *
 * @tparam T The type of the held objects
 * @tparam N The number of elements the array can store
 */
template<typename T, const std::size_t N>
class Array {
    static_assert(N > 0, "Invalid size!");

public:
    using iterator = ContinuousIterator<T>;

public:
    Array() = default;  // If i write default something like Container::Array<int, 10> arr; is not initialized...

    // Construct like this: bse::array<int, 5> arr = {1, 2, 3, 4, 5};
    /**
     * Initialize the Array with initial values provided by an initializer list.
     * If the initializer list has a smaller size than the Array the last value
     * will be repeated.
     *
     * @param list The initial values
     */
    Array(std::initializer_list<T> list) {
        // TODO: Exception on wrong size? Can't static_assert on list.size()
        typename std::initializer_list<T>::iterator it = list.begin();
        typename std::initializer_list<T>::iterator end = list.end();

        for (unsigned int i = 0; i < N; ++i) {
            buf[i] = *it;
            if (it < end - 1) {
                // Repeat the last initializer_list element
                // if the array has more slots than initial values are provided
                ++it;
            }
        }
    }

    ~Array() = default;

    iterator begin() { return iterator(&buf[0]); }

    iterator begin() const { return iterator(&buf[0]); }

    iterator end() { return iterator(&buf[N]); }

    iterator end() const { return iterator(&buf[N]); }

    constexpr T &operator[](std::size_t i) {
        if (i >= N) {
            // TODO: Exception
        }

        return buf[i];
    }

    constexpr const T &operator[](std::size_t i) const {
        if (i >= N) {
            // TODO: Exception
        }

        return buf[i];
    }

    /**
     * Get a pointer to the stack allocated memory.
     *
     * @return The pointer to the stack allocated memory
     */
    T *data() { return &buf[0]; }

    const T *data() const { return &buf[0]; }

    /**
     * Swap the content of two arrays of the same size.
     *
     * @param other The array to swap with
     */
    void swap(Array<T, N> &other) {
        for (std::size_t i = 0; i < N; ++i) {
            std::swap(buf[i], other[i]);
        }
    }

    // Array& other has to have size n:
    // arr1.swap_n<5>(arr2) => arr2 has size 5, arr1 has size >= 5
    /**
     * Swap the contents of two arrays with different size.
     *
     * @tparam n The number of elements to swap
     * @param other The array to swap with
     */
    template<std::size_t n>
    void swap_n(Array<T, n> &other) {
        static_assert(n <= N && n <= other.size(), "Invalid size!");

        for (std::size_t i = 0; i < n; ++i) {
            std::swap(buf[i], other[i]);
        }
    }

    [[nodiscard]] constexpr std::size_t size() const {
        return N;
    }

private:
    T buf[N];
};

}  // namespace Container

#endif
