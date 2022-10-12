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


xmlNodePtr FindChildNode( const xmlNodePtr & node, const xmlCharPtr  node_name){
    auto item    = node->children;
    while (item != nullptr) {
        if (!xmlStrEqual(item->name, node_name)) {
            return item;
        }
        item = item->next;
    }
}

xmlNodePtr FindChildNodeInDoc( const DocSmartPtr & doc, xmlCharPtr const node_name){
    bool found = false;
    auto item    = doc->children;
    while (item != nullptr) {
        if (xmlStrEqual(item->name, node_name)  == 0) {
            found = true;
            break;
        }
        item = item->next;
    }
    return found ? item : nullptr;
}

std::string getNodeProp(const xmlNodePtr& node, const xmlCharPtr prop_name) {
    std::string prop{};
    auto attr = xmlGetProp(node,prop_name);
    if (attr != nullptr){
        prop = (char*)(attr);
        xmlFree(attr);
    }
    return prop;
}


std::vector<xmlNodePtr> FindChildNodesAll( const xmlNodePtr & node, const xmlCharPtr node_name){
    auto item    = node->children;
    std::vector<xmlNodePtr> v;
    while (item != nullptr) {
        if (xmlStrEqual(item->name, node_name)  == 0){
            v.emplace_back(item);
        }
        item = item->next;
    }
    return v;
}
}  // namespace dash
