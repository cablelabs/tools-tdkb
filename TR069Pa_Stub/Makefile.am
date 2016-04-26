ACLOCAL_AMFLAGS = -Im4 --install --coverage

AM_CPPFLAGS = -c ${COPTS} -fPIC 
AM_LDFLAGS = -ltdkagentssp
INCLUDES = -I${top_srcdir}/TR069_Pa_Stub/include -I${top_srcdir}/agent/include


AM_CXXFLAGS = --coverage -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/json \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/jsonrpc \
              -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)/curl \
              -I${top_srcdir}/TR069Pa_Stub/include -I${top_srcdir}/agent/include \
	      -I${PKG_CONFIG_SYSROOT_DIR}$(includedir)

lib_LTLIBRARIES = libTR069Pastub.la
libTR069Pastub_la_SOURCES = src/TR069Agent.cpp
libTR069Pastub_la_LDFLAGS = -ltdkagentssp

