

#include "common_parser.h"
#include "xml/dash_xml.h"
#include "base/helper.h"
namespace dash {

static NumericalInterval parseByteRangeString(const std::string& range){
    
}
BaseURL parseBaseUrl(xmlNodePtr node) {
    BaseURL base_url{};
    auto service_location = getNodeProp(node,"serviceLocation");
    if (!service_location.empty()){
        base_url.service_location_ = service_location;
    }
    auto range = getNodeProp(node,"byteRange");
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
}

