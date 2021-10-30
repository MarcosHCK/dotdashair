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
# Enumerations
#

ENUM_FILES=\
	pa_error.h \
	$(VOID)

pa_enums.c: $(ENUM_FILES) pa_enums.c.template
	$(GLIB_MKENUMS) --symbol-prefix "pa" \
									--identifier-prefix "Pa" \
									--template "pa_enums.c.template" \
									--output $@ \
									$(ENUM_FILES)

#
# C headers
#

EXTRA_DIST+=\
	$(VOID)

#
# Binaries and libraries
#

noinst_LTLIBRARIES=libpabackend.la

libpabackend_la_SOURCES=\
	pa_backend.c \
	pa_backend_device.c \
	pa_enums.c \
	pa_error.c \
	$(VOID)
libpabackend_la_CFLAGS=\
	$(CGLM_CFLAGS) \
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(PORTAUDIO_CFLAGS) \
	-I.. \
	-DTOPBUILDDIR=\"${top_builddir}\" \
	-D__PA_BACKEND_INSIDE__=1 \
	-fstack-protector-strong \
	-funwind-tables \
	-Winline \
	-Wpacked \
	-Wimplicit-fallthrough \
	$(VOID)
libpabackend_la_LIBADD=\
	$(CGLM_LIBS) \
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	$(PORTAUDIO_LIBS) \
	$(VOID)
libpabackend_la_LDFLAGS=\
	-static \
	$(VOID)
