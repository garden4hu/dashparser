#pragma once

#include <string>
#include <vector>

#include "mpd.h"
#include "status.h"
namespace dash {

typedef struct Track {
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
    


} Track;

typedef struct SegmentUnit {
    MediaType type_;
    std::string url_;
    int duration_;  // in ms
    int pts;        // in ms
    int width_;
    int height_;

    optional<NumericalInterval> range_;

} SegmentUnit;

class Dash {
  public:
    Dash()  = default;
    ~Dash() = default;

  public:
    StatusCode open(const std::string& base_url, const std::string& xml);
    StatusCode update(const std::string& base_url, const std::string& xml);
    bool isLive() { return !static_cast<int>(mpd_->type_); }

  private:
    std::unique_ptr<Mpd> mpd_;
};
}  // namespace dash