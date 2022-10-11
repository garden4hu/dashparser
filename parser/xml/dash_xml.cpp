#include "dash_xml.h"

#include <absl/strings/str_split.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <optional>

namespace dash {
DocSmartPtr initXmlDoc(const char* src, int length) {
    return xmlReadMemory(src, length, nullptr, "UTF-8", 0);
}
std::string getNodeProp(NodeSmartPtr& ptr, const char* prop_name) {
    auto prop = xmlGetProp(ptr.get(), CAST_CHAR_TO_XML_CHAR(prop_name));
    if (prop) {
        return CAST_XML_CHAR_TO_CHAR(prop);
    }
    return "";
}


xmlNodePtr FindChildNode( const xmlNodePtr & node, const std::string& name){
    bool found = false;
    auto item    = node->children;
    while (item != nullptr) {
        if (!memcmp(item->name, name.c_str(), name.length())) {
            found = true;
            break;
        }
        item = item->next;
    }
    return found ? item : nullptr;
}

xmlNodePtr FindChildNodeInDoc( const DocSmartPtr & doc, const std::string& name){
    bool found = false;
    auto item    = doc->children;
    while (item != nullptr) {
        if (!memcmp(item->name, name.c_str(), name.length())) {
            found = true;
            break;
        }
        item = item->next;
    }
    return found ? item : nullptr;
}

std::string getNodeProp(const xmlNodePtr& node, const std::string& prop_name) {
    auto prop = node->properties;
    bool found = false;
    while(prop != nullptr){
        if (memcmp(prop->name,prop_name.c_str(),prop_name.length()) == 0){
            found = true;
            break ;
        }
        prop = prop->next;
    }
    return found ? CAST_XML_CHAR_TO_CHAR(prop->children->content) : std::string() ;
}


std::vector<xmlNodePtr> FindChildNodesAll( const xmlNodePtr & node, const std::string& name){
    auto item    = node->children;
    std::vector<xmlNodePtr> v;
    while (item != nullptr) {
        if (!memcmp(item->name, name.c_str(), name.length())) {
            v.emplace_back(item);
        }
        item = item->next;
    }
    return v;
}
}  // namespace dash
