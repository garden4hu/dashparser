#include "mpd.h"

#include <absl/strings/match.h>

#include <utility>

#include "base/helper.h"
#include "common_parser.h"
#include "identifier.h"
#include "mime.h"
#include "utils/dash_time.h"
#include "xml/dash_xml.h"
namespace dash {

Mpd::Mpd(std::string base_url) : base_url_(std::move(base_url)) {}

StatusCode Mpd::Parse(const char* xml, int len) {
    auto docXml = initXmlDoc(xml, len);
    if (!docXml) {
        return StatusCode::kErrorInvalidMPD;
    }

    doc = std::move(docXml);  // find mpd node
    auto mpd = FindChildNodeInDoc(doc, kElemMpd);
    if (!mpd) {
        return StatusCode::kErrorInvalidMPD;
    }
    return ParseMpdTag(mpd);
}
StatusCode Mpd::ParseMpdTag(void* node) {
    auto mpd          = (xmlNodePtr)node;
    // parse properties
    auto parse_result = parseMpdLevelAttr(mpd);
    if (parse_result != StatusCode::kOk) {
        return parse_result;
    }

    // parse BaseURL if exist
    auto base_url = FindChildNodesAll(mpd, kElemBaseURL);
    if (!base_url.empty()) {
        std::for_each(base_url.begin(), base_url.end(), [this](xmlNodePtr url) {
            auto base_url        = ParseBaseUrl(url);
            base_url.source_url_ = CAST_XML_CHAR_TO_CHAR(url->content);
            base_urls_.emplace_back(std::move(base_url));
        });
    }

    // parse Location
    auto locations = FindChildNodesAll(mpd, kElemLocation);
    if (!locations.empty()) {
        std::for_each(locations.begin(), locations.end(), [this](xmlNodePtr node) {
            locations_.emplace_back(CAST_XML_CHAR_TO_CHAR(node->content));
        });
    }
    // parse UTCTing

    auto utc_timing = FindChildNodesAll(mpd, kElemUTCTiming);
    if (!utc_timing.empty()) {
        std::for_each(utc_timing.begin(), utc_timing.end(), [this](xmlNodePtr node) {
            auto utc = ParseUtcTiming(node);
            if (utc.has_value()) {
                utc_timing_.emplace_back(std::move(utc.value()));
            }
        });
    }
    auto periods = FindChildNodesAll(mpd, kElemPeriod);
    return StatusCode::kOk;
}
StatusCode Mpd::parseMpdLevelAttr(const xmlNodePtr mpd) {
    do {
        auto mpd_type = getNodeProp(mpd, kPropType);
        auto profile  = getNodeProp(mpd, kPropProfiles);
        if (profile.empty()) {
            return StatusCode::kErrorInvalidMPD;
        }
        if (absl::StrContains(profile, kSchemaIdProfileISOFFVOD) ||
            absl::StrContains(profile, kSchemaIdProfileISOFFExtVOD)) {
            if (mpd_type == "static" || mpd_type.empty()) {
                type_ = TYPE::DASH_MPD_TYPE_STATIC;
            }
            profile_ = absl::StrContains(profile, kSchemaIdProfileISOFFVOD)
                           ? ProfileType::ISO_FF_ON_DEMAND
                           : ProfileType::ISO_FF_EXT_ON_DEMAND;
        } else if (absl::StrContains(profile, kSchemaIdProfileISOFFLIVE) ||
                   absl::StrContains(profile, kSchemaIdProfileISOFFExtLIVE)) {
            if (mpd_type == "dynamic" || mpd_type.empty()) {
                type_ = TYPE::DASH_MPD_TYPE_DYNAMIC;
            }
            profile_ = absl::StrContains(profile, kSchemaIdProfileISOFFLIVE)
                           ? ProfileType::ISO_FF_LIVE
                           : ProfileType::ISO_FF_EXT_LIVE;
        } else if (absl::StrContains(profile, kSchemaIdProfileISOFFMain) ||
                   absl::StrContains(profile, kSchemaIdProfileISOFFCommon)) {
            type_ =
                mpd_type == "dynamic" ? TYPE::DASH_MPD_TYPE_DYNAMIC : TYPE::DASH_MPD_TYPE_STATIC;
            profile_ = absl::StrContains(profile, kSchemaIdProfileISOFFMain)
                           ? ProfileType::ISO_FF_MAIN
                           : ProfileType::ISO_FF_COMMON;
        } else if (absl::StrContains(profile, kSchemaIdProfileMP2TMain) ||
                   absl::StrContains(profile, kSchemaIdProfileMP2TSimple)) {
            type_ =
                mpd_type == "dynamic" ? TYPE::DASH_MPD_TYPE_DYNAMIC : TYPE::DASH_MPD_TYPE_STATIC;
            profile_ = absl::StrContains(profile, kSchemaIdProfileMP2TMain)
                           ? ProfileType::MPEG2T_MAIN
                           : ProfileType::MPEG2T_SIMPLE;
        } else {
            return StatusCode::KErrorInvalidMPDProfile;
        }

        id_ = getNodeProp(mpd, kPropID).empty() ? getNodeProp(mpd, kPropID) : base_url_;
        SetIfHasValue<int, int64_t>(min_buffer_time_,
                                    ParseDurationString(getNodeProp(mpd, kPropMinBufferTime)));

        availability_start_time_ = ParseTimeString(getNodeProp(mpd, kPropAvailabilityStartTime));
        availability_end_time_   = ParseTimeString(getNodeProp(mpd, kPropAvailabilityEndTime));
        media_presentation_duration_ =
            ParseTimeString(getNodeProp(mpd, kPropMediaPresentationDuration));

        max_segment_duration_ = ParseDurationString(getNodeProp(mpd, kPropMaxSegmentDuration));
        // check live props
        if (type_ == TYPE::DASH_MPD_TYPE_DYNAMIC) {
            SetIfHasValue<int64_t, int64_t>(publish_time_,
                                            ParseTimeString(getNodeProp(mpd, kPropPublishTime)));
            SetIfHasValue<int64_t, int64_t>(
                time_shift_buffer_depth_,
                ParseDurationString(getNodeProp(mpd, kPropTimeShiftBufferDepth)));
            minimum_update_period_ =
                ParseDurationString(getNodeProp(mpd, kPropMinimumUpdatePeriod));
            suggested_presentation_delay_ =
                ParseDurationString(getNodeProp(mpd, kPropSuggestedPresentationDelay));
        }
    } while (false);
    return StatusCode::kOk;
}
StatusCode Mpd::ParsePeriod(xmlNodePtr period_node) {
    auto period = std::make_unique<Period>();

    return StatusCode::kOk;
}

}  // namespace dash
