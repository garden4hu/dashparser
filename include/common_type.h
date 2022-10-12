#pragma once

enum RoleType {
    DASH_ROLE_MAIN,           // primary audio and video
    DASH_ROLE_SUPPLEMENTARY,  // supplementary audio and video of main content
    DASH_ROLE_CAPTION,        // caption
    DASH_ROLE_SUBTITLE,       // subtitle
    DASH_ROLE_SIGN,           // a sign-language interpretation of an audio  component
    DASH_ROLE_ALTERNATE,      // alternative to (a) main media content
    DASH_ROLE_METADATA,       // application  specific
    DASH_ROLE_DESCRIPTION,    // Textual or audio media component containing a textual description
    DASH_ROLE_COMMENTARY,     // commentary information
    DASH_ROLE_DUB,            // a different language from  the original
    DASH_ROLE_EMERGENCY,      // provide emergency information
    DASH_ROLE_ENHANCED_AUDIO_INTELLIGIBILITY,  // for improved intelligibility of the dialogue
};

enum UTCTimingServerType {

    DASH_UTC_TIMING_SERVER_NTP,           // ntp based timing server
    DASH_UTC_TIMING_SERVER_SNTP,          // sntp based timing server
    DASH_UTC_TIMING_SERVER_HTTP_HEAD,     // http head based timing server
    DASH_UTC_TIMING_SERVER_HTTP_XS_DATE,  // http xs-date based timing server
    DASH_UTC_TIMING_SERVER_HTTP_NTP,      // http NTP based timing server
    DASH_UTC_TIMING_SERVER_HTTP_ISO,      // http ISO based timing server
    DASH_UTC_TIMING_SERVER_DIRECT,        // direct based timing server
};

/**
 * DRM Type
 * Refer to : https://dashif.org/identifiers/content_protection/
 */
enum DRMType {
    DASH_DRM_DASH_MP4,
    DASH_DRM_DASH_CA,
    DASH_DRM_CLEAR_AES_128,
    DASH_DRM_CLEAR_SAMPLE_AES,
    DASH_DRM_DASH_IF,
    DASH_DRM_GOOGLE_WIDEVINE,
    DASH_DRM_MICROSOFT_PLAYREADY,
    DASH_DRM_APPLE_FAIRPLAY,
    DASH_DRM_CHINA_DRM,
};

/**
 *
 */

enum AudioChannelConfigurationType {
    // Refer to ISO/IEC 23009-1.  The channel configuration as defined by Table 68 of ISO/IEC
    // 23003-3.
    DASH_AUDIO_CHANNEL_CONFIG_DASH,
    // Dolby audio channel configuration information. The 16 bit value refer to table E.5 in ETSI TS
    // 102 366
    // https://www.etsi.org/deliver/etsi_ts/102300_102399/102366/01.02.01_60/ts_102366v010201p.pdf
    DASH_AUDIO_CHANNEL_CONFIG_Dolby,
};

enum MediaType {
    AUDIO,
    VIDEO,
    SUBTITLE,
    CLOSED_CAPTION,
};