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


/** @brief trait for setting integer when the the content string @param str
 * can be converted into the optional struct of integer.
* It's an ugly implementation.
 * @note Unknown types will cause unforeseen errors
 * */
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
void SetIntegerFromString(std::optional<T>& dest, const std::string& str) {
    if (str.empty()) {
        return;
    }
    if (std::is_same_v<T, int>) {
        dest = static_cast<int>(std::stoi(str));
    } else if (std::is_same_v<T, uint32_t>) {
        dest = static_cast<uint32_t>(std::stoul(str));
    } else if (std::is_same_v<T, int64_t>) {
        dest = static_cast<int>(std::stoll(str));
    } else {
        // doing nothing
    }
}

/** @brief trait for setting integer when the the content string @param str
 * can be converted into integer.
 * It's an ugly implementation.
 * @note Unknown types will cause unforeseen errors
 * */
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
void SetIntegerFromString(T& dest, const std::string& str) {
    if (str.empty()) {
        return;
    }
    if (std::is_same_v<T, int>) {
        dest = static_cast<int>(std::stoi(str));
    } else if (std::is_same_v<T, uint32_t>) {
        dest = static_cast<uint32_t>(std::stoul(str));
    } else if (std::is_same_v<T, int64_t>) {
        dest = static_cast<int>(std::stoll(str));
    } else {
        // doing nothing
    }
}