#include "adaptation_set.h"

#include "drm.h"

namespace dash {
AdaptationSet::AdaptationSet() {
    common_attributes_elements_.reset(new CommonAttributesElements());
}
}  // namespace dash
