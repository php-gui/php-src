/*
+----------------------------------------------------------------------+
| PHP Version 8                                                        |
+----------------------------------------------------------------------+
| Copyright (c) 1997-2021 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: No Name                                                      |
+----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_RFC_7230_H
#define PHP_RFC_7230_H

//#define ENABLE_STRICT_RFC_7230 1
#undef ENABLE_STRICT_RFC_7230

/**
 * @brief The http_status_line struct hold a representation of
 * HTTP Status-line
 * @see   https://datatracker.ietf.org/doc/html/rfc7230#section-3.1.2
 */
struct _http_status_line {
    short http_version;
    char  protocol_name[16];
    short protocol_version_major;
    short protocol_version_minor;
    short code;
    char  str_code[4];// 3DIGIT null-terminated
    char  message[60];
};
typedef struct _http_status_line http_status_line;// see sapi_header_

/**
 * @brief Hold error parsing
 */
typedef struct _http_status_error_t {
    int   domain;
    int   code;
    char *message;
} http_status_error_t;

/**
 * @brief Parse status line
 * status-line = HTTP-version SP status-code SP reason-phrase CRLF
 * @see   https://datatracker.ietf.org/doc/html/rfc7230#section-3.2.
 * @see   https://datatracker.ietf.org/doc/html/rfc5234#appendix-B.1
 * @param str
 * @param end Indicate the next char. Only set if SUCCESS
 * @param status_line
 * @param error nullable.
 * @return 0 if SUCCESS else a new pointer to the error
 * @since 8.1
 */
http_status_error_t *http_status_line_parse(const char *str, http_status_line *status_line);

/**
 * @brief The http_header_fields struct hold a representation of HTTP Header Fields
 * @see   https://datatracker.ietf.org/doc/html/rfc7230#section-3.2.
 * @todo: implementation
 */


#endif	/* PHP_RFC_7230_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
