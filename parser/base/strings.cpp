//
// Created by hu_peili on 2022/10/12.
//

#include "strings.h"

#include <absl/strings/match.h>
#include <absl/strings/strip.h>

namespace dash {
bool IsInteger(const std::string& s) {
    bool b = true;
    absl::string_view v{s};
    if (EndsWithIgnoreCase(v, "UL")) {
        v.remove_suffix(2);
    } else if (EndsWithIgnoreCase(v, "L") || EndsWithIgnoreCase(v, "U")) {
        v.remove_suffix(1);
    } else if (EndsWithIgnoreCase(v, "ULL")) {
        v.remove_suffix(3);
    } else {
    }
    absl::StripAsciiWhitespace(v);
    if (absl::StartsWith(v, "+") || absl::StartsWith(v, "-")) {
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