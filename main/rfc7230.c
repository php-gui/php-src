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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend.h"
//#include "zend_API.h"
//#include "zend_llist.h"
#include "zend_operators.h"

#include <string.h>

#include "rfc7230.h"


/**
 * @brief Tokens of the HTTP/0.9 CODE Status
 */
typedef enum _HttpStatusTokens {
    // The negative value reflet the status code
    /// 5xx server error
    /// 4xx client error
    /// 3xx redirection
    /// 2xx successful
    T_HTTP_200 = -201,// OK
    /// 1xx informational response
    T_HTTP_101 = -102,
    T_HTTP_100 = -101,
    T_HTTP_000 = -1,

    // In error case, positives value represente the unicode character
    // T_EOF = 0,
    // ...
} HttpStatusTokens;



/**
 * This function implement the RFC 7230( HTTP Status codes)
 * return a HttpStatusTokens if success else the char where error occured
 */
static int http_status_line_code_parse(const char *str, char **next)
{
    int code = -1;// Equ 000
    char *ptr = str;

    //TODO: use ZEND_IS_SPACE(*ptr);
    if (' '==ptr[0]) ptr++;
#if !defined(STRICT_RFC_7230) || !STRICT_RFC_7230
    while (ptr[0]==' ') ptr++;
#endif

    if (ZEND_IS_DIGIT(ptr[0])) {
        ++ptr;
        if (ZEND_IS_DIGIT(ptr[0])) {
            ++ptr;
            if (ZEND_IS_DIGIT(ptr[0])) {
                code -=   1 * (ptr[0]-'0');
                code -=  10 * (ptr[-1]-'0');
                code -= 100 * (ptr[-2]-'0');
                ++ptr;
                if (next) { *next=ptr;}
                return code;
            }
        }
    }
    //printf("Unexpecting char %c at column %d", ptr[0], ptr-str);
    // error{ php line/column, file, ..., str_column}

    return ptr[0];
}

/**
 * @brief Tokens of the HTTP protocol
 * The negative value reflet the protocol version.
 * value = -(version * 10 + 1)
 * In error case, positives value represente the unicode character
 * of the unexpected char
 */
typedef enum _HttpProtocolTokens {
    T_PROTOCOL_1_1 = -1020 -1,
    T_PROTOCOL_1_0 = -1010 -1,
    T_PROTOCOL_ERRORS = 0,
} HttpProtocolTokens;

/**
 * @brief Tokens of the HTTP protocol
 */
typedef enum _HttpNameTokens {
    T_PROTOCOL_HTTP = -1,
    T_PROTOCOL_HTTP_ERRORS = 0,
} HttpNameTokens;
/**
 * This function implement the RFC 7230( HTTP Status protocol/version)
 * @param str The string to scan
 * @param next if not null return a reference on the next
 * return a HttpProtocolTokens if success else the char where error occured
 */
static char http_status_line_protocol_name_scan(const char *str, char **next)
{
    char *ptr = str;

    //while (ptr[0]==' ') ptr++;//TODO: use ZEND_IS_SPACE(*ptr);

    if ('H'==ptr[0]) {
        ++ptr;
        if ('T'==ptr[0]) {
            ++ptr;
            if ('T'==ptr[0]) {
                ++ptr;
                if ('P'==ptr[0]) {
                    ++ptr;
                    if (next) { *next=ptr;}
                    return T_PROTOCOL_HTTP;
                }
            }
        }
    }
    printf("Unexpecting char %c at column %d", ptr[0], ptr-str);

    return ptr[0];
}

typedef enum _HttpVersionTokens {
    T_VERSION = -1,// HTTP/0.0
    T_VERSION_ERRORS = 0,
} HttpVersionTokens;
/**
 * reason-phrase  = *( HTAB / SP / VCHAR / obs-text )
 * @see https://datatracker.ietf.org/doc/html/rfc5234#appendix-B.1
 */
static char http_status_line_reason_phrase_scan(const char *str, char **next)
{
    char *ptr;

    for (ptr = str; ; ptr++) {
        // TODO: Create ZEND_IS_PRINTABLE()
        if ('\t'==ptr[0]
        ||   ' '==ptr[0]
        ||  ('!'<=ptr[0] && ptr[0]<='~')
        || (0x80<=ptr[0] && ptr[0]<=0xFF) ) {
            ptr++;
            continue;
        }
        break;
    };

    if (next) { *next=ptr;}

    return -1;
}

// @see /home/dev/Projets/tests/php-src/ext/mbstring/mbstring.c::php_mb_rfc1867_substring_conf
// to manage multibyte
http_status_error_t*
http_status_line_parse(const char *str,
                       http_status_line *status_line)
{
    http_status_error_t *error = NULL;
    char *next;
    char *ptr = str;
    char token;

    /// HTTP-version : "HTTP/" [0-9] "." [0-9]
    token = http_status_line_protocol_name_scan(ptr, &next);
    if (FAILURE<=token) {
        // Error
    }
    php_printf("%.*s\n", next-ptr, ptr);
    ptr = next;

    if ('/' != ptr[0]) {//TODO: create ZEND_IS_SLASH(ptr[0])
        // Error
    }
    ++ptr;

    if (ZEND_IS_DIGIT(ptr[0])) {
        status_line->protocol_version_major = ptr[0] - '0';// atoi()
        ++ptr;
    } else {
        // Error
    }

    if ('.' == ptr[0]) {//TODO: create ZEND_IS_DOT(ptr[0])
    } else {
        // Error
    }
    ++ptr;

    if (ZEND_IS_DIGIT(ptr[0])) {
        status_line->protocol_version_minor = ptr[0] - '0';// atoi()
        ++ptr;
    } else {
        // Error
    }
    php_printf("%d.%d\n", status_line->protocol_version_major, status_line->protocol_version_minor);

    ///SP : " "
    if (' ' != ptr[0]) {//TODO: create ZEND_IS_SPACE(ptr[0])
        // Error
    }
    ++ptr;


    ///status-code: [0-9]{3}
    int code = http_status_line_code_parse(ptr, &next);
    if (SUCCESS>=code) {
        ptr = next;
        //status_line.code = code*-1-1;
        status_line->code = ~code;//-201 => 200
        php_printf("%d\n", status_line->code);
    } else {
        // Error
        php_printf("Error\n");
    }

    //SP : " "
    if (' ' == ptr[0]) {//TODO: create ZEND_IS_SP(ptr[0])
    } else {
        // Error
    }
    ++ptr;

    ///reason-phrase: [20-FF]*
    char msg = http_status_line_reason_phrase_scan(ptr, &next);
    if (msg) {
        status_line->message = strndup(ptr, next-ptr+1);
        php_printf("%.*s\n", next-ptr, ptr);
        ptr = next;
    } else {
        // Error
    }

    ///CRLF: CR LF
    if ('\r' == ptr[0] && '\n' == ptr[1]) {//TODO: create ZEND_IS_CRLF(ptr[0])
        ptr += 2;
    } else if ('\n' == ptr[0]) {
        ++ptr;
    } else {
        // Error
        error = http_status_error_new();
    }

    return error;
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
