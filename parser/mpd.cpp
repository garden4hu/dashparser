#include "mpd.h"

#include <utility>

#include "base/helper.h"
#include "identifier.h"
#include "utils/dash_time.h"
#include <absl/strings/match.h>

namespace dash {

Mpd::Mpd(std::string base_url) : base_url_(std::move(base_url)) {}

StatusCode Mpd::Parse(const char* xml, int len) {
   do{
       auto docXml = initXmlDoc(xml, len);
       if (!docXml) {
           return  StatusCode::kErrorInvalidMPD;
       }
       doc = std::move(docXml);
       // find mpd node
       auto mpd = FindChildNodeInDoc(doc,"MPD");
       if (!mpd){
           return StatusCode::kErrorInvalidMPD;
       }
       ParseMpdTag(mpd);
   }while(false);
    return  StatusCode::kOk;
}
StatusCode Mpd::ParseMpdTag(const xmlNodePtr mpd) {

    // parse properties
    auto parse_result = parseMpdLevelAttr(mpd);
    if (parse_result != StatusCode::kOk){
        return parse_result;
    }

    // parse BaseURL if exist
    auto base_url = FindChildNodesAll(mpd,"BaseURL");
    if (!base_url.empty()){
        std::for_each(base_url.begin(),base_url.end(),[](xmlNodePtr url){});
    }

    return StatusCode::kOk;
}
StatusCode Mpd::parseMpdLevelAttr(const xmlNodePtr mpd) {
    do {
        auto mpd_type = getNodeProp(mpd, "type");
        auto profile  = getNodeProp(mpd, "profiles");
        if (profile.empty()) {
            return StatusCode::kErrorInvalidMPD;
        }
        if (absl::StrContains(profile,kSchemaIdProfileISOFFVOD) || absl::StrContains(profile,kSchemaIdProfileISOFFExtVOD)) {
            if (mpd_type == "static" || mpd_type.empty()) {
                type_ = TYPE::DASH_MPD_TYPE_STATIC;
            }
            profile_ = absl::StrContains(profile,kSchemaIdProfileISOFFVOD) ? ProfileType::ISO_FF_ON_DEMAND
                                                              : ProfileType::ISO_FF_EXT_ON_DEMAND;
        } else if (absl::StrContains(profile,kSchemaIdProfileISOFFLIVE) ||
                   absl::StrContains(profile,kSchemaIdProfileISOFFExtLIVE)) {
            if (mpd_type == "dynamic" || mpd_type.empty()) {
                type_ = TYPE::DASH_MPD_TYPE_DYNAMIC;
            }
            profile_ = absl::StrContains(profile,kSchemaIdProfileISOFFLIVE) ? ProfileType::ISO_FF_LIVE
                                                               : ProfileType::ISO_FF_EXT_LIVE;
        } else if (absl::StrContains(profile, kSchemaIdProfileISOFFMain) || absl::StrContains(profile, kSchemaIdProfileISOFFCommon) ) {
            type_    = mpd_type == "dynamic" ? TYPE::DASH_MPD_TYPE_DYNAMIC : TYPE::DASH_MPD_TYPE_STATIC;
            profile_ = absl::StrContains(profile,kSchemaIdProfileISOFFMain) ? ProfileType::ISO_FF_MAIN
                                                               : ProfileType::ISO_FF_COMMON;
        } else if (absl::StrContains(profile,kSchemaIdProfileMP2TMain) || absl::StrContains(profile,kSchemaIdProfileMP2TSimple)) {
            type_    = mpd_type == "dynamic" ? TYPE::DASH_MPD_TYPE_DYNAMIC : TYPE::DASH_MPD_TYPE_STATIC;
            profile_ = absl::StrContains(profile,kSchemaIdProfileMP2TMain) ? ProfileType::MPEG2T_MAIN
                                                              : ProfileType::MPEG2T_SIMPLE;
        } else {
            return StatusCode::KErrorInvalidMPDProfile;
        }

        id_ = getNodeProp(mpd, "id").empty() ? getNodeProp(mpd, "id") : base_url_;
        SetIfHasValue<int, int64_t>(min_buffer_time_,
                                    ParseDurationString(getNodeProp(mpd, "minBufferTime")));

        availability_start_time_     = ParseTimeString(getNodeProp(mpd, "availabilityStartTime"));
        availability_end_time_       = ParseTimeString(getNodeProp(mpd, "availabilityEndTime"));
        media_presentation_duration_ = ParseTimeString(getNodeProp(mpd, "mediaPresentationDuration"));

        max_segment_duration_        = ParseDurationString(getNodeProp(mpd, "maxSegmentDuration"));
        // check live props
        if (type_ == TYPE::DASH_MPD_TYPE_DYNAMIC) {
            SetIfHasValue<int64_t, int64_t>(publish_time_,
                                            ParseTimeString(getNodeProp(mpd, "publishTime")));
            SetIfHasValue<int64_t, int64_t>(
                time_shift_buffer_depth_,
                ParseDurationString(getNodeProp(mpd, "timeShiftBufferDepth")));
            minimum_update_period_ = ParseDurationString(getNodeProp(mpd, "minimumUpdatePeriod"));
            suggested_presentation_delay_ =
                ParseDurationString(getNodeProp(mpd, "suggestedPresentationDelay"));
        }
    }while(false);
    return StatusCode::kOk;
}

}  // namespace dash
