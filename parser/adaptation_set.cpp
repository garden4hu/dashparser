#include "adaptation_set.h"

#include "drm.h"
#include "xml/dash_xml.h"
#include "mime.h"

namespace dash {
StatusCode AdaptationSet::ParseAdaptationSet(xmlNodePtr node) {
    id_ = getNodeProp(node,kPropID);

    return StatusCode::kOk;
}
}  // namespace dash
