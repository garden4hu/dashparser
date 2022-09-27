#ifndef DASH_MPD_H
#define DASH_MPD_H

#pragma once

#include <optional>
#include <string>
#include <cmath>
#include <list>
#include <queue>

using std::optional;

namespace dash {

class ProgramInformation;
class BaseURL;
class Location;
class Period;
class Metrics;
class EssentialProperty;
class SupplementalProperty;
class UTCTiming;

class Mpd {
public:
    Mpd() = default;
    ~Mpd() = default;
    Mpd(Mpd& mpd) = default;
    optional<std::string> id_;

    enum class Type {
        DASH_MPD_TYPE_STATIC,
        DASH_MPD_TYPE_DYNAMIC
    };

    struct DynamicAttr {
        int64_t publish_time_ = INT64_MIN;
        optional<int64_t> minimum_update_period_;
        int64_t time_shift_buffer_depth_ = INT64_MAX;
        optional<int32_t> suggested_presentation_delay_;
    };

    Type type_ = Type::DASH_MPD_TYPE_STATIC;

    optional<int64_t> availability_start_time_; // shall be present when dynamic

    optional<int64_t> availability_end_time_; // the last segment end time

    // shall be present when neither the attribute MPD@minimumUpdatePeriod nor the Period @duration
    // of the last Period are present.
    optional<int64_t> media_presentation_duration_;

    optional<int64_t> max_segment_duration_; // the duration of any segment

    int32_t min_buffer_time_ = 0;

    std::list<ProgramInformation> program_information_;
    std::list<BaseURL> base_urls_;
    std::list<Location> locations_;
    std::vector<Period> periods_;
    std::list<Metrics> metrics_;
    std::list<EssentialProperty> essential_properties_;
    std::list<SupplementalProperty> supplemental_properties_;
    std::list<UTCTiming> utc_timing_;
};

} // namespace dash

#endif  // !DASH_MPD_H
