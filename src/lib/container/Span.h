#ifndef SPAN_INCLUDE_H
#define SPAN_INCLUDE_H

#include "Iterator.h"
#include <utility>

namespace Container {

/**
 * This class implements a readonly view on a memory region of uniform type.
 * The Span can be initialized wihout size checking by supplying 0 as size
 * and using the one-argument constructor. Then iterators become invalid.
 *
 * @tparam T The type of the objects located in the memory region
 * @tparam N The size of the memory region
 */
template<typename T, std::size_t N = 0>
class Span {
public:
    using iterator = ContinuousIterator<T>;

private:
    T *const ptr;
    const std::size_t sz = N;

public:
    Span() = delete;

    explicit Span(T *first) : ptr(first) {}

    Span(T *first, T *last) : ptr(first), sz(last - first) {}

    // TODO: Rest of constructors

    iterator begin() { return iterator(ptr); }

    iterator begin() const { return iterator(ptr); }

    // If size is unchecked end() is equal to begin()
    iterator end() { return iterator(&ptr[sz]); }

    // If size is unchecked end() is equal to begin()
    iterator end() const { return iterator(&ptr[sz]); }

    T *operator[](std::size_t i) {
        if (sz != 0) {
            if (i >= sz) { return nullptr; }
        }
        return &ptr[i];
    }

    T *operator[](std::size_t i) const {
        if (sz != 0) {
            if (i >= sz) { return nullptr; }
        }
        return &ptr[i];
    }

    T *data() { return ptr; }

    const T *data() const { return ptr; }

    explicit operator T *() {
        return ptr;
    }

    // First is inclusive, last exclusive [first, last)
    Span &subspan(std::size_t first, std::size_t last) {
        return Span(ptr + first, ptr + last - 1);
    }

    [[nodiscard]] std::size_t size() const {
        return sz;
    }
};

}  // namespace bse

#endif
