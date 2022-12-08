#ifndef SPAN_INCLUDE_H
#define SPAN_INCLUDE_H

#include "Iterator.h"
#include <utility>

namespace Container {

/**
 * This class implements a view on a continuous memory region of uniform type
 * with runtime bounds checking and iterator support.
 *
 * @tparam T The type of the objects located in the memory region
 * @tparam N The size of the memory region
 */
template<typename T, std::size_t N>
class Span {
    static_assert(N > 0, "Invalid size!");

public:
    using iterator = ContinuousIterator<T>;

public:
    Span() = delete;

    // Don't mark explicit to allow Span<uint32_t, 32> span = &int;
    Span(T *first) : ptr(first) {}

    // TODO: Rest of constructors

    iterator begin() { return iterator(ptr); }

    iterator end() { return iterator(&ptr[N]); }

    T *operator[](std::size_t i) const {
        if (i >= N) {
            // TODO: Exception
        }
        return &ptr[i];
    }

    T *data() const { return ptr; }

    explicit operator T *() const { return ptr; }

    // First is inclusive, last exclusive [first, last)
    template<std::size_t Offset, std::size_t Count>
    Span &subspan() const {
        static_assert(Offset + Count <= N, "Ivalid range!");

        return Span<T, Count>(ptr + Offset);
    }

    [[nodiscard]] constexpr std::size_t size() const {
        return N;
    }

private:
    T *const ptr;
};

}  // namespace bse

#endif
