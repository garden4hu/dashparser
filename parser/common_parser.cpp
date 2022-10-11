

#include "common_parser.h"
#include "xml/dash_xml.h"
#include "base/helper.h"
namespace dash {

static NumericalInterval parseByteRangeString(const std::string& range){
    
}
BaseURL parseBaseUrl(const xmlNodePtr node) {
    BaseURL base_url{};
    auto service_location = getNodeProp(node,"serviceLocation");
    if (!service_location.empty()){
        base_url.service_location_ = service_location;
    }
    auto range = getNodeProp(node,"byteRange");
    if(!range.empty()){

    }
}
}

