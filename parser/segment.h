#ifndef DASH_SEGMENT_H
#define DASH_SEGMENT_H

#pragma once

#include <optional>

#include "common_attributes_elements.h"

namespace dash {
class SegmentBase {
  public:
    SegmentBase()                                      = default;
    ~SegmentBase()                                     = default;
    SegmentBase(SegmentBase& segment)                  = default;
    SegmentBase(SegmentBase&& segment)                 = default;
    SegmentBase& operator=(const SegmentBase& segment) = default;
    SegmentBase& operator=(SegmentBase&& segment)      = default;

  private:
    int time_scale_               = 1;

    // specifies the presentation time offset of the Representation relative to the start of the
    // Period
    int presentation_time_offset_ = 0;

    int presentationDuration      = INT32_MAX;  // INT32_MAX is a invalid value

    // using for dynamic only. If present, it should not smaller than the timeShiftBufferDepth in
    // MPD level. If not present, it's the timeShiftBufferDepth in MPD level.
    int time_shift_buffer_depth_  = INT32_MAX;

    NumericalInterval index_range_;

    bool index_range_exact_          = false;  // must work with index_range_ if present

    // specifies an offset to define the adjusted segment availability time in ms.
    // The offset provides the time how much earlier these segments are available compared to their
    // computed availability start time for all Segments of all associated Representation.
    // If availability_time_offset_ is INT32_MIN, it means that all the segments are available since
    // MPD@availabilityStartTime.
    int availability_time_offset_    = INT32_MIN;

    // specifies if all Segments of all associated Representation are complete at the adjusted
    // availability start time. It works only with the presenting of availability_time_offset_.
    // Setting it to false indicates that the segment can be advance accessed.
    bool availability_time_complete_ = false;

    // specifies the URL including a possible byte range for the Initialization Segment.
    URLType initialization_;

    // specifies the URL including a possible byte range for the Representation Index Segment.
    URLType representation_index_;  // map to "sidx"
};
}  // namespace dash

#endif  // !DASH_SEGMENT_H