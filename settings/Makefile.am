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
charsetsdir=${pkgdatadir}/charsets

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
# Charsets
#

charsets_DATA=\
	default_charset.cfg \
	$(VOID)

#
# Schemas
#

SCHEMAS_CLFAGS=\
	-D "CHARSETSDIR=${charsetsdir}" \
	$(VOID)

SUFFIXES=.xml.in .xml

.xml.in.xml:
	m4 $(SCHEMAS_CLFAGS) $< > $@

#
# GSettings cache
#

SCHEMAS=\
	org.hck.dotdashair.gschema.xml \
	$(VOID)

schemas_DATA=\
	gschemas.compiled \
	$(SCHEMAS) \
	$(VOID)

gschemas.compiled: $(SCHEMAS)
	$(GLIB_COMPILE_SCHEMAS) ${top_builddir}/settings/

CLEANFILES=\
	gschemas.compiled \
	org.hck.dotdashair.gschema.xml \
	$(VOID)
