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
AM_CPPFLAGS = ${COPTS} -fPIC -DDEBUG_LEVEL_TRACE
AM_CXXFLAGS = -I${top_srcdir}/LMLite_Stub/include -I${top_srcdir}/agent/include -I${top_srcdir}/tdkb_lib/include
lib_LTLIBRARIES = liblmlitestub.la
liblmlitestub_la_SOURCES = src/LMLite_Stub.cpp
liblmlitestub_la_DEPENDENCIES= ${top_builddir}/tdkb_lib/.libs/libtdkagentssp.la
liblmlitestub_la_LIBADD =  $(liblmlitestub_la_DEPENDENCIES)
liblmlitestub_la_includedir = ${includedir}
liblmlitestub_la_include_HEADERS = ${top_srcdir}/LMLite_Stub/include/LMLite_Stub.h

