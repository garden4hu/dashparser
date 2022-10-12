//
// Created by hu_pe on 2022/10/10.
//

#include "dash_time.h"

#include <absl/strings/numbers.h>

#include <algorithm>
#include <set>
#include <sstream>

#include "prtime.h"

namespace {
std::optional<int> ParseNumberFromPrefix(std::string& str) {}
}  // namespace

namespace dash {

#define SetBit(x, y)   x |= (1 << y)

#define ClrBit(x, y)   x &= ~(1 << y)

#define CheckBit(x, y) ((x >> y) & 1)

std::optional<uint32_t> ParseDurationString(const std::string& duration) {
    std::string_view delta(duration);
    int i = -1;
    do {
        while (++i < delta.length()) {
            if (delta[i] != ' ') {
                break;
            }
        }
        delta = delta.substr(i);
        if (delta.length() < 2) {
            break;
        }
        i = 0;
        if (delta[i] != 'P' && delta[i] != 'p') {
            break;
        }

        auto tag_T = delta.find('T');

        std::string date_duration;
        std::string time_duration;
        if (tag_T == std::string::npos) {
            date_duration = delta.substr(1);
        } else {
            if (tag_T - 1 > 0) {
                date_duration = delta.substr(1, tag_T - 1);
            }
            time_duration = delta.substr(tag_T);
        }

        int y           = 0;
        int mon         = 0;
        int d           = 0;
        int h           = 0;
        int min         = 0;
        int ms      = 0;

        // process the first half: xxYxxMxxD
        if (!date_duration.empty()){
            std::transform(date_duration.begin(), date_duration.end(), date_duration.begin(),
                           [](unsigned char c) { return std::toupper(c); });
            // process year
            auto y_pos = date_duration.find_first_of('Y');
            if (y_pos != std::string::npos) {
                int year = 0;
                if (absl::SimpleAtoi<int>(date_duration.substr(0, y_pos), &year)) {
                    y = year;
                }
                date_duration = date_duration.substr(y_pos + 1);
            }

            // process month
            auto month_pos = date_duration.find_first_of('M');
            if (month_pos != std::string::npos) {
                int month = 0;
                if (absl::SimpleAtoi<int>(date_duration.substr(0, month_pos), &month)) {
                    mon = month;
                }
                date_duration = date_duration.substr(month_pos + 1);
            }

            // process day
            auto day_pos = date_duration.find_first_of('D');
            if (day_pos != std::string::npos) {
                int day = 0;
                if (absl::SimpleAtoi<int>(date_duration.substr(0, day_pos), &day)) {
                    d = day;
                }
                date_duration = date_duration.substr(day_pos + 1);
            }
        }

        if (!time_duration.empty()){
            std::transform(time_duration.begin(), time_duration.end(), time_duration.begin(),
                           [](unsigned char c) { return std::toupper(c); });
            // process hour
            auto hour_pos = time_duration.find_first_of('H');
            if (hour_pos != std::string::npos) {
                int hour = 0;
                if (absl::SimpleAtoi<int>(time_duration.substr(0, hour_pos), &hour)) {
                    h = hour;
                }
                time_duration = time_duration.substr(hour_pos + 1);
            }

            auto minute_pos = time_duration.find_first_of('M');
            if (minute_pos != std::string::npos) {
                int minute = 0;
                if (absl::SimpleAtoi<int>(time_duration.substr(0, minute_pos), &minute)) {
                    min = minute;
                }
                time_duration = time_duration.substr(minute_pos + 1);
            }

            auto sec_pos = time_duration.find_first_of('S');
            if (sec_pos != std::string::npos) {
                double sec = 0;
                if (absl::SimpleAtod(time_duration.substr(0, sec_pos), &sec)) {
                    ms = static_cast<int64_t>(sec * 1000);
                }
            }
        }
        const int ms_per_minute = 60 * 1000;
        const int ms_per_hour   = 60 * ms_per_minute;
        const int ms_per_day    = 24 * ms_per_hour;
        return d * ms_per_day + h * ms_per_hour + min * ms_per_minute + ms;
    } while (false);
    return std::nullopt;
}

std::optional<int64_t> DateAdvance(std::string& date, std::string& delta) {
    PRTime t;
    if (PRStatus::PR_FAILURE != PR_ParseTimeString(date.c_str(), 1, &t)) {
        return std::nullopt;
    }
    auto delta_time = ParseDurationString(delta);
    if (std::nullopt == delta_time) {
        return std::nullopt;
    }
    return t + delta_time.value();
}

std::optional<int64_t> DateRewind(std::string& date, std::string& delta) {
    PRTime t;
    if (PRStatus::PR_FAILURE != PR_ParseTimeString(date.c_str(), 1, &t)) {
        return std::nullopt;
    }
    auto delta_time = ParseDurationString(delta);
    if (std::nullopt == delta_time) {
        return std::nullopt;
    }
    return t - delta_time.value();
}


std::optional<int64_t> ParseTimeString(const std::string& s) {
    if (s.empty()){
        return std::nullopt;
    }
    PRTime t = 0;
    if (PR_ParseTimeString(s.c_str(),1,&t) == PRStatus::PR_SUCCESS){
        return t;
    }
    return std::nullopt;
}
}  // namespace dash