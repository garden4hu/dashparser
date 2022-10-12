#pragma  once

#include "common_attributes_elements.h"
#include <libxml/tree.h>
#include "status.h"

namespace dash {
    BaseURL ParseBaseUrl(xmlNodePtr node);
    std::optional<UTCTiming>  ParseUtcTiming(xmlNodePtr node);
    StatusCode ParseCommonAttributesElements(xmlNodePtr node);

}