# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================

# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.

# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================

AM_CXXFLAGS = -DYOCTO_LIB_LOADING -DDEBUG_LEVEL_TRACE -DRDKVERSION="\"${RDK_VERSION}\"" $(GST_CFLAGS) $(GST_LIBS) $(AGENT_FLAGS) \
              -I./include/ -I${top_srcdir}/agent/include -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)

bin_PROGRAMS = rdk_tdk_agent_process
rdk_tdk_agent_processdir = ${bindir}
rdk_tdk_agent_process_SOURCES = src/agentmain.cpp src/rpcmethods.cpp
rdk_tdk_agent_process_SCRIPTS = scripts/runSysStat.sh scripts/TDK_version.txt scripts/RemoveLogs.sh scripts/file_copy.sh
rdk_tdk_agent_process_LDADD = -ljsoncpp -ljsonrpc-cpp -ldl -lpthread
rdk_tdk_agent_process_includedir = ${includedir}
