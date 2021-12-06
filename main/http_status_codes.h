/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | https://www.php.net/license/3_01.txt                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Andrea Faulds     <ajf@ajf.me>                               |
   +----------------------------------------------------------------------+
*/

#ifndef HTTP_STATUS_CODES_H
#define HTTP_STATUS_CODES_H



// @see get_status_string(int code)
typedef enum _HttpStatusCodes {
    HTTP_100=0, // "Continue"
    HTTP_101, // "Switching Protocols"
    HTTP_200, // "OK"
    HTTP_201, // "Created"
    HTTP_202, // "Accepted"
    HTTP_203, // "Non-Authoritative Information"
    HTTP_204, // "No Content"
    HTTP_205, // "Reset Content"
    HTTP_206, // "Partial Content"
    HTTP_300, // "Multiple Choices"
    HTTP_301, // "Moved Permanently"
    HTTP_302, // "Found"
    HTTP_303, // "See Other"
    HTTP_304, // "Not Modified"
    HTTP_305, // "Use Proxy"
    HTTP_307, // "Temporary Redirect"
    HTTP_308, // "Permanent Redirect"
    HTTP_400, // "Bad Request"
    HTTP_401, // "Unauthorized"
    HTTP_402, // "Payment Required"
    HTTP_403, // "Forbidden"
    HTTP_404, // "Not Found"
    HTTP_405, // "Method Not Allowed"
    HTTP_406, // "Not Acceptable"
    HTTP_407, // "Proxy Authentication Required"
    HTTP_408, // "Request Timeout"
    HTTP_409, // "Conflict"
    HTTP_410, // "Gone"
    HTTP_411, // "Length Required"
    HTTP_412, // "Precondition Failed"
    HTTP_413, // "Request Entity Too Large"
    HTTP_414, // "Request-URI Too Long"
    HTTP_415, // "Unsupported Media Type"
    HTTP_416, // "Requested Range Not Satisfiable"
    HTTP_417, // "Expectation Failed"
    HTTP_426, // "Upgrade Required"
    HTTP_428, // "Precondition Required"
    HTTP_429, // "Too Many Requests"
    HTTP_431, // "Request Header Fields Too Large"
    HTTP_451, // "Unavailable For Legal Reasons"},
    HTTP_500, // "Internal Server Error"
    HTTP_501, // "Not Implemented"
    HTTP_502, // "Bad Gateway"
    HTTP_503, // "Service Unavailable"
    HTTP_504, // "Gateway Timeout"
    HTTP_505, // "HTTP Version Not Supported"
    HTTP_506, // "Variant Also Negotiates"
    HTTP_511, // "Network Authentication Required"
    /* to allow search with while() loop */
    HTTP_0,


    /* sizeof */
    HTTP_NUM_CODES,
} HttpStatusCodes;

typedef struct _http_response_status_code_pair {
    const int code;
    const char *str;
} http_response_status_code_pair;

// @help synchronization with HttpStatusCodes enum
// @since C++20 and C99 support designated initializer
//#define HTTP_STATUS(code, msg) [HTTP_##code] = {code, msg}
#define HTTP_STATUS(code, msg) {code, msg}

static const http_response_status_code_pair http_status_map[HTTP_NUM_CODES] = {
    HTTP_STATUS(100, "Continue"),
    HTTP_STATUS(101, "Switching Protocols"),
    HTTP_STATUS(200, "OK"),
    HTTP_STATUS(201, "Created"),
    HTTP_STATUS(202, "Accepted"),
    HTTP_STATUS(203, "Non-Authoritative Information"),
    HTTP_STATUS(204, "No Content"),
    HTTP_STATUS(205, "Reset Content"),
    HTTP_STATUS(206, "Partial Content"),
    HTTP_STATUS(300, "Multiple Choices"),
    HTTP_STATUS(301, "Moved Permanently"),
    HTTP_STATUS(302, "Found"),
    HTTP_STATUS(303, "See Other"),
    HTTP_STATUS(304, "Not Modified"),
    HTTP_STATUS(305, "Use Proxy"),
    HTTP_STATUS(307, "Temporary Redirect"),
    HTTP_STATUS(308, "Permanent Redirect"),
    HTTP_STATUS(400, "Bad Request"),
    HTTP_STATUS(401, "Unauthorized"),
    HTTP_STATUS(402, "Payment Required"),
    HTTP_STATUS(403, "Forbidden"),
    HTTP_STATUS(404, "Not Found"),
    HTTP_STATUS(405, "Method Not Allowed"),
    HTTP_STATUS(406, "Not Acceptable"),
    HTTP_STATUS(407, "Proxy Authentication Required"),
    HTTP_STATUS(408, "Request Timeout"),
    HTTP_STATUS(409, "Conflict"),
    HTTP_STATUS(410, "Gone"),
    HTTP_STATUS(411, "Length Required"),
    HTTP_STATUS(412, "Precondition Failed"),
    HTTP_STATUS(413, "Request Entity Too Large"),
    HTTP_STATUS(414, "Request-URI Too Long"),
    HTTP_STATUS(415, "Unsupported Media Type"),
    HTTP_STATUS(416, "Requested Range Not Satisfiable"),
    HTTP_STATUS(417, "Expectation Failed"),
    HTTP_STATUS(426, "Upgrade Required"),
    HTTP_STATUS(428, "Precondition Required"),
    HTTP_STATUS(429, "Too Many Requests"),
    HTTP_STATUS(431, "Request Header Fields Too Large"),
    HTTP_STATUS(451, "Unavailable For Legal Reasons"),
    HTTP_STATUS(500, "Internal Server Error"),
    HTTP_STATUS(501, "Not Implemented"),
    HTTP_STATUS(502, "Bad Gateway"),
    HTTP_STATUS(503, "Service Unavailable"),
    HTTP_STATUS(504, "Gateway Timeout"),
    HTTP_STATUS(505, "HTTP Version Not Supported"),
    HTTP_STATUS(506, "Variant Also Negotiates"),
    HTTP_STATUS(511, "Network Authentication Required"),
    /* to allow search with while() loop */
    HTTP_STATUS(0, NULL)
};

static const size_t http_status_map_len = (sizeof(http_status_map) / sizeof(http_response_status_code_pair)) - 1;

#endif /* HTTP_STATUS_CODES_H */
