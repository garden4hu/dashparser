#include "common_attributes_elements.h"

#include <absl/strings/strip.h>

#include "base/helper.h"
#include "mime.h"
#include "util.h"
#include "xml/dash_xml.h"
namespace dash {
StatusCode CommonAttributesElements::Parse(void* node) {
    auto common_attr_elems = static_cast<xmlNodePtr>(node);
    profile_               = getNodeProp(common_attr_elems, kPropProfiles);
    SetIntegerFromString<int>(width_, getNodeProp(common_attr_elems, kPropWidth));
    SetIntegerFromString<int>(height_, getNodeProp(common_attr_elems, kPropHeight));
    auto sar = ParseRatioString(getNodeProp(common_attr_elems, kPropSar));
    if (sar.has_value()) {
        sar_->num = std::get<0>(sar.value());
        sar_->den = std::get<1>(sar.value());
    } else {
        sar_->num = sar_->den = 1;
    }

    auto frame_rate = getNodeProp(common_attr_elems, kPropFrameRate);
    if (!frame_rate.empty()) {
        auto slash_pos   = frame_rate.find('/');
        frame_rate_->num = std::stoi(frame_rate.substr(0, slash_pos));
        frame_rate_->den =
            (slash_pos != std::string::npos) ? std::stoi(frame_rate.substr(slash_pos)) : 1;
    }

    auto audio_sample_rate = getNodeProp(common_attr_elems, kPropAudioSamplingRate);
    if (!audio_sample_rate.empty()) {
        absl::StripAsciiWhitespace(&audio_sample_rate);
        do {
            if (audio_sample_rate.empty()) break;
            auto white_space_found = audio_sample_rate.find(' ');
            if (white_space_found != std::string::npos) {
                audio_sampling_rate_->flooring =
                    std::stoi(audio_sample_rate.substr(0, white_space_found));
                audio_sampling_rate_->ceiling =
                    std::stoi(audio_sample_rate.substr(white_space_found));
            } else {
                audio_sampling_rate_->flooring = audio_sampling_rate_->flooring =
                    std::stoi(audio_sample_rate);
            }
        } while (false);
    }

    mime_type_ = getNodeProp(common_attr_elems, kPropMimeType);

    codecs_    = getNodeProp(common_attr_elems, kPropMimeType);

    SetIntegerFromString<int>(maximum_sap_period_,
                                 getNodeProp(common_attr_elems, kPropMaximumSAPPeriod));

    SetIntegerFromString<int>(start_with_sap_,
                                 getNodeProp(common_attr_elems, kPropMaximumStartWithSAP));
    max_play_out_rate_ = getNodeProp(common_attr_elems, kPropMaxPlayoutRate).empty()
                             ? 1
                             : std::stoi(getNodeProp(common_attr_elems, kPropMaxPlayoutRate));
    auto coding_dependency = getNodeProp(common_attr_elems,kPropCodingDependency);
    if (!coding_dependency.empty()){
        coding_dependency_ = coding_dependency.find("true") != std::string::npos;
    }


}

}  // namespace dash
