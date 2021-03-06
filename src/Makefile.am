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
schemasdir=${pkgdatadir}/schemas

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
	portaudio \
	resources \
	vapi \
	$(VOID)

#
# C headers
#

EXTRA_DIST+=\
	dda_application.h \
	dda_backend.h \
	dda_input_stream.h \
	dda_macros.h \
	dda_morse_charset.h \
	dda_morse_converter.h \
	dda_morse_converter_private.h \
	dda_output_stream.h \
	dda_override.h \
	dda_settings.h \
	dda_settings_window.h \
	dda_streams.h \
	dda_window.h \
	$(VOID)

#
# Binaries and libraries
#

pkglib_LTLIBRARIES=libddagio.la libddaaudio.la
bin_PROGRAMS=dotdashair

libddaaudio_la_SOURCES=\
	dda_backend.vala \
	dda_streams.vala \
	$(VOID)
libddaaudio_la_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	-DTOPBUILDDIR=\"${top_builddir}\" \
	-D__DDA_AUDIO_INSIDE__=1 \
	-fstack-protector-strong \
	-funwind-tables \
	-Winline \
	-Wpacked \
	-Wimplicit-fallthrough \
	$(VOID)
libddaaudio_la_LIBADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	portaudio/libpabackend.la \
	$(VOID)
libddaaudio_la_LDFLAGS=\
	-rpath ${pkglibdir} \
	-release ${PACKAGE_RELEASE} \
	-version-info ${PACKAGE_VERSION_MAYOR}:${PACKAGE_VERSION_MINOR}:${PACKAGE_VERSION_MICRO} \
	$(VOID)

libddagio_la_SOURCES=\
	dda_morse_charset.c \
	dda_morse_converter.c \
	dda_morse_converter_ch2co.c \
	dda_morse_converter_co2ch.c \
	$(VOID)
libddagio_la_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	-DTOPBUILDDIR=\"${top_builddir}\" \
	-D__DDA_GIO_INSIDE__=1 \
	-fstack-protector-strong \
	-funwind-tables \
	-Winline \
	-Wpacked \
	-Wimplicit-fallthrough \
	$(VOID)
libddagio_la_LIBADD=\
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
	dda_infobar.vala \
	dda_settings.vala \
	dda_settings_window.vala \
	dda_textbox.vala \
	dda_window.vala \
	$(VOID)
dotdashair_CFLAGS=\
	$(GIO_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(GOBJECT_CFLAGS) \
	$(GTK_CLAGS) \
	-DLOCALEDIR=\"${localedir}\" \
	-DSCHEMASDIR=\"${schemasdir}\" \
	-DGAPPNAME=\"org.hck.${PACKAGE_NAME}\" \
	-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\" \
	-DGRESNAME=\"/org/hck/${PACKAGE_NAME}\" \
	-D__DDA_GUI_INSIDE__=1 \
	$(GTK_CFLAGS) \
	$(VOID)
dotdashair_LDADD=\
	$(GIO_LIBS) \
	$(GLIB_LIBS) \
	$(GOBJECT_LIBS) \
	$(GTK_LIBS) \
	resources/libbundle.la \
	libddaaudio.la \
	libddagio.la \
	$(VOID)

#
# Vala
#

AM_VALAFLAGS=\
	--vapidir=vapi/ \
	--hide-internal \
	--abi-stability \
	--pkg config \
	--pkg dda \
	-D DEBUG=${DEBUG} \
	-D DEVELOPER=${DEVELOPER} \
	--gresources "${top_builddir}/src/resources/dda_resources.gresources.xml" \
	$(VOID)
