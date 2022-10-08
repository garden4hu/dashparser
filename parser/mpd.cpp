#include "mpd.h"


namespace dash{

Mpd::Mpd(const std::string& base_url):base_url_(base_url) {

}

bool Mpd::Parse(const std::string& xml) {
    std::optional<DocSmartPtr> docXml = initXmlDoc(xml.c_str(),xml.length());
    if (!docXml.has_value()){
        return false;
    }
    DocSmartPtr& doc = docXml.value();
    if (doc->children == nullptr){
        return false;
    }
    bool has_mpd = false;
    auto item = doc->children;
    while (item != nullptr){
        if (!memcmp(item->name, "MPD",3)){
            has_mpd = true;
            break ;
        }
        item = item->next;
    }
    if (!has_mpd){
        return false;
    }
    ParseMpdTag(std::move(NodeSmartPtr(item)));
    return true ;
}
bool Mpd::ParseMpdTag(NodeSmartPtr node) {



    return true;

}
}
