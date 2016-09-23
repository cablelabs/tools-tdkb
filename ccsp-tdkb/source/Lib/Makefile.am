# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================

# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.

# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================

AM_CFLAGS = -D_ANSC_LINUX
AM_CFLAGS += -D_ANSC_USER
AM_CFLAGS += -D_ANSC_LITTLE_ENDIAN_
AM_LDFLAGS = -lccsp_common
AM_LDFLAGS += -lcm_mgnt
AM_LDFLAGS += -lcm_tr181
AM_LDFLAGS += -lmta_tr181
if PLATFORM_ENABLED
AM_LDFLAGS += -ltr181
endif
AM_CFLAGS += -DeRT=$(ERT_VALUE)
AM_CFLAGS += -Dplatform=$(PLATFORM_ENABLED)
AM_CPPFLAGS = -Wall
ACLOCAL_AMFLAGS = -I m4
hardware_platform = i686-linux-gnu
lib_LTLIBRARIES = libtdkagentssp.la
libtdkagentssp_la_CPPFLAGS = -I/var/tmp/pc-rdkb/include/dbus-1.0 -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/board_sbapi -I$(top_srcdir)/../..//CcspCMAgent/source/TR-181/middle_layer_src -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/include  -I$(top_srcdir)/../../CcspMtaAgent/source/TR-181/board_sbapi -I$(top_srcdir)/../..//CcspMtaAgent/source/TR-181/middle_layer_src -I$(top_srcdir)/../../CcspMtaAgent/source/TR-181/include -I$(top_srcdir)/../../CcspWifiAgent/source/TR-181/sbapi/ -I$(top_srcdir)/../../CcspWifiAgent/include/TR-181/ml/ -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/include/ -I$(top_srcdir)/../../CcspPandM/source/TR-181/include/ -I$(top_srcdir)/../../CcspPandM/source/TR-181/middle_layer_src/ -I$(top_srcdir)/../../CcspPandM/source-pc/TR-181/middle_layer_src -I$(top_srcdir)/source/Custom $(CPPFLAGS)
libtdkagentssp_la_SOURCES = ssp_messagebus_interface.c ssp_tdk_mbus_wrp.c ssp_tdk_mbus_lib.c ssp_action.c ssp_main.c ssp_tdk_CosaCM_wrp.c ssp_tdk_wrp.c ssp_tdk_CosaMTA_wrp.c ssp_pam_bridge.c
if PLATFORM_ENABLED
libtdkagentssp_la_LDFLAGS =  -lccsp_common -lcm_mgnt -lcm_tr181 -lmta_tr181 -ltr181
endif
