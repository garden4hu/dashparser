#pragma once
#include <string>
#include <absl/strings/string_view.h>
#include <absl/strings/strip.h>

namespace dash {
bool IsAbsoluteURL(const std::string& url);
std::string UrlJoin(const std::string& first, const std::string& second);
}