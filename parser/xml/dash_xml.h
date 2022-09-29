#pragma once

#include <absl/types/optional.h>
#include <fmt/format.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <optional>
#include <string>

#include "base/c_smart_ptr.h"

namespace dash {

using DocSmartPtr       = CSmartPtr<xmlDoc, xmlFreeDoc>;

using NodeSmartPtr      = CSmartPtr<xmlNode, xmlFreeNode>;

using AttrTableSmartPtr = CSmartPtr<xmlAttributeTable, xmlFreeAttributeTable>;

std::optional<DocSmartPtr> initXmlDoc(const char* src, int length);

class XmlNode {
  public:
    explicit XmlNode(NodeSmartPtr ptr) : node_(std::move(ptr)) {}

    [[nodiscard]] NodeSmartPtr getParentNode() const { return {node_->parent}; }

  private:
    NodeSmartPtr node_;
};
}  // namespace dash

