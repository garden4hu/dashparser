#pragma once

#include "common_attributes_elements.h"

namespace dash {
class Representation : public CommonAttributesElements {
  public:
    Representation()                                 = default;
    ~Representation()                                = default;
    Representation(const Representation&)            = default;
    Representation& operator=(const Representation&) = default;
    Representation(const Representation&&)           = default;

  public:
    std::string id_;
    int bandwidth = 0;
    std::vector<BaseURL> base_urls_;
    optional<std::string> quality_ranking_;
    optional<std::string> dependency_id_;
    optional<std::string> association_id_;
    optional<std::string> association_type_;  // work with association_id_
    optional<std::string> media_stream_structure_id_;
};
}  // namespace dash
