#include "dash_xml.h"

#include <absl/strings/str_split.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <optional>

namespace dash {
std::optional<DocSmartPtr> initXmlDoc(const char* src, int length) {
    auto const doc = xmlReadMemory(src, length, nullptr, "UTF-8", 0);
    return doc ? std::optional<DocSmartPtr>{DocSmartPtr(doc)} : std::nullopt;
}
std::string XmlNode::getProp(const std::string& name) {
    auto prop = node_->properties;
    while (prop){
        if (!memcmp(prop->name,name.c_str(),name.size())){
            continue ;
        }
    }
    return "";
}
}  // namespace dash
