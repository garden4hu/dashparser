

#include "common_parser.h"
#include "xml/dash_xml.h"
#include "base/helper.h"
#include "mime.h"
#include "identifier.h"
namespace dash {

static NumericalInterval parseByteRangeString(const std::string& range){
    
}
BaseURL ParseBaseUrl(xmlNodePtr node) {
    BaseURL base_url{};
    auto service_location = getNodeProp(node,kPropServiceLocation);
    if (!service_location.empty()){
        base_url.service_location_ = service_location;
    }
    auto range = getNodeProp(node,kPropByteRange);
    if(!range.empty()){
        // byteRange looks like:
        //  1. $base$?$query$&range=$first$-$last$
        //  2. $base$/range/$first$-$last$
        // we just to check where should the range locates, PATH OR QUERY
        // Note: it doesn't check whether the template contains unrecognized identifiers.
        if (range.find("/range/")){
            base_url.range_locates_query_ = false;
        }
        if (range.find("?$query$")){
            base_url.range_locates_query_ = true;
        }
    }
    return base_url;
}
std::optional<UTCTiming> ParseUtcTiming(xmlNodePtr node) {
    UTCTiming utc;
    auto utc_type = getNodeProp(node,kPropSchemeIdUri);
    if (utc_type == kSchemaIdUTCTimingNTP){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_NTP;
    }else if (utc_type == kSchemaIdUTCTimingSNTP){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_SNTP;
    } else if (utc_type == kSchemaIdUTCTimingHttpHead){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_HTTP_HEAD;
    }else if (utc_type == kSchemaIdUTCTimingHttpXsDate){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_HTTP_XS_DATE;
    }else if (utc_type == kSchemaIdUTCTimingHttpISO){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_HTTP_ISO;
    }else if (utc_type == kSchemaIdUTCTimingHttpNTP){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_HTTP_NTP;
    }else if (utc_type == kSchemaIdUTCTimingDirect){
        utc.utc_server_type_ = DASH_UTC_TIMING_SERVER_DIRECT;
    } else{
        return std::nullopt;
    }
    utc.servers_ = getNodeProp(node,kPropValue);
    return utc;
}
}

