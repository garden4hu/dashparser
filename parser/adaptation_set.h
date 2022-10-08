#ifndef DASH_ADAPTATION_SET_H
#define DASH_ADAPTATION_SET_H
#pragma once

#include <optional>
#include <string>

#include "common_attributes_elements.h"
#include "representation.h"
#include "segment.h"

using std::optional;

namespace dash {
class AdaptationSet : public CommonAttributesElements {
  public:
    AdaptationSet() = default;
    ~AdaptationSet()               = default;

    optional<std::string> id_;
    optional<uint32_t> group_;

    optional<std::string> lang_;

    optional<std::string> content_type_;

    bool segment_alignment_         = false;

    // When this attribute is set to true, the DASH  Client can continue decoding without
    // reinitialization
    bool bit_stream_switching_      = false;
    bool sub_segment_alignment_     = false;
    int sub_segment_starts_with_SAP = 0;

    // BaseURL in adaptationSet level
    optional<std::vector<std::unique_ptr<BaseURL>>> base_urls_;

    // SegmentList in adaptationSet level, at most one
    optional<std::unique_ptr<SegmentList>> segment_list_;
    // SegmentTemplate in adaptationSet level, at most one
    optional<std::unique_ptr<SegmentTemplate>> segment_template_;

    // Representation in adaptationSet level, at least one
    std::vector<std::unique_ptr<Representation>> representations_;

    std::vector<RoleType> types_;
    std::vector<ContentComponent> content_component_;
};
}  // namespace dash

#endif  // !ADAPTATION_SET_H
