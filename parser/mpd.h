#pragma once

#include <cmath>
#include <list>
#include <optional>
#include <queue>
#include <string>
#include <absl/strings/str_split.h>

#include "period.h"
#include "status.h"
#include "xml/dash_xml.h"

using std::optional;

namespace dash {

class Metrics {};  // place holder

using DynamicAttr = struct DynamicAttr {
    int64_t publish_time_ = INT64_MIN;
    optional<int64_t> minimum_update_period_;
    int64_t time_shift_buffer_depth_ = INT64_MAX;
    optional<int32_t> suggested_presentation_delay_;
};

class Mpd : public DynamicAttr {
  public:
    Mpd() = default;
    explicit Mpd(std::string  base_url);
    ~Mpd() = default;

    optional<std::string> id_;

    enum class TYPE : int {
        DASH_MPD_TYPE_STATIC  = 0,
        DASH_MPD_TYPE_DYNAMIC = 1,
    };

  public:
    bool Parse(const char* xml, int len);
    StatusCode ParseMpdTag(NodeSmartPtr mpd);

    bool IsVod() { return type_ == TYPE::DASH_MPD_TYPE_STATIC; }

  private:
    TYPE type_ = TYPE::DASH_MPD_TYPE_STATIC;

    optional<int64_t> availability_start_time_;  // shall be present when dynamic

    optional<int64_t> availability_end_time_;  // the last segment end time

    // shall be present when neither the attribute MPD@minimumUpdatePeriod nor the Period @duration
    // of the last Period are present.
    optional<int64_t> media_presentation_duration_;

    optional<int64_t> max_segment_duration_;  // the duration of any segment

    int32_t min_buffer_time_ = 0;

    std::vector<std::unique_ptr<Period>> periods_;

    std::list<ProgramInformation> program_information_;

    std::list<BaseURL> base_urls_;

    std::list<std::string> locations_;

    std::list<Metrics> metrics_;

    std::list<EssentialProperty> essential_properties_;

    std::list<SupplementalProperty> supplemental_properties_;

    std::list<UTCTiming> utc_timing_;

  private:
    std::string base_url_;

    enum class ProfileType : int {
        ISO_FF_ON_DEMAND,
        ISO_FF_EXT_ON_DEMAND,
        ISO_FF_LIVE,
        ISO_FF_EXT_LIVE,
        ISO_FF_MAIN,
        ISO_FF_COMMON,
        ISO_FF_BROADCAST,
        MPEG2T_MAIN,
        MPEG2T_SIMPLE
    };

    ProfileType profile_ = ProfileType::ISO_FF_ON_DEMAND;
};



}  // namespace dash
