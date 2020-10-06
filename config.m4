dnl $Id$
dnl config.m4 for extension h3

PHP_ARG_ENABLE([h3],
  [whether to enable h3 support],
  [AS_HELP_STRING([--enable-h3],
    [Enable h3 support])],
  [no])

if test -z "$PHP_DEBUG"; then
  AC_ARG_ENABLE(debug, [AS_HELP_STRING(--enable-debug)], [
    PHP_DEBUG=$enableval
  ], [
    PHP_DEBUG=no
  ])
fi

if test "$PHP_H3" != "no"; then
  PHP_ADD_INCLUDE(h3/src/h3lib/include)
  EXTRA_CFLAGS="-lh3 -std=c99 -Lh3/lib"
  PHP_SUBST(EXTRA_CFLAGS)
  PHP_SUBST(H3_SHARED_LIBADD)
  PHP_NEW_EXTENSION(h3, h3.c, $ext_shared)
fi
