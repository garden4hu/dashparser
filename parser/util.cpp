#include "util.h"

#include <absl/strings/str_split.h>
#include <absl/strings/string_view.h>
#include <absl/strings/strip.h>

#include <iostream>
#include <strng>

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

std::optional<std::tuple<int,int>> ParseRatioString(const std::string& ratio){
    if (ratio.empty()){
        return std::nullopt;
    }
    auto pos = ratio.find(':');
    if (pos == std::string::npos){
        return std::nullopt;
    }
    auto num_str = ratio.substr(0,pos);
    auto denomi_str  = ratio.substr(pos);
    if (!num_str.empty() && !denomi_str.empty()){
        int numerator = std::stoi(num_str);
        int denominator = std::stoi(denomi_str);
            return std::make_tuple(numerator,denominator);
    }
    return  std::nullopt;
}
}  // namespace dash
