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

/**
 * @brief XmlDurationConvert only support convert the ISO8601 duration into a struct.
 * For example: P2Y11M3D15H59M45.500S Or PT568.500S.
 * It only support the decimal number in second.
 * */
std::unique_ptr<ISO8601Duration> XmlDurationConvert(std::string& xml_duration) {
    int i = -1;
    std::set<char> valid_chars{'P', 'Y', 'M', 'D', 'T', 'H', 'S', '.', ','};
    enum class FSM : int {
        FSM_XML_DURATION_STATE_DATE,
        FSM_XML_DURATION_STATE_TIME,
        FSM_XML_DURATION_STATE_OK,
        FSM_XML_DURATION_STATE_FAILED,
    };
    auto duration = std::make_unique<ISO8601Duration>();
    do {
        while (++i < xml_duration.length()) {
            if (xml_duration[i] != ' ') {
                break;
            }
        }
        xml_duration = xml_duration.substr(i);
        if (xml_duration.length() < 2) {
            break;
        }
        i = 0;
        if (xml_duration[i] != 'P') {
            break;
        }
        auto stage = FSM::FSM_XML_DURATION_STATE_DATE;
        std::stringstream ss;
        while (++i < xml_duration.length() && stage != FSM::FSM_XML_DURATION_STATE_FAILED &&
               stage != FSM::FSM_XML_DURATION_STATE_OK) {
            if (valid_chars.find(xml_duration[i]) != valid_chars.end()) {
                ss.clear();
            }
            switch (xml_duration[i]) {
                case 'Y':
                    ss >> duration->year;
                    break;
                case 'M':
                    if (stage == FSM::FSM_XML_DURATION_STATE_DATE) {
                        ss >> duration->month;
                    } else {
                        ss >> duration->minute;
                    }
                    break;
                case 'D':
                    ss >> duration->day;
                    break;
                case 'T':
                    stage = FSM::FSM_XML_DURATION_STATE_TIME;
                    break;
                case 'H':
                    ss >> duration->hour;
                    break;
                case 'S': {
                    // it may be a float number, and the value may be greater than 59.
                    // so, save it in a separate variable.
                    std::string tmp;
                    ss >> tmp;

                    auto delimiter  = (tmp.find('.') != std::string::npos)
                                          ? tmp.find('.')
                                          : (tmp.find(',') != std::string::npos ? tmp.find(',')
                                                                                : std::string::npos);
                    if (delimiter != std::string::npos) {
                        auto sec = tmp.substr(0, tmp.find('.'));
                        std::stringstream(sec) >> duration->second;
                        auto milli_sec = tmp.substr(tmp.find('.') + 1);
                        if (milli_sec.length() > 6) {
                            stage = FSM::FSM_XML_DURATION_STATE_FAILED;
                            break;
                        }
                        if (milli_sec.length() > 3) {
                            milli_sec = milli_sec.substr(0, 3);  // if having microsecond precision
                        }
                        std::stringstream(milli_sec) >> duration->millisecond;
                        duration->millisecond *= (3 - static_cast<int>(milli_sec.length())) * 10;
                    } else {
                        ss >> duration->second;
                    }
                    stage = FSM::FSM_XML_DURATION_STATE_OK;
                } break;
                default: {
                    if (('0' <= xml_duration[i] && xml_duration[i] <= '9') ||
                        ('.' == xml_duration[i]) || (',' == xml_duration[i])) {
                        ss.putback(xml_duration[i]);
                    } else {
                        stage = FSM::FSM_XML_DURATION_STATE_FAILED;
                    }
                } break;
            }
        }
        if (stage == FSM::FSM_XML_DURATION_STATE_OK) {
            return duration;
        }
        if (stage == FSM::FSM_XML_DURATION_STATE_FAILED) {
            break;
        }
    } while (false);
    return nullptr;
}
}  // namespace dash
