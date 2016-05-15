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

AM_CPPFLAGS = -c ${COPTS} -fPIC 
AM_LDFLAGS = -ltdkagentssp
INCLUDES = -I${top_srcdir}/TR069_Pa_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/json \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/jsonrpc \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/curl \
              -I${top_srcdir}/TR069Pa_Stub/include -I${top_srcdir}/agent/include \
	      -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)

lib_LTLIBRARIES = libTR069Pastub.la
libTR069Pastub_la_SOURCES = src/TR069Agent.cpp
libTR069Pastub_la_LDFLAGS = -ltdkagentssp

