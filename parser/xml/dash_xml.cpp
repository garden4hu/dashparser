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
std::string getNodeProp(NodeSmartPtr& ptr, const char* prop_name) {
    auto prop = xmlGetProp(ptr.get(), reinterpret_cast<const xmlChar*>(prop_name));
    if (prop) {
        return reinterpret_cast<const char* const>(prop);
    }
    return "";
}


}  // namespace dash
