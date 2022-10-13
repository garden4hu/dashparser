#pragma once

#include <string>
#include <optional>

namespace dash {
bool IsAbsoluteURL(const std::string& url);
std::string UrlJoin(const std::string& first, const std::string& second);



/**
 * @brief it will parse the string look like "1:1" in to a tuple.
 * @return an optional value. If has value, the first is numerator,
 * and the second is denominator.
 * */
std::optional<std::tuple<int,int>> ParseRatioString(const std::string& ratio);



}  // namespace dash