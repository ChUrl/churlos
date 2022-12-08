#ifndef CHURLOS_RESTRICTEDCONSTRUCTORS_H
#define CHURLOS_RESTRICTEDCONSTRUCTORS_H

// Some convenience macros to easily delete copy/move constructors

#define MakeDefault(T) \
    T() = default; \
    ~T() = default;

#define MakeUncopyable(T) \
    T(const T &copy) = delete; \
    T &operator=(const T &copy) = delete;

#define MakeUnmovable(T) \
    T(T &&move) = delete;\
    T &operator=(T &&move) = delete;

#endif //CHURLOS_RESTRICTEDCONSTRUCTORS_H
