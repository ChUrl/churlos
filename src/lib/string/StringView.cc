#include "StringView.h"

namespace String {

StringView StringView::substring(std::size_t first, std::size_t last) const {
    if (first < 0 || first > len || last <= first || last > len) {
        return nullptr;
    }

    StringView new_view;
    new_view.len = last - first;
    new_view.buf = &buf[first];
    return new_view;
}

}