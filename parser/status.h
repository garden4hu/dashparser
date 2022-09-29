#pragma once

namespace dash {
enum class StatusCode : int {
    kOk     = 0,
    kFailed = 0x1000,
    kErrorInvalidMPD = 0x1001,
    kErrorInvalidBaseURL = 0x1002,
};
}