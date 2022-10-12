#include "period.h"

#include "base/helper.h"
#include "mime.h"
#include "utils/dash_time.h"
#include "common_parser.h"
#include "xml/dash_xml.h"
namespace dash {

dash::StatusCode Period::ParsePeriod(void* node) {
    xmlNodePtr period = (xmlNodePtr)node;
    id_                   = getNodeProp(period, kPropID);
    start_                = ParseDurationString(getNodeProp(period, kPropStart));
    duration_             = ParseDurationString(getNodeProp(period, kPropDuration));
    bit_stream_switching_ = getNodeProp(period, kPropDuration) == "true";

    // parse BaseURL
    // parse BaseURL if exist
    auto base_url = FindChildNodesAll(period,kElemBaseURL);
    if (!base_url.empty()){
        std::for_each(base_url.begin(),base_url.end(),[this](xmlNodePtr url){
            auto base_url = ParseBaseUrl(url);
            base_url.source_url_ = CAST_XML_CHAR_TO_CHAR(url->content);
            base_urls_.emplace_back(std::move(base_url));
        });
    }

    auto adaptation_sets = FindChildNodesAll(period,kElemAdaptationSet);
    // process the AdaptationSet
    std::for_each(adaptation_sets.begin(),adaptation_sets.end(),[](xmlNodePtr adaptation_set){
        auto as = std::make_unique<AdaptationSet>();
        // TODO. handle error
        as->ParseAdaptationSet(adaptation_set);
    });

    return dash::StatusCode::kOk;
}

}  // namespace dash