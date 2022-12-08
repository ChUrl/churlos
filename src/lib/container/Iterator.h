#ifndef Iterator_Include_H_
#define Iterator_Include_H_

namespace Container {

/**
 * This class implements an iterator that works on continuous memory regions
 * of uniform type.
 *
 * @tparam T The type of the elements contained in the memory region
 */
template<typename T>
class ContinuousIterator {
public:
    ContinuousIterator() = delete;

    // Use const_cast as the iterator has to increment the pointer
    // Don't make this explicit: Want to write Container::Vector<int>::iterator = nullptr;
    ContinuousIterator(const T *ptr) : ptr(const_cast<T *>(ptr)) {} // NOLINT(google-explicit-constructor)

    ~ContinuousIterator() = default;

    ContinuousIterator &operator++() {
        ++ptr;
        return *this;
    }

    ContinuousIterator &operator--() {
        --ptr;
        return *this;
    }

    ContinuousIterator operator+(unsigned int add) {
        return ContinuousIterator(ptr + add);
    }

    ContinuousIterator operator-(unsigned int sub) {
        return ContinuousIterator(ptr - sub);
    }

    // Convenience operators
    T *operator->() { return ptr; }

    const T *operator->() const { return ptr; }

    T &operator*() { return *ptr; }

    const T &operator*() const { return *ptr; }

    bool operator<(const ContinuousIterator &other) const { return ptr < other.ptr; }

    bool operator<=(const ContinuousIterator &other) const { return ptr <= other.ptr; }

    bool operator>(const ContinuousIterator &other) const { return ptr > other.ptr; }

    bool operator>=(const ContinuousIterator &other) const { return ptr >= other.ptr; }

    bool operator==(const ContinuousIterator &other) const { return ptr == other.ptr; }

    bool operator!=(const ContinuousIterator &other) const { return ptr != other.ptr; }

    // Convenience function
    template<typename t>
    friend unsigned int distance(const ContinuousIterator<t> &first, const ContinuousIterator<t> &last);

private:
    T *ptr = nullptr;
};

template<typename T>
unsigned int distance(const ContinuousIterator<T> &first, const ContinuousIterator<T> &last) {
    return last.ptr - first.ptr;
}

}  // namespace bse

#endif
