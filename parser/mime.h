#pragma once

#include <libxml/tree.h>

constexpr xmlChar kElemMpd[]                        = "MPD";
constexpr xmlChar kElemProgramInformation[]         = "ProgramInformation";
constexpr xmlChar kElemBaseURL[]                    = "BaseURL";
constexpr xmlChar kElemLocation[]                   = "Location";
constexpr xmlChar kElemPeriod[]                     = "Period";
constexpr xmlChar kElemMetrics[]                    = "EssentialMetrics";
constexpr xmlChar kElemEssentialProperty[]          = "EssentialProperty";
constexpr xmlChar kElemSupplementalProperty[]       = "SupplementalProperty";
constexpr xmlChar kElemUTCTiming[]                  = "UTCTiming";

// attributes in mpd
constexpr xmlChar kAttrID[]                         = "id";
constexpr xmlChar kAttrProfiles[]                   = "profiles";
constexpr xmlChar kAttrType[]                       = "type";
constexpr xmlChar kAttrAvailabilityStartTime[]      = "availabilityStartTime";
constexpr xmlChar kAttrPublishTime[]                = "publishTime";
constexpr xmlChar kAttrAvailabilityEndTime[]        = "availabilityEndTime";
constexpr xmlChar kAttrMediaPresentationDuration[]  = "mediaPresentationDuration";
constexpr xmlChar kAttrMinimumUpdatePeriod[]        = "minimumUpdatePeriod";
constexpr xmlChar kAttrMinBufferTime[]              = "minBufferTime";
constexpr xmlChar kAttrTimeShiftBufferDepth[]       = "timeShiftBufferDepth";
constexpr xmlChar kAttrSuggestedPresentationDelay[] = "suggestedPresentationDelay";
constexpr xmlChar kAttrMaxSegmentDuration[]         = "maxSegmentDuration";
constexpr xmlChar kAttrMaxSubsegmentDuration[]      = "maxSubsegmentDuration";