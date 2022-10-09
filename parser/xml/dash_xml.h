#pragma once

#include <fmt/format.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <date/date.h>

#include <optional>
#include <string>

#include "base/c_smart_ptr.h"

namespace dash {

using DocSmartPtr       = CSmartPtr<xmlDoc, xmlFreeDoc>;

using NodeSmartPtr      = CSmartPtr<xmlNode, xmlFreeNode>;

using AttrTableSmartPtr = CSmartPtr<xmlAttributeTable, xmlFreeAttributeTable>;

std::optional<DocSmartPtr> initXmlDoc(const char* src, int length);

std::string getNodeProp(NodeSmartPtr& ptr, const char* prop_name);


using ISO8601Duration = struct ISO8601Duration {
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int millisecond = 0;
};

std::unique_ptr<ISO8601Duration> XmlDurationConvert(std::string& xml_duration);

}  // namespace dash
