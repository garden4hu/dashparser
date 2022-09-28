#include "util.h"

#include <absl/strings/strip.h>

#include <iostream>

namespace dash {

bool IsAbsoluteURL(const std::string& url) {
    if (url.empty()) {
        return false;
    }
    if (url.find("://") == std::string::npos) {
        return false;
    }
    return true;
}

std::string UrlJoin(const std::string& first, const std::string& second) {
    if (!(IsAbsoluteURL(first) ^ IsAbsoluteURL(second))) {
        return "";
    }
    const std::string& base = IsAbsoluteURL(first) ? first : second;
    const std::string& leaf = IsAbsoluteURL(first) ? second : first;
    const auto result       = absl::StripSuffix(base, "/");
    std::string url(result);
    url += "/";
    if (leaf != "./") {
        url += leaf;
    }
    return url;
}

}  // namespace dash
