#pragma once
#include <libxml/tree.h>
xmlChar* kElemMpd                        = (xmlChar*)"MPD";
xmlChar* kElemProgramInformation         = (xmlChar*)"ProgramInformation";
xmlChar* kElemBaseURL                    = (xmlChar*)"BaseURL";
xmlChar* kElemLocation                   = (xmlChar*)"Location";
xmlChar* kElemPeriod                     = (xmlChar*)"Period";
xmlChar* kElemMetrics                    = (xmlChar*)"EssentialMetrics";
xmlChar* kElemEssentialProperty          = (xmlChar*)"EssentialProperty";
xmlChar* kElemSupplementalProperty       = (xmlChar*)"SupplementalProperty";
xmlChar* kElemUTCTiming                  = (xmlChar*)"UTCTiming";
xmlChar* kElemAdaptationSet              = (xmlChar*)"AdaptationSet";

// common attributes
xmlChar* kPropServiceLocation            = (xmlChar*)"serviceLocation";
xmlChar* kPropValue                      = (xmlChar*)"value";
xmlChar* kPropID                         = (xmlChar*)"id";
xmlChar* kPropType                       = (xmlChar*)"type";
xmlChar* kPropSchemeIdUri                = (xmlChar*)"schemeIdUri";
xmlChar* kPropStart                      = (xmlChar*)"start";
xmlChar* kPropDuration                   = (xmlChar*)"duration";
xmlChar* kPropWidth                      = (xmlChar*)"width";
xmlChar* kPropHeight                     = (xmlChar*)"height";
xmlChar* kPropSar                        = (xmlChar*)"sar";
xmlChar* kPropFrameRate                  = (xmlChar*)"frameRate";
xmlChar* kPropAudioSamplingRate          = (xmlChar*)"audioSamplingRate";
xmlChar* kPropMimeType                   = (xmlChar*)"mimeType";
xmlChar* kPropCodecs                   = (xmlChar*)"codecs";
xmlChar* kPropMaximumSAPPeriod                  = (xmlChar*)"maximumSAPPeriod";
xmlChar* kPropMaximumStartWithSAP                 = (xmlChar*)"startWithSAP";
xmlChar* kPropMaxPlayoutRate                 = (xmlChar*)"maxPlayoutRate";
xmlChar* kPropCodingDependency                = (xmlChar*)"codingDependency";

// BaseURL Attribute
xmlChar* kPropByteRange                  = (xmlChar*)"byteRange";

// attributes in mpd

xmlChar* kPropProfiles                   = (xmlChar*)"profiles";
xmlChar* kPropAvailabilityStartTime      = (xmlChar*)"availabilityStartTime";
xmlChar* kPropPublishTime                = (xmlChar*)"publishTime";
xmlChar* kPropAvailabilityEndTime        = (xmlChar*)"availabilityEndTime";
xmlChar* kPropMediaPresentationDuration  = (xmlChar*)"mediaPresentationDuration";
xmlChar* kPropMinimumUpdatePeriod        = (xmlChar*)"minimumUpdatePeriod";
xmlChar* kPropMinBufferTime              = (xmlChar*)"minBufferTime";
xmlChar* kPropTimeShiftBufferDepth       = (xmlChar*)"timeShiftBufferDepth";
xmlChar* kPropSuggestedPresentationDelay = (xmlChar*)"suggestedPresentationDelay";
xmlChar* kPropMaxSegmentDuration         = (xmlChar*)"maxSegmentDuration";
xmlChar* kPropMaxSubsegmentDuration      = (xmlChar*)"maxSubsegmentDuration";
