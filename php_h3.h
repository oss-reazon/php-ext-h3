/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_H3_H
#define PHP_H3_H

#define PHP_H3_INVALID_INDEX 0
#define PHP_H3_MAX_RESOLUTION 15
#define PHP_H3_UNIT_KM 2
#define PHP_H3_UNIT_KM2 102
#define PHP_H3_UNIT_M 1
#define PHP_H3_UNIT_M2 101

extern zend_module_entry h3_module_entry;
#define phpext_h3_ptr &h3_module_entry

#define PHP_H3_VERSION "0.1.1"

#ifdef PHP_WIN32
#	define PHP_H3_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_H3_API __attribute__ ((visibility("default")))
#else
#	define PHP_H3_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif
typedef struct {
	double north;  ///< north latitude
	double south;  ///< south latitude
	double east;   ///< east longitude
	double west;   ///< west longitude
} BBox;

#if defined(ZTS) && defined(COMPILE_DL_H3)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
