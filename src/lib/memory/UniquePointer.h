#ifndef UniquePointer_Include_H_
#define UniquePointer_Include_H_

#include <utility>
#include "lib/util/RestrictedConstructors.h"

// https://en.cppreference.com/w/cpp/memory/unique_ptr

// NOTE: Because of the way the scheduling works our functions are not executed completely.
//       This means that object destructors are not called if the objects live in a scope
//       that is left because of thread switching (e.g. a threads run function)...

namespace Memory {

// T is the type make_unique is called with, meaning int or int[] for example
// T_ is the bare type without extents (int in both cases), so we have a
// int* pointer type for both unique_ptr<int> and unique_ptr<int[]>

/**
 * This class implements a simple managed pointer with a single owner.
 *
 * @tparam T The type of object the pointer holds
 */
template<typename T>
class UniquePtr {
    using T_ = std::remove_extent_t<T>;

public:
    // Construction
    UniquePtr() = default;  // Allow declaration without explicit definition

    MakeUncopyable(UniquePtr)

    // Moving
    UniquePtr(UniquePtr &&move) noexcept { reset(move.release()); };

    // Implicit upcasting is needed: unique_ptr<Thread> ptr = make_unique<IdleThread>();
    // Not explicit for the same reason
    template<typename t>
    UniquePtr(UniquePtr<t> &&move) noexcept { // NOLINT(google-explicit-constructor)
        static_assert(std::is_base_of_v<T, t>, "Has to be derived type");
        reset(move.release());
    }

    UniquePtr &operator=(UniquePtr &&move) noexcept {
        reset(move.release());
        return *this;
    }

    ~UniquePtr() {
        del();
    }

    // Utility construction
    template<typename t, typename... Args>
    friend typename std::enable_if_t<!std::is_array_v<t>, UniquePtr<t>>
    make_unique(Args &&... args);

    template<typename t>
    friend typename std::enable_if_t<std::is_array_v<t>, UniquePtr<t>>
    make_unique(std::size_t size);

    /**
     * Delete the contained object and reset the pointer.
     */
    void reset() { del(); }

    /**
     * Delete the contained object and reset the pointer to a new pointer.
     *
     * @param pt The new pointer stored in the unique pointer
     */
    void reset(T_ *pt) {
        del();
        ptr = pt;
    }

    /**
     * Release the contained object without deleting it.
     *
     * @return The contained pointer
     */
    T_ *release() {
        // T* old = ptr;
        // ptr = nullptr;
        // return old;
        return std::exchange(ptr, nullptr);
    }

    /**
     * Get a pointer to the contained object without taking ownership.
     *
     * @return The contained pointer
     */
    T_ *get() const {
        return ptr;
    }

    // Pointer operators
    T_ *operator->() { return ptr; }

    const T_ *operator->() const { return ptr; }

    T_ &operator*() { return *ptr; }

    const T_ &operator*() const { return *ptr; }

    explicit operator void *() const { return ptr; }

    explicit operator bool() const { return (ptr != nullptr); }

    bool operator==(const UniquePtr &other) const { return ptr == other.ptr; }

    // These are only for array unique_ptr but I didn't enforce that
    T_ &operator[](std::size_t i) { return ptr[i]; }

    const T_ &operator[](std::size_t i) const { return ptr[i]; }

private:
    T_ *ptr = nullptr;

private:
    // Only use make_unique or reset for construction
    // Not explicit to allow assigning nullptr: UniquePtr<IdleThread> ptr = nullptr;
    UniquePtr(T_ *ptr) : ptr(ptr) {} // NOLINT(google-explicit-constructor)

    // I didn't want to introduce custom deleters for my small needs
    void del() {
        if constexpr (std::is_array_v<T>) {
            delete[] ptr;
        } else {
            delete ptr;
        }
        ptr = nullptr;
    }

};

// make_unique implementation =======================================

// Allow initialization of unique_ptr<int> with optional constructor arguments
// and unique_ptr<int[]> without constructor arguments
template<typename T, typename... Args>

// We make the return type dependent on whether T is an array type or not
typename std::enable_if_t<!std::is_array_v<T>, UniquePtr<T>>
make_unique(Args &&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
typename std::enable_if_t<std::is_array_v<T>, UniquePtr<T>>
make_unique(std::size_t size) {
    using T_ = typename std::remove_extent_t<T>;
    return UniquePtr<T>(new T_[size]);
}

}  // namespace bse

#endif
