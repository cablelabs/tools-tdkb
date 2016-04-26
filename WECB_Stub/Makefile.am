## Copyright (c) 2013 Comcast. All rights reserved.

ACLOCAL_AMFLAGS = -Im4 --install
AM_LDFLAGS = -ltdkagentssp
AM_CPPFLAGS = ${COPTS} -fPIC -DDEBUG_LEVEL_TRACE

INCLUDES = -I${top_srcdir}/WECB_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${top_srcdir}/WECB_Stub/include -I${top_srcdir}/tdk/agent/include


lib_LTLIBRARIES = libwecbstub.la
libwecbstub_la_SOURCES = src/wecb.cpp
libwecbstub_la_LDFLAGS = -ltdkagentssp
libwecb_la_includedir = ${includedir}
