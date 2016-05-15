# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================

# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.

# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================

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
