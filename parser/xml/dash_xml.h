#pragma once

#include <fmt/format.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <date/date.h>

#include <optional>
#include <string>
#include <vector>

#include "base/c_smart_ptr.h"
#include "utils/prtime.h"

namespace dash {

#define CAST_XML_CHAR_TO_CHAR(str) (char *)(str)
#define CAST_CHAR_TO_XML_CHAR(str) (xmlChar *)(str)

using DocSmartPtr       = CSmartPtr<xmlDoc, xmlFreeDoc>;
using NodeSmartPtr      = CSmartPtr<xmlNode, xmlFreeNode>;

using xmlCharPtr = xmlChar*;

using AttrTableSmartPtr = CSmartPtr<xmlAttributeTable, xmlFreeAttributeTable>;

DocSmartPtr initXmlDoc(const char* src, int length);

std::string getNodeProp(const xmlNodePtr& node, const xmlCharPtr prop_name);

xmlNodePtr FindChildNode( const xmlNodePtr & node, const xmlCharPtr  node_name);

std::vector<xmlNodePtr> FindChildNodesAll( const xmlNodePtr & node, const xmlCharPtr node_name);


xmlNodePtr FindChildNodeInDoc( const DocSmartPtr & node, const xmlCharPtr node_name);






}  // namespace dash
