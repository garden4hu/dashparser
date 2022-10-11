#pragma once
#include <optional>
#include <type_traits>

/**
 * @brief It's a helper function for setting the @param dest value
 * from the optional value if the @param dest has a valid value.
 * Note: Only the type of std::string and numerical are support.
 * */

template <typename T, typename U>
void SetIfHasValue(T& dest, std::optional<U> opt) {
    if (!opt.has_value() || std::is_const_v<T>) return;
    if (std::is_same_v<T, U>) {
        dest = opt.value();
    } else if (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {
        dest = static_cast<T>(opt.value());
    } else {
        return;
    }
}