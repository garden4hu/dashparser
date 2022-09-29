#pragma once

namespace dash {

// Role Schema ID Uri identifier
constexpr char kSchemaIdRole[]                   = "urn:mpeg:dash:role:2011";

// Period continuity signaling Schema ID Uri identifier
constexpr char kSchemaIdPeriodContinuity[]       = "urn:mpeg:dash:period-continuity:2015";

// Period connectivity signaling Schema ID Uri identifier
constexpr char kSchemaIdPeriodConnectivity[]     = "urn:mpeg:dash:period-connectivity:2015";

// switching across Adaptation Sets
constexpr char kSchemaIdAdaptationSetSwitching[] = "urn:mpeg:dash:adaptation-set-switching:2016";

// Preselection
constexpr char kSchemaIdPreselection[]           = "urn:mpeg:dash:preselection:2016";

// MPD reset indicator
constexpr char kSchemaIdReset[]                  = "urn:mpeg:dash:reset:2016";

/**
 * UTC Timing Schema ID Uri identifiers
 */
constexpr char kSchemaIdUTCTimingNTP[]           = "urn:mpeg:dash:utc:ntp:2014";
constexpr char kSchemaIdUTCTimingSNTP[]          = "urn:mpeg:dash:utc:sntp:2014";
constexpr char kSchemaIdUTCTimingHttpHead[]      = "urn:mpeg:dash:utc:http-head:2014";
constexpr char kSchemaIdUTCTimingHttpSxDate[]    = "urn:mpeg:dash:utc:http-xsdate:2014";
constexpr char kSchemaIdUTCTimingHttpISO[]       = "urn:mpeg:dash:utc:http-iso:2014";
constexpr char kSchemaIdUTCTimingHttpNTP[]       = "urn:mpeg:dash:utc:http-ntp:2014";
constexpr char kSchemaIdUTCTimingDirect[]        = "urn:mpeg:dash:utc:direct:2014";

/**
 * Events Schema ID Uri identifiers
 * Refer to https://dashif.org/identifiers/event_schemes/ for more details
 */
constexpr char kSchemaIdEventDASHSignalling[]    = "urn:mpeg:dash:event:2012";
constexpr char kSchemaIdEventDASHCallback[]      = "urn:mpeg:dash:event:callback:2015";
constexpr char kSchemaIdEventDVB[]               = "urn:dvb:iptv:cpm:2014";
constexpr char kSchemaIdEventSCTE[]              = "urn:scte:scte35:2013:xml";
constexpr char kSchemaIdEventDASHIF[]            = "https://dashif.org/identifiers/vast30";
constexpr char kSchemaIdEventETSI[]              = "urn:dvb:iptv:cpm:2014";
constexpr char kSchemaIdEventPresentationTermination[] = "urn:mpeg:dash:event:ttfn:2016";

/**
 * Content Rating Schema ID Uri identifiers
 */
constexpr char kSchemaIdContentRatingDVBGuidance[]         = "urn:dvb:iptv:guidance:2014";
constexpr char kSchemaIdContentRatingDVBRating[]           = "urn:dvb:iptv:rating:2014";

/**
 * Output Protection Schema ID Uri identifier
 */
constexpr char kSchemaIdOutputProtectionHDCP[] = "urn:mpeg:dash:output-protection:hdcp:2020";

/**
 * Subtitle and Closed Captioning Schema ID Uri identifiers
 */
constexpr char kSchemaIdClosedCaption[]        = "urn:scte:dash:cc:cea-608:2015";

/**
 * Audio Channel Configuration Schema ID Uri identifier
 */
constexpr char kSchemaIdAudioChannelConfigurationDASH[] =
    "urn:mpeg:dash:23003:3:audio_channel_configuration:2011";
constexpr char kSchemaIdAudioChannelConfigurationDolby[] =
    "tag:dolby.com,2014:dash:audio_channel_configuration:2011";

/**
 * Video Frame Packing Schema ID Uri identifiers
 */

// video component that conforms to ISO/IEC 14496-10. (ITU-T H.264)
constexpr char kSchemaIdVideoFramePackingISO14496[] =
    "urn:mpeg:dash:14496:10:frame_packing_arrangement_type:2011";
//  video component that conforms to ISO/IEC 13818-1. (ITU-T H.222)
constexpr char kSchemaIdVideoFramePackingISO13818[] =
    "urn:mpeg:dash:13818:1:stereo_video_format_type:2011";

// Generic Identifiers, For Representations based on ISO/IEC 14496-12
constexpr char kSchemaIdDRMISOFFMP4[]           = "urn:mpeg:dash:mp4protection:2011";
// Generic Identifiers, For Representations based on ISO/IEC 13818-1
constexpr char kSchemaIdDRMMPEG2TS[]            = "urn:mpeg:dash:13818:1:CA_descriptor:201";
// 3rd Party identifiers
// More detail refer to: https://dashif.org/identifiers/content_protection/
constexpr char kSchemaIdDRMClearKeyAES128[]     = "urn:uuid:3ea8778f-7742-4bf9-b18b-e834b2acbd47";
constexpr char kSchemaIdDRMClearKeySampleAES[]  = "urn:uuid:be58615b-19c4-4684-88b3-c8c57e99e957";
constexpr char kSchemaIdDRMClearKeyDashIF[]     = "urn:uuid:e2719d58-a985-b3c9-781a-b030af78d30e";
constexpr char kSchemaIdDRMGoogleWidevine[]     = "urn:uuid:edef8ba9-79d6-4ace-a3c8-27dcd51d21ed";
constexpr char kSchemaIdDRMMicrosoftPlayReady[] = "urn:uuid:9a04f079-9840-4286-ab92-e65be0885f95";
constexpr char kSchemaIdDRMAppleFairPlay[]      = "urn:uuid:94ce86fb-07ff-4f43-adb8-93d2fa968ca2";
constexpr char kSchemaIdDRMChinaDrm[]           = "urn:uuid:3d5e6d35-9b9a-41e8-b843-dd3c6e72c42c";

/**
 * Profile Schema ID Uri identifiers
 */

constexpr char kSchemaIdProfileISOFFVOD[]       = "urn:mpeg:dash:profile:isoff-on-demand:2011";
constexpr char kSchemaIdProfileISOFFExtVOD[]    = "urn:mpeg:dash:profile:isoff-ext-on-demand:2014";
constexpr char kSchemaIdProfileISOFFLIVE[]      = "urn:mpeg:dash:profile:isoff-live:2011";
constexpr char kSchemaIdProfileISOFFExtLIVE[]   = "urn:mpeg:dash:profile:isoff-ext-live:2014";
constexpr char kSchemaIdProfileISOFFMain[]      = "urn:mpeg:dash:profile:isoff-main:2011";
constexpr char kSchemaIdProfileISOFFCommon[]    = "urn:mpeg:dash:profile:isoff-common:2014";
constexpr char kSchemaIdProfileISOFFBroadCast[] = "urn:mpeg:dash:profile:isoff-broadcast:2015";
constexpr char kSchemaIdProfileMP2TMain[]       = "urn:mpeg:dash:profile:mp2t-main:2011";
constexpr char kSchemaIdProfileMP2TSimple[]     = "urn:mpeg:dash:profile:mp2t-simple:2011";

/**
 * Other Schema ID Uri identifiers
 */

// Spatial Relationship Description and dynamic srd
constexpr char kSchemaIdSRD[]                   = "urn:mpeg:dash:srd:2014";
constexpr char kSchemaIdSRDDynamic[]            = "urn:mpeg:dash:srd:dynamic:2016";

// indicating usage of the flexible insertion of URL query parameters
constexpr char kSchemaIdURLParam2014[]          = "rn:mpeg:dash:urlparam:2014";
constexpr char kSchemaIdURLParam2016[]          = "rn:mpeg:dash:urlparam:2016";

//  Open GOP resolution change
constexpr char kSchemaIdResolutionSwitching[]   = "urn:mpeg:dash:resolutionSwitching:2016";

}  // namespace dash
