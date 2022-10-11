#include "dash.h"

#include <memory>


namespace dash {
StatusCode Dash::open(const std::string& base_url, const char* xml, int len) {
    if (!len){
        return StatusCode::kErrorInvalidMPD;
    }
    current_mpd_ = std::make_unique<Mpd>(base_url);
    if (!current_mpd_->Parse(xml, len)){
        return StatusCode::kErrorInvalidMPD;
    }
    return StatusCode::kOk;
}

StatusCode Dash::update(const std::string& base_url, const std::string& xml) {
    if (xml.empty()){
        return StatusCode::kErrorInvalidMPD;
    }
    // TODO. save current mpd status.
    return StatusCode::kOk;
}

}
