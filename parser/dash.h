#pragma once

#include <string>

#include "mpd.h"
#include "status.h"

namespace dash {

using Track = struct {
    MediaType type_;
    int track_id_;
    std::string language_;
    RoleType role_;
    std::string codec_;
    int bandwidth_;

    // video prop
    int width_;
    int height_;
    float frame_rate_;

    // audio prop
    int channel_count_;
    int sample_rate_;
};

using SegmentUnit = struct {
    MediaType type_;
    std::string url_;
    int duration_; // in ms
    int pts;       // in ms
    int width_;
    int height_;

    optional<NumericalInterval> range_;
};

class Dash {
public:
    Dash() = default;
    ~Dash() = default;

public:
    StatusCode open(const std::string& base_url, const std::string& xml);
    StatusCode update(const std::string& base_url, const std::string& xml);
    bool IsLive() { return !static_cast<int>(current_mpd_->IsVod()); }

private:
    std::unique_ptr<Mpd> current_mpd_;
};
} // namespace dash
