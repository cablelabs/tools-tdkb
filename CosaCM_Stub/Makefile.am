## Copyright (c) 2013 Comcast. All rights reserved.

ACLOCAL_AMFLAGS = -Im4 --install
AM_LDFLAGS = -ltdkagentssp
AM_CPPFLAGS = ${COPTS} -fPIC -DDEBUG_LEVEL_TRACE

INCLUDES = -I${top_srcdir}/CosaCM_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${top_srcdir}/CosaCM_Stub/include -I${top_srcdir}/agent/include


lib_LTLIBRARIES = libcosacmstub.la
libcosacmstub_la_SOURCES = src/CosaCM.cpp
libcosacmstub_la_LDFLAGS = -ltdkagentssp
