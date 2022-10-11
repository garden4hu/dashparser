#include "util.h"

#include <absl/strings/strip.h>

#include <iostream>

#include <absl/strings/string_view.h>
#include <absl/strings/strip.h>
#include <absl/strings/str_split.h>


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


bool IsInteger(const std::string& s) {
    bool b = true;
    absl::string_view v{s};
    if (EndsWithIgnoreCase(v, "UL")){
        v.remove_suffix(2);
    }else if (EndsWithIgnoreCase(v,"L") || EndsWithIgnoreCase(v,"U")){
        v.remove_suffix(1);
    }else {
    }
    absl::StripAsciiWhitespace(v);
    if (absl::StartsWith(v,"+") || absl::StartsWith(v,"-")){
        v.remove_prefix(1);
    }
    std::for_each(v.begin(), v.end(), [&b](unsigned char c) {
        if (!std::isdigit(c)) {
            b = false;
        }
    });
    return b;
}

}  // namespace dash
