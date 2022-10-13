#pragma once
#include <algorithm>
#include <string>
#include <string_view>

namespace dash {
/**
 * @brief trim all the given leading character @param ch of the @param view in place
 * */
inline std::string_view TrimPrefixAll(std::string_view view, unsigned char ch) {
    const auto pos =
        std::find_if_not(view.begin(), view.end(), [ch](const unsigned char c) { return c == ch; });
    return view.substr(static_cast<size_t>(pos - view.begin()));
}

/**
 * @brief trim all the given trailing character @param ch of the @param view in place
 * */
inline std::string_view TrimSuffixAll(std::string_view view, unsigned char ch) {
    auto it = std::find_if_not(view.rbegin(), view.rend(),
                               [ch](const unsigned char c) { return c == ch; });
    return view.substr(0, static_cast<size_t>(view.rend() - it));
}

/**
 * @brief trim all the given leading character @param ch of the @param str in place
 * */
inline void TrimPrefixAll(std::string* str, unsigned char ch) {
    const auto pos =
        std::find_if_not(str->begin(), str->end(), [ch](const unsigned char c) { return c == ch; });
    str->erase(str->begin(), pos);
}

/**
 * @brief trim all the given trailing character @param ch of the @param str in place
 * */
inline void TrimSuffixAll(std::string* str, unsigned char ch) {
    auto it = std::find_if_not(str->rbegin(), str->rend(),
                               [ch](const unsigned char c) { return c == ch; });
    str->erase(static_cast<size_t>(str->rend() - it));
}

/**
 * @brief to check if the string @param s is an integer.
 * */
bool IsInteger(const std::string& s);
}  // namespace dash