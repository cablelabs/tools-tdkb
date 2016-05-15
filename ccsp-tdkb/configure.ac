# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================

# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.

# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================

#                                              -*- Autoconf -*-
# Process this file with autoconf to produce configure script.
#

AC_PREREQ([2.65])
AC_INIT([cm_tr181], [1.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
LT_INIT

AC_PREFIX_DEFAULT(`pwd`)
AC_ENABLE_SHARED
AC_DISABLE_STATIC

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_CC_C_O
AM_PROG_LIBTOOL(libtool)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC

ERT_VALUE=0

AC_ARG_ENABLE([ert],
        AS_HELP_STRING([--enable-ert],[enable ert]),
        [
          case "${enableval}" in
             yes) ERT_VALUE=1 ;;
           no) ERT_VALUE=0 ;;
          *) AC_MSG_ERROR([bad value ${enableval} for --enable-ert ]) ;;
           esac
           ],
         [echo "ert is enabled"])


AC_SUBST(ERT_VALUE)


AC_CONFIG_FILES(
        source/Lib/Makefile
	source/Makefile
	Makefile
)

AC_OUTPUT

