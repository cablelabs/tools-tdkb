ACLOCAL_AMFLAGS = -Im4 --install --coverage

AM_CPPFLAGS = -c ${COPTS} -fPIC 
AM_LDFLAGS = -ltdkagentssp
INCLUDES = -I${PKG_CONFIG_SYSROOT_DIR}$(includedir) \
           -I${top_srcdir}/Mta_agent_Stub/include -I${top_srcdir}/tdk/agent/include

AM_CXXFLAGS = --coverage -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/json \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/jsonrpc \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/curl \
              -I${top_srcdir}/Mta_agent_Stub/include -I${top_srcdir}/agent/include -I${top_srcdir}/tdk/agent/include \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)

lib_LTLIBRARIES = libMta_agentstub.la
libMta_agentstub_la_SOURCES = src/MTA_Agent.cpp
libMta_agentstub_la_LDFLAGS = -ltdkagentssp
libMta_agentstub_la_includedir = ${includedir}
libMta_agentstub_la_include_HEADERS = ${top_srcdir}/Mta_agent_Stub/include/MTA_Agent.h

