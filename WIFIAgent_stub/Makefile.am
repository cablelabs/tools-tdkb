## Copyright (c) 2013 Comcast. All rights reserved.

ACLOCAL_AMFLAGS = -Im4 --install
AM_LDFLAGS = -ltdkagentssp
AM_CPPFLAGS = ${COPTS} -fPIC -DDEBUG_LEVEL_TRACE

INCLUDES = -I${top_srcdir}/WIFIAgent_stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${top_srcdir}/WIFIAgent_stub/include -I${top_srcdir}/agent/include


lib_LTLIBRARIES = libwifiagentstub.la
libwifiagentstub_la_SOURCES = src/WIFIAgent.cpp
libwifiagentstub_la_LDFLAGS = -ltdkagentssp
libwifiagentstub_la_includedir = ${includedir}
libwifiagentstub_la_include_HEADERS = ${top_srcdir}/WIFIAgent_stub/include/WIFIAgent.h
