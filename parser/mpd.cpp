#include "mpd.h"

#include <chrono>
#include <ctime>
#include <sstream>
#include <utility>

#include "identifier.h"
#include "utils/dash_time.h"

namespace dash {

Mpd::Mpd(std::string base_url) : base_url_(std::move(base_url)) {}

bool Mpd::Parse(const char* xml, int len) {
    std::optional<DocSmartPtr> docXml = initXmlDoc(xml, len);
    if (!docXml.has_value()) {
        return false;
    }
    DocSmartPtr& doc = docXml.value();
    if (doc->children == nullptr) {
        return false;
    }

    // find mpd node
    bool has_mpd = false;
    auto item    = doc->children;
    while (item != nullptr) {
        if (!memcmp(item->name, "MPD", 3)) {
            has_mpd = true;
            break;
        }
        item = item->next;
    }
    if (!has_mpd) {
        return false;
    }
    ParseMpdTag(std::move(NodeSmartPtr(item)));
    return true;
}
StatusCode Mpd::ParseMpdTag(NodeSmartPtr mpd) {
    // find type prop in MPD node
    auto mpd_type = getNodeProp(mpd, "type");
    auto profile  = getNodeProp(mpd, "profiles");
    if (profile.empty()) {
        return StatusCode::kErrorInvalidMPD;
    }
    if (profile.find(kSchemaIdProfileISOFFVOD) || profile.find(kSchemaIdProfileISOFFExtVOD)) {
        if (mpd_type == "static" || mpd_type.empty()) {
            type_ = TYPE::DASH_MPD_TYPE_STATIC;
        }
        profile_ = profile.find(kSchemaIdProfileISOFFVOD) ? ProfileType::ISO_FF_ON_DEMAND
                                                          : ProfileType::ISO_FF_EXT_ON_DEMAND;
    } else if (profile.find(kSchemaIdProfileISOFFLIVE) ||
               profile.find(kSchemaIdProfileISOFFExtLIVE)) {
        if (mpd_type == "dynamic" || mpd_type.empty()) {
            type_ = TYPE::DASH_MPD_TYPE_DYNAMIC;
        }
        profile_ = profile.find(kSchemaIdProfileISOFFLIVE) ? ProfileType::ISO_FF_LIVE
                                                           : ProfileType::ISO_FF_EXT_LIVE;
    } else if (profile.find(kSchemaIdProfileISOFFMain) ||
               profile.find(kSchemaIdProfileISOFFCommon)) {
        type_    = mpd_type == "dynamic" ? TYPE::DASH_MPD_TYPE_DYNAMIC : TYPE::DASH_MPD_TYPE_STATIC;
        profile_ = profile.find(kSchemaIdProfileISOFFMain) ? ProfileType::ISO_FF_MAIN
                                                           : ProfileType::ISO_FF_COMMON;
    } else if (profile.find(kSchemaIdProfileMP2TMain) || profile.find(kSchemaIdProfileMP2TSimple)) {
        type_    = mpd_type == "dynamic" ? TYPE::DASH_MPD_TYPE_DYNAMIC : TYPE::DASH_MPD_TYPE_STATIC;
        profile_ = profile.find(kSchemaIdProfileMP2TMain) ? ProfileType::MPEG2T_MAIN
                                                          : ProfileType::MPEG2T_SIMPLE;
    } else {
        return StatusCode::KErrorInvalidMPDProfile;
    }

    // get id
    id_                      = getNodeProp(mpd, "id").empty() ? getNodeProp(mpd, "id") : base_url_;

    availability_start_time_ = ParseTimeString(getNodeProp(mpd, "availabilityStartTime"));
    availability_end_time_   = ParseTimeString(getNodeProp(mpd, "availabilityEndTime"));

    // check live props
    if (type_ == TYPE::DASH_MPD_TYPE_DYNAMIC) {
        // availability_start_time_ = getNodeProp(mpd, "availabilityStartTime");
        auto timeShiftBufferDepth = getNodeProp(mpd, "timeShiftBufferDepth");
        auto publishTime          = getNodeProp(mpd, "publishTime");
        auto minimumUpdatePeriod  = getNodeProp(mpd, "minimumUpdatePeriod");
        auto minBufferTime        = getNodeProp(mpd, "minBufferTime");
    }

    return StatusCode::kOk;
}

}  // namespace dash
