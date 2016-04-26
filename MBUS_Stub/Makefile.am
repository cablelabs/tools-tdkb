## Copyright (c) 2013 Comcast. All rights reserved.

ACLOCAL_AMFLAGS = -Im4 --install
AM_LDFLAGS = -ltdkagentssp
AM_CPPFLAGS = ${COPTS} -fPIC -DDEBUG_LEVEL_TRACE

INCLUDES = -I${top_srcdir}/MBUS_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${top_srcdir}/MBUS_Stub/include -I${top_srcdir}/agent/include


lib_LTLIBRARIES = libccspcommon_mbusstub.la
libccspcommon_mbusstub_la_SOURCES = src/CCSPMBUS_Stub.cpp
libccspcommon_mbusstub_la_LDFLAGS = -ltdkagentssp
libccspcommon_mbus_la_includedir = ${includedir}
