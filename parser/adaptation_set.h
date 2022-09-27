#ifndef DASH_ADAPTATION_SET_H
#define DASH_ADAPTATION_SET_H
#pragma once

#include <optional>
#include <string>
#include "common_attributes.h"

using std::optional;

class AdaptationSet {
public:
    AdaptationSet() = default;
    ~AdaptationSet() = default;
    AdaptationSet(AdaptationSet&) = default;
    AdaptationSet(AdaptationSet&&) = default;

    optional<std::string> id_;
    optional<uint32_t> group_;

    CommonAttribute common_attribute_;

    optional<std::string> lang_;

    optional<std::string> content_type_;

    optional<int> min_band_width_;
    optional<int> max_band_width_;

    optional<int> min_width_;
    optional<int> max_width_;

    optional<int> min_height_;
    optional<int> max_height_;

        optional<int> min_frame_rate_;
    optional<int> max_frame_rate_;

    bool segment_alignment_ = false;

    bool bit_stream_switching_ = false; // When this attribute is set to true, the DASH  Client can continue decoding without reinitialization

    bool sub_segment_alignment_ = false;
    int sub_segment_starts_with_SAP = 0;


    
};


#endif  // !ADAPTATION_SET_H
