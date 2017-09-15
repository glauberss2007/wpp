//
// Created by Alan de Freitas on 16/06/17.
//

#ifndef WPP_HTTP_PARSER_ENUMS_H
#define WPP_HTTP_PARSER_ENUMS_H

/* Also update SONAME in the Makefile whenever you change these. */
const int WPP_HTTP_PARSER_VERSION_MAJOR = 2;
const int WPP_HTTP_PARSER_VERSION_MINOR = 3;
const int WPP_HTTP_PARSER_VERSION_PATCH = 0;

#include <sys/types.h>
#if defined(_WIN32) && !defined(__MINGW32__) && (!defined(_MSC_VER) || _MSC_VER<1600)
#include <BaseTsd.h>
#include <stddef.h>
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

/* Compile with -DHTTP_PARSER_STRICT=0 to make less checks, but run
 * faster
 */
#ifndef WPP_HTTP_PARSER_STRICT
# define WPP_HTTP_PARSER_STRICT 1
#endif

/* Maximium header size allowed. If the macro is not defined
 * before including this header then the default is used. To
 * change the maximum header size, define the macro in the build
 * environment (e.g. -DHTTP_MAX_HEADER_SIZE=<value>). To remove
 * the effective limit on the size of the header, define the macro
 * to a very large number (e.g. -DHTTP_MAX_HEADER_SIZE=0x7fffffff)
 */
#ifndef WPP_HTTP_MAX_HEADER_SIZE
# define WPP_HTTP_MAX_HEADER_SIZE (80*1024)
#endif

/* Request Methods */
#define WPP_HTTP_METHOD_MAP(WPP_XX)         \
  WPP_XX(0,  DELETE,      DELETE)       \
  WPP_XX(1,  GET,         GET)          \
  WPP_XX(2,  HEAD,        HEAD)         \
  WPP_XX(3,  POST,        POST)         \
  WPP_XX(4,  PUT,         PUT)          \
  /* pathological */                \
  WPP_XX(5,  CONNECT,     CONNECT)      \
  WPP_XX(6,  OPTIONS,     OPTIONS)      \
  WPP_XX(7,  TRACE,       TRACE)        \
  /* webdav */                      \
  WPP_XX(8,  COPY,        COPY)         \
  WPP_XX(9,  LOCK,        LOCK)         \
  WPP_XX(10, MKCOL,       MKCOL)        \
  WPP_XX(11, MOVE,        MOVE)         \
  WPP_XX(12, PROPFIND,    PROPFIND)     \
  WPP_XX(13, PROPPATCH,   PROPPATCH)    \
  WPP_XX(14, SEARCH,      SEARCH)       \
  WPP_XX(15, UNLOCK,      UNLOCK)       \
  /* subversion */                  \
  WPP_XX(16, REPORT,      REPORT)       \
  WPP_XX(17, MKACTIVITY,  MKACTIVITY)   \
  WPP_XX(18, CHECKOUT,    CHECKOUT)     \
  WPP_XX(19, MERGE,       MERGE)        \
  /* upnp */                        \
  WPP_XX(20, MSEARCH,     M-SEARCH)     \
  WPP_XX(21, NOTIFY,      NOTIFY)       \
  WPP_XX(22, SUBSCRIBE,   SUBSCRIBE)    \
  WPP_XX(23, UNSUBSCRIBE, UNSUBSCRIBE)  \
  /* RFC-5789 */                    \
  WPP_XX(24, PATCH,       PATCH)        \
  WPP_XX(25, PURGE,       PURGE)        \
  /* CalDAV */                      \
  WPP_XX(26, MKCALENDAR,  MKCALENDAR)   \

enum http_method
{
#define WPP_XX(num, name, string) HTTP_##name = num,
    WPP_HTTP_METHOD_MAP(WPP_XX)
#undef WPP_XX
};


enum http_parser_type { HTTP_REQUEST, HTTP_RESPONSE, HTTP_BOTH };


/* Flag values for http_parser.flags field */
enum flags
{ F_CHUNKED               = 1 << 0
    , F_CONNECTION_KEEP_ALIVE = 1 << 1
    , F_CONNECTION_CLOSE      = 1 << 2
    , F_TRAILING              = 1 << 3
    , F_UPGRADE               = 1 << 4
    , F_SKIPBODY              = 1 << 5
};


/* Map for errno-related constants
 *
 * The provided argument should be a macro that takes 2 arguments.
 */
#define WPP_HTTP_ERRNO_MAP(WPP_XX)                                           \
  /* No error */                                                     \
  WPP_XX(OK, "success")                                                  \
                                                                     \
  /* Callback-related errors */                                      \
  WPP_XX(CB_message_begin, "the on_message_begin callback failed")       \
  WPP_XX(CB_url, "the on_url callback failed")                           \
  WPP_XX(CB_header_field, "the on_header_field callback failed")         \
  WPP_XX(CB_header_value, "the on_header_value callback failed")         \
  WPP_XX(CB_headers_complete, "the on_headers_complete callback failed") \
  WPP_XX(CB_body, "the on_body callback failed")                         \
  WPP_XX(CB_message_complete, "the on_message_complete callback failed") \
  WPP_XX(CB_status, "the on_status callback failed")                     \
                                                                     \
  /* Parsing-related errors */                                       \
  WPP_XX(INVALID_EOF_STATE, "stream ended at an unexpected time")        \
  WPP_XX(HEADER_OVERFLOW,                                                \
     "too many header bytes seen; overflow detected")                \
  WPP_XX(CLOSED_CONNECTION,                                              \
     "data received after completed connection: close message")      \
  WPP_XX(INVALID_VERSION, "invalid HTTP version")                        \
  WPP_XX(INVALID_STATUS, "invalid HTTP status code")                     \
  WPP_XX(INVALID_METHOD, "invalid HTTP method")                          \
  WPP_XX(INVALID_URL, "invalid URL")                                     \
  WPP_XX(INVALID_HOST, "invalid host")                                   \
  WPP_XX(INVALID_PORT, "invalid port")                                   \
  WPP_XX(INVALID_PATH, "invalid path")                                   \
  WPP_XX(INVALID_QUERY_STRING, "invalid query string")                   \
  WPP_XX(INVALID_FRAGMENT, "invalid fragment")                           \
  WPP_XX(LF_EXPECTED, "WPP_LF character expected")                           \
  WPP_XX(INVALID_HEADER_TOKEN, "invalid character in header")            \
  WPP_XX(INVALID_CONTENT_LENGTH,                                         \
     "invalid character in content-length header")                   \
  WPP_XX(INVALID_CHUNK_SIZE,                                             \
     "invalid character in chunk size header")                       \
  WPP_XX(INVALID_CONSTANT, "invalid constant string")                    \
  WPP_XX(INVALID_INTERNAL_STATE, "encountered unexpected internal state")\
  WPP_XX(STRICT, "strict mode assertion failed")                         \
  WPP_XX(PAUSED, "parser is paused")                                     \
  WPP_XX(UNKNOWN, "an unknown error occurred")


/* Define HPE_* values for each errno value above */
#define WPP_HTTP_ERRNO_GEN(n, s) HPE_##n,
enum http_errno {
    WPP_HTTP_ERRNO_MAP(WPP_HTTP_ERRNO_GEN)
};
#undef WPP_HTTP_ERRNO_GEN


/* Get an http_errno value from an http_parser */
#define WPP_HTTP_PARSER_ERRNO(p)            ((enum http_errno) (p)->http_errno)

enum http_parser_url_fields
{ UF_SCHEMA           = 0
    , UF_HOST             = 1
    , UF_PORT             = 2
    , UF_PATH             = 3
    , UF_QUERY            = 4
    , UF_FRAGMENT         = 5
    , UF_USERINFO         = 6
    , UF_MAX              = 7
};


#endif //WPP_HTTP_PARSER_ENUMS_H
