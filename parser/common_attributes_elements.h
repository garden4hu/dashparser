#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common_type.h"
#include "status.h"




using std::optional;

namespace dash {



typedef struct {
    int num;
    int den;
} Fraction;

typedef struct NumericalInterval {
    int flooring   = -1;
    int ceiling = -1;
} NumericalInterval;

 typedef Fraction FrameRate;

//using FrameRate = std::ratio<int, int>;

typedef struct URLType {
    std::optional<NumericalInterval> range_;
    std::string source_url_;  // if it doesn't present, it will inherit from BaseRUL
} URLType;

typedef struct BaseURL : public URLType{
    std::optional<std::string> service_location_;  // may be useful for CDN
    bool range_locates_query_ = false;
} BaseURL;

typedef struct Initialization {
} Initialization;

typedef struct audioChannelConfiguration {
    AudioChannelConfigurationType type_ =
        AudioChannelConfigurationType::DASH_AUDIO_CHANNEL_CONFIG_DASH;
    optional<int> value_;
    optional<std::string> id_;
} AudioChannelConfiguration;

typedef struct ContentProtection {
    DRMType type_ = DRMType::DASH_DRM_DASH_MP4;
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

using GroupLabel = Label;

class CommonAttributesElements {
  public:
    CommonAttributesElements() = default;
    ~CommonAttributesElements() = default;
  public:
    StatusCode Parse(void* node);
  private:
    // Mandatory parameters
    std::string mime_type_;  // "application/mp4", "video/mp4", "audio/mp4"

    // Optional parameters
    optional<std::string> profile_;
    optional<int> width_;
    optional<int> height_;
    optional<Fraction> sar_;
    optional<FrameRate> frame_rate_;
    optional<NumericalInterval> audio_sampling_rate_;
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
} ;

typedef struct UTCTiming {
    UTCTimingServerType utc_server_type_;
    std::string servers_;
} UTCTiming;

typedef struct SupplementalProperty {
} SupplementalProperty;

typedef struct EssentialProperty {
} EssentialProperty;

typedef struct ProgramInformation {
    std::string lang_;
    std::string title_;
} ProgramInformation;

// typedef struct Accessibility {
//
// } Accessibility;

typedef struct ContentComponent {
    int id_;  // track id in ISOBMFF or PID in MP2-TS
    std::string lang_;
    std::string content_type_;  // TODO. need to check the type.
    Fraction par_;
    std::string tag_;
    std::vector<RoleType> roles_;
} ContentComponent;
}  // namespace dash
