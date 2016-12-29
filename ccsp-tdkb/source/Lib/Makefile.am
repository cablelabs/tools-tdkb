##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

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
libtdkagentssp_la_CPPFLAGS = -I/var/tmp/pc-rdkb/include/dbus-1.0 -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/board_sbapi -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/middle_layer_src -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/include  -I$(top_srcdir)/../../CcspMtaAgent/source/TR-181/board_sbapi -I$(top_srcdir)/../../CcspMtaAgent/source/TR-181/middle_layer_src -I$(top_srcdir)/../../CcspMtaAgent/source/TR-181/include -I$(top_srcdir)/../../CcspWifiAgent/source/TR-181/sbapi -I$(top_srcdir)/../../CcspWifiAgent/include/TR-181/ml -I$(top_srcdir)/../../CcspCMAgent/source/TR-181/include -I$(top_srcdir)/../../CcspPandM/source/TR-181/include -I$(top_srcdir)/../../CcspPandM/source/TR-181/middle_layer_src -I$(top_srcdir)/../../CcspPandM/source-pc/TR-181/middle_layer_src -I$(top_srcdir)/../../../rdkb/components/opensource/ccsp/CcspMtaAgent/source/TR-181/include -I$(top_srcdir)/../../../rdkb/components/opensource/ccsp/CcspPandM/source/TR-181/middle_layer_src -I$(top_srcdir)/../../../rdkb/components/opensource/ccsp/CcspPandM/source-pc/TR-181/middle_layer_src -I$(top_srcdir)/../../CcspPandM/source-pc/TR-181/board_include -I$(top_srcdir)/source/Custom $(CPPFLAGS)
libtdkagentssp_la_SOURCES = ssp_messagebus_interface.c ssp_tdk_mbus_wrp.c ssp_tdk_mbus_lib.c ssp_action.c ssp_main.c ssp_tdk_CosaCM_wrp.c ssp_tdk_wrp.c ssp_tdk_CosaMTA_wrp.c ssp_pam_bridge.c
if PLATFORM_ENABLED
libtdkagentssp_la_LDFLAGS =  -lccsp_common -lcm_mgnt -lcm_tr181 -lmta_tr181 -ltr181
endif
