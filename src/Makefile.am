# Copyright 2021-2023 MarcosHCK
# This file is part of dotdashair.
#
# dotdashair is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# dotdashair is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with dotdashair. If not, see <http://www.gnu.org/licenses/>.
#

# Keep sync with src/Makefile.am
schemasdir=${pkgdatadir}/schemas/

#
# Some variables
#

PACKAGE_NAME=@PACKAGE_NAME@
PACKAGE_RELEASE=@PACKAGE_RELEASE@
PACKAGE_VERSION_MAYOR=@PACKAGE_VERSION_MAYOR@
PACKAGE_VERSION_MINOR=@PACKAGE_VERSION_MINOR@
PACKAGE_VERSION_MICRO=@PACKAGE_VERSION_MICRO@
PACKAGE_VERSION_BUILD=@PACKAGE_VERSION_BUILD@

EXTRA_DIST=
VOID=

#
# Subdirectories
#

SUBDIRS=\
	vapi \
	$(VOID)

#
# C headers
#

EXTRA_DIST+=\
	dda_application.h \
	dda_stream.h \
	$(VOID)

#
# Binaries and libraries
#

pkglib_LTLIBRARIES=libddagio.la
bin_PROGRAMS=dotdashair

libddagio_la_SOURCES=\
	dda_stream.c \
	$(VOID)
libddagio_la_CFLAGS=\
	$(CGLM_CFLAGS) \
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	-DSCHEMASDIR=\"${schemasdir}\" \
	-DTOPBUILDDIR=\"${top_builddir}\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}\" \
	-D__DDA_GIO_INSIDE__=1 \
	-fstack-protector-strong \
	-funwind-tables \
	-Winline \
	-Wpacked \
	-Wimplicit-fallthrough \
	$(VOID)
libddagio_la_LIBADD=\
	$(CGLM_LIBS) \
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	$(VOID)
libddagio_la_LDFLAGS=\
	-rpath ${pkglibdir} \
	-release ${PACKAGE_RELEASE} \
	-version-info ${PACKAGE_VERSION_MAYOR}:${PACKAGE_VERSION_MINOR}:${PACKAGE_VERSION_MICRO} \
	$(VOID)

dotdashair_SOURCES=\
	dda_application.c \
	dda_main.c \
	$(VOID)
dotdashair_CFLAGS=\
	$(libddagio_la_CFLAGS) \
	$(VOID)
dotdashair_LDADD=\
	$(libddagio_la_LIBADD) \
	libddagio.la \
	$(VOID)

#
# Vala
#

VALA_PKG=\
	gio-2.0 \
	glib-2.0 \
	gobject-2.0 \
	$(VOID)

VALA_VAPIS=\
	config \
	dds \
	deus \
	$(VOID)

AM_VALAFLAGS=\
	--vapidir=vapi/ \
	--hide-internal \
	--abi-stability \
	-D DEBUG=${DEBUG} \
	-D DEVELOPER=${DEVELOPER} \
	$(addprefix --pkg , ${VALA_PKG}) \
	$(addprefix --pkg , ${VALA_VAPIS}) \
	$(VOID)
