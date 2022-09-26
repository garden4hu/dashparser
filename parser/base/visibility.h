#ifndef VISIBILITY_H_
#define VISIBILITY_H_

#ifdef DASH_PARSER_ENABLE_EXPORT

#if defined(_WIN32) || defined(_WINDOWS) || defined(WIN32) || defined(_MSC_VER)
#define DASH_PARSER_EXPORT __declspec(dllexport)
#else
#define DASH_PARSER_EXPORT __declspec(dllimport)
#endif

#else // !DASH_PARSER_EXPORT
#if __has_attribute(visibility)
#define DASH_PARSER_EXPORT __attribute__((visibility("default")))
#endif

#endif // DASH_PARSER_ENABLE_EXPORT


#ifndef DASH_PARSER_EXPORT
#define DASH_PARSER_EXPORT
#endif

#endif // !VISIBILITY_H_