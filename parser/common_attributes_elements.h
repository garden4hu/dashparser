#ifndef DASH_COMMON_ATTRIBUTES_ELEMENTS_H
#define DASH_COMMON_ATTRIBUTES_ELEMENTS_H

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common_type.h"

using std::optional;

namespace dash {



typedef struct {
    int num;
    int den;
} Fraction;

typedef struct {
    int floor;
    int ceiling;
} NumericalInterval;

typedef Fraction FrameRate;

typedef struct audioChannelConfiguration {
    AudioChannelConfigurationType type_;
    optional<int> value_;
    optional<std::string> id_;
} AudioChannelConfiguration;

typedef struct ContentProtection {
    DRMType type_;
    optional<std::string> value_;
    optional<std::string> id_;
    optional<std::string> cenc_default_kid_;
    optional<std::string> cenc_pssh_;
} ContentProtection;

typedef struct DashEvent {
    int64_t presentation_time_ = 0;  // presentation time of the event
    optional<int64_t> duration_;     //  presentation duration of the event
    optional<std::string> id_;
    optional<std::string> message_data_;
} DashEvent;

typedef struct EventStream {
    optional<std::string> value_;
    int time_scale_ = 1;
    std::vector<std::unique_ptr<DashEvent>> events_;
} EventStream;

typedef struct Switching {
    int interval_ = 0;
    // the interval between two switching points in the scale of the @timescale on Representation
    // level.
    int type_     = 0;  // 0: "media", 1: "bitstream".
} Switching;

typedef struct RandomAccess {
    int interval_ = 0;  // the interval between two switching points in the scale of the @timescale
    // on Representation level.
    /**
     * specifies the random access strategy for the random access points.
     * 0: "closed",     Closed GOP random access
     * 1: "open",       Open GOP random access
     * 2: "gradual",    Gradual decoder refresh random access
     */
    int type_     = 0;
    optional<int> min_buffer_time_;
    optional<int> bandwidth_;
} RandomAccess;

typedef struct Label {
    /**
     * For Label, it's the identifier. Labels with same id_ that share the same GroupLabel.
     * For GroupLabel, it's the unique identifier.
     */
    optional<std::string> id_;
    optional<std::string> lang_;
} Label;

typedef Label GroupLabel;

typedef struct CommonAttributesElements {
    optional<std::string> profile_;
    optional<int> width_;
    optional<int> height_;
    optional<Fraction> sar_;
    optional<FrameRate> frame_rate_;
    optional<NumericalInterval> audio_sampling_rate_;
    std::string mime_type_;
    optional<std::string> codecs_;
    optional<int> maximum_sap_period_;
    optional<int> start_with_sap_;
    int max_play_out_rate_ = 1;
    optional<bool> coding_dependency_;
    int scan_type_          = 0;  // 0: progressive, 1: interlaced, 2: unknown
    int selection_priority_ = 1;
    // FramePacking
    std::vector<AudioChannelConfiguration> audio_channel_configurations_;
    std::vector<ContentProtection> content_protections_;
    std::vector<EventStream> in_band_event_streams_;
    std::vector<Switching> switching_;
    std::vector<RandomAccess> random_access_;
    std::vector<Label> labels_;
    std::vector<GroupLabel> group_labels_;
} CommonAttributesElements;

typedef struct UTCTiming {
    UTCTimingServerType utc_server_type_;
    std::vector<std::string> servers_;
} UTCTiming;
}  // namespace dash

#endif  // !DASH_COMMON_ATTRIBUTES_ELEMENTS_H
