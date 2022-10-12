#pragma  once

#include "common_attributes_elements.h"
#include <libxml/tree.h>


namespace dash {
    BaseURL parseBaseUrl(xmlNodePtr node);
}