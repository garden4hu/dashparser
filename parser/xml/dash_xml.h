#pragma once

#include <fmt/format.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <date/date.h>

#include <optional>
#include <string>

#include "base/c_smart_ptr.h"
#include "utils/prtime.h"

namespace dash {

using DocSmartPtr       = CSmartPtr<xmlDoc, xmlFreeDoc>;

using NodeSmartPtr      = CSmartPtr<xmlNode, xmlFreeNode>;

using AttrTableSmartPtr = CSmartPtr<xmlAttributeTable, xmlFreeAttributeTable>;

std::optional<DocSmartPtr> initXmlDoc(const char* src, int length);

std::string getNodeProp(NodeSmartPtr& ptr, const char* prop_name);






}  // namespace dash
