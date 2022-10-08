#pragma once

#include <deque>
#include <optional>

#include "common_attributes_elements.h"

namespace dash {

struct SegmentBaseInformation {
    int time_scale_               = 1;

    // specifies the presentation time offset of the Representation relative to the start of the
    // Period
    int presentation_time_offset_ = 0;

    int64_t presentationDuration_ = INT64_MAX;  // INT32_MAX is a invalid value

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

class SegmentBase : public SegmentBaseInformation {
  public:
    SegmentBase()  = default;
    ~SegmentBase() = default;

  public:
    void getType() {}
};

class SegmentList : public SegmentBaseInformation {
  public:
    SegmentList()                              = default;
    ~SegmentList()                             = default;
    SegmentList& operator=(const SegmentList&) = default;

  private:
    class SegmentURL {
      public:
        SegmentURL()  = default;
        ~SegmentURL() = default;
        optional<std::string> media_;
        optional<NumericalInterval> media_range_;
        optional<std::string> index_;
        optional<NumericalInterval> index_range_;
    };
    std::vector<std::unique_ptr<SegmentURL>> segments_;
};

struct SegmentTimeLineUnit {
    int64_t segment_time_ = 0;
    int64_t duration_     = 0;  // in the timescale
};

class SegmentTemplate : public SegmentBaseInformation {
  public:
    SegmentTemplate()                                  = default;
    ~SegmentTemplate()                                 = default;
    SegmentTemplate& operator=(const SegmentTemplate&) = default;

  private:
    // specifies the constant approximate Segment duration, if present
    int64_t duration_ = INT64_MAX;

    // specifies the number of the first Media Segment in this Representation in the Period
    int start_number_ = 1;

    // specifies the template to create the Media Segment List
    optional<std::string> media_;

    // specifies the template to create the Index Segment List
    optional<std::string> index_;

    // specifies the template to create the Initialization Segment
    optional<std::string> initialization_segment_;

    // specifies the template to create the Bitstream Switching Segment
    optional<std::string> bitstream_switching_;

    std::deque<std::unique_ptr<SegmentTimeLineUnit>> segment_time_line_units_;
};
}  // namespace dash
