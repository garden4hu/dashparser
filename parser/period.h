#ifndef DASH_PERIOD_H
#define DASH_PERIOD_H
#pragma once

#include <optional>
#include <string>
#include <list>
using std::optional;

namespace dash {
class BaseURL;
class SegmentBase;
class SegmentList;
class SegmentTemplate;
class AssetIdentifier;
class EventStream;
class AdaptationSet;
class Subset;
class SupplementalProperty;
class EmptyAdaptationSet;
class GroupLabel;
class PreSelection;


/**
 * @brief There are 3 kind of period:
 * 1. Regular Period; 2. Early Available Period; 3. Early Terminated Period.
 * period type 1/3: if the start attribute is presented, PeriodStart equal to it.
 * period type 1/3: the start attribute is absent in current period, say it as i,
 *                  but the previous period(i-1) contains a duration attribute.
 *                  PeriodStart(i) = PeriodStart(i-1) + Period(i-1)'s duration.
 * period type 1/3: if (1) The start attribute is absent,
 *                     (2) current period is the first,
 *                     (3) mpd's type is "static", then PeriodStart = 0
 * period type 3:   if (1) duration attribute is present, and
 *                     (2)the next period start attribute or minimumUpdatePeriod element is present.
 * period type 2:   if (1) start attribute is absent,
 *                     (2) the previous period does not contain a duration attribute,
 *                     (3) mpd's type is "dynamic"
 *
 *
 *  |-period-|-period-|...|-period-|
 *  |                     |
 *  PeriodStart(0)        PeriodStart(n)
 *
 */

class Period {
public:
    optional<std::string> id_;
    // if present, is PeriodStart. Or refer to the brief above.
    optional<int32_t> start_;
    optional<int32_t> duration_;
    bool bit_stream_switching_ = false;

    std::list<BaseURL> base_url_;
    optional<SegmentBase> segment_bases_;
    optional<SegmentList> segment_lists_;
    optional<SegmentTemplate> segment_template_;
    optional<AssetIdentifier> asset_identifier_;
    std::list<EventStream> event_streams_;
    std::list<AdaptationSet> adaptation_sets_;
    std::list<Subset> subsets_;
    std::list<SupplementalProperty> supplemental_properties_;
    std::list<EmptyAdaptationSet> empty_adaptation_sets_;
    std::list<GroupLabel> group_labels_;
    std::list<PreSelection> pre_selections_;
};
}

#endif  // !DASH_PERIOD_H
