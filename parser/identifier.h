#ifndef DASH_IDENTIFIER_H
#define DASH_IDENTIFIER_H

namespace dash {

/**
 * Role Schema ID Uri identifier
 */
constexpr char kSchemaIdUriRole[]                     = "urn:mpeg:dash:role:2011";

/**
 * UTC Timing Schema ID Uri identifiers
 */
constexpr char kSchemaIdUriUTCTimingNTP[]             = "urn:mpeg:dash:utc:ntp:2014";
constexpr char kSchemaIdUriUTCTimingSNTP[]            = "urn:mpeg:dash:utc:sntp:2014";
constexpr char kSchemaIdUriUTCTimingHttpHead[]        = "urn:mpeg:dash:utc:http-head:2014";
constexpr char kSchemaIdUriUTCTimingHttpSxDate[]      = "urn:mpeg:dash:utc:http-xsdate:2014";
constexpr char kSchemaIdUriUTCTimingHttpISO[]         = "urn:mpeg:dash:utc:http-iso:2014";
constexpr char kSchemaIdUriUTCTimingHttpNTP[]         = "urn:mpeg:dash:utc:http-ntp:2014";
constexpr char kSchemaIdUriUTCTimingDirect[]          = "urn:mpeg:dash:utc:direct:2014";

/**
 * Events Schema ID Uri identifiers
 * Refer to https://dashif.org/identifiers/event_schemes/ for more details
 */
constexpr char kSchemaIdUriEventDASH[]                = "urn:mpeg:dash:event:2012";
constexpr char kSchemaIdUriEventDVB[]                 = "urn:dvb:iptv:cpm:2014";
constexpr char kSchemaIdUriEventSCTE[]                = "urn:scte:scte35:2013:xml";
constexpr char kSchemaIdUriEventDASHIF[]              = "https://dashif.org/identifiers/vast30";
constexpr char kSchemaIdUriEventETSI[]                = "urn:dvb:iptv:cpm:2014";

/**
 * Content Rating Schema ID Uri identifiers
 */
constexpr char kSchemaIdUriContentRatingDVBGuidance[] = "urn:dvb:iptv:guidance:2014";
constexpr char kSchemaIdUriContentRatingDVBRating[]   = "urn:dvb:iptv:rating:2014";

/**
 * Output Protection Schema ID Uri identifier
 */
constexpr char kSchemaIdUriOutputProtectionHDCP[]     = "urn:mpeg:dash:output-protection:hdcp:2020";

/**
 * Subtitle and Closed Captioning Schema ID Uri identifiers
 */
constexpr char kSchemaIdUriClosedCaption[]            = "urn:scte:dash:cc:cea-608:2015";

/**
 * Audio Channel Configuration Schema ID Uri identifier
 */
constexpr char kSchemaIdUriAudioChannelConfigurationDASH[] =
    "urn:mpeg:dash:23003:3:audio_channel_configuration:2011";
constexpr char kSchemaIdUriAudioChannelConfigurationDolby[] =
    "tag:dolby.com,2014:dash:audio_channel_configuration:2011";

/**
 * Video Frame Packing Schema ID Uri identifiers
 */

// video component that conforms to ISO/IEC 14496-10. (ITU-T H.264)
constexpr char kSchemaIdUriVideoFramePackingISO14496[] =
    "urn:mpeg:dash:14496:10:frame_packing_arrangement_type:2011";
//  video component that conforms to ISO/IEC 13818-1. (ITU-T H.222)
constexpr char kSchemaIdUriVideoFramePackingISO13818[] =
    "urn:mpeg:dash:13818:1:stereo_video_format_type:2011";

// Generic Identifiers, For Representations based on ISO/IEC 14496-12
constexpr char kDrmProviderIBMFFMP4[]           = "urn:mpeg:dash:mp4protection:2011";
// Generic Identifiers, For Representations based on ISO/IEC 13818-1
constexpr char kDrmProviderMPEG2TS[]           = "urn:mpeg:dash:13818:1:CA_descriptor:201";
// 3rd Party identifiers
// More detail refer to: https://dashif.org/identifiers/content_protection/
constexpr char kDrmProviderClearKeyAES128[]     = "urn:uuid:3ea8778f-7742-4bf9-b18b-e834b2acbd47";
constexpr char kDrmProviderClearKeySampleAES[]  = "urn:uuid:be58615b-19c4-4684-88b3-c8c57e99e957";
constexpr char kDrmProviderClearKeyDashIF[]     = "urn:uuid:e2719d58-a985-b3c9-781a-b030af78d30e";
constexpr char kDrmProviderGoogleWidevine[]     = "urn:uuid:edef8ba9-79d6-4ace-a3c8-27dcd51d21ed";
constexpr char kDrmProviderMicrosoftPlayReady[] = "urn:uuid:9a04f079-9840-4286-ab92-e65be0885f95";
constexpr char kDrmProviderAppleFairPlay[]      = "urn:uuid:94ce86fb-07ff-4f43-adb8-93d2fa968ca2";
constexpr char kDrmProviderChinaDrm[]           = "urn:uuid:3d5e6d35-9b9a-41e8-b843-dd3c6e72c42c";
}  // namespace dash

#endif  // !DASH_IDENTIFIER_H