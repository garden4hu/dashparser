#pragma once

#include <string>
#include <optional>

namespace dash {
bool IsAbsoluteURL(const std::string& url);
std::string UrlJoin(const std::string& first, const std::string& second);



bool IsInteger(const std::string& s);



}  // namespace dash