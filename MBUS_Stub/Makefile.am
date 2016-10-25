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

ACLOCAL_AMFLAGS = -Im4 --install
AM_LDFLAGS = -ltdkagentssp
AM_CPPFLAGS = ${COPTS} -fPIC -DDEBUG_LEVEL_TRACE

INCLUDES = -I${top_srcdir}/MBUS_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${top_srcdir}/MBUS_Stub/include -I${top_srcdir}/agent/include


lib_LTLIBRARIES = libccspcommon_mbusstub.la
libccspcommon_mbusstub_la_SOURCES = src/CCSPMBUS_Stub.cpp
libccspcommon_mbusstub_la_LDFLAGS = -ltdkagentssp
libccspcommon_mbus_la_includedir = ${includedir}
