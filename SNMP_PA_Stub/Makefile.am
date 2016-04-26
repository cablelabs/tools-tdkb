ACLOCAL_AMFLAGS = -Im4 --install

AM_LDFLAGS = -ltdkagentssp
AM_CPPFLAGS = -c -Wall -shared ${COPTS} -fPIC

INCLUDES = -I${top_srcdir}/SNMP_PA_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = -I${top_srcdir}/SNMP_PA_Stub/include -I${top_srcdir}/agent/include




lib_LTLIBRARIES = libSNMP_PAstub.la
libSNMP_PAstub_la_SOURCES = src/SNMPProtocolAgent.cpp
libSNMP_PAstub_la_LDFLAGS = -ltdkagentssp
libSNMP_PAstub_la_includedir = ${includedir}
libSNMP_PAstub_la_include_HEADERS = ${top_srcdir}/SNMP_PA_Stub/include/SNMPProtocolAgent.h

