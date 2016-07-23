dnl                                               -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

dnl AC_PREREQ([2.69])
AC_INIT(tdk-b, 1.0, sabarinathp@tataelxsi.co.in,tdk-b)
AC_CONFIG_SRCDIR([CMAgent_stub/src/CMAgent.cpp])
AM_CONFIG_HEADER(cfg/config.h)
AC_CONFIG_MACRO_DIR([cfg])
AC_CONFIG_AUX_DIR([cfg])
AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-bzip2 subdir-objects 1.9])
LT_INIT

dnl subdirectories.

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_CPP
AC_PROG_CXXCPP

dnl use pretty build output with automake >= 1.11
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],
  [AM_DEFAULT_VERBOSITY=1
   AC_SUBST(AM_DEFAULT_VERBOSITY)])


dnl **********************************
dnl checks for dependencies
dnl **********************************
AC_HEADER_STDC

dnl Checks for header files.
AC_CHECK_HEADERS([limits.h memory.h stdlib.h string.h sys/socket.h unistd.h])

dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT8_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strdup strerror])

COPTS="-DDEBUG_LEVEL_TRACE"
AM_CXXFLAGS="$AM_CXXFLAGS -DDEBUG_LEVEL_TRACE"
AGENT_FLAGS=" "
RDK_VERSION="RDKB"
SUBDIR_HYBRID=" "
SUBDIR_CLIENT=" "



AC_SUBST(COPTS)
AC_SUBST(AGENT_FLAGS)
AC_SUBST(RDK_VERSION)
AC_SUBST(SUBDIR_HYBRID)
AC_SUBST(SUBDIR_CLIENT)
AC_CONFIG_FILES([Makefile
         cfg/Makefile
	 agent/Makefile
         CMAgent_stub/Makefile
	 WIFIAgent_stub/Makefile
	 MBUS_Stub/Makefile
	 WECB_Stub/Makefile
	 Mta_agent_Stub/Makefile
	 CosaCM_Stub/Makefile
         CosaMTA_Stub/Makefile
	 TR069Pa_Stub/Makefile
	 AdvancedConfig_stub/Makefile
	 SNMP_PA_Stub/Makefile])
AC_OUTPUT
