/*  Copyright 2021-2022 MarcosHCK
 *  This file is part of dotdashair.
 *
 *  dotdashair is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dotdashair is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dotdashair.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <config.h>
#include <dda_application.h>

/*
 * Object definition
 *
 *
 */

struct _DdaApplication
{
  GApplication parent_instance;
};

struct _DdaApplicationClass
{
  GApplicationClass parent_class;
};

G_DEFINE_TYPE_WITH_CODE
(DdaApplication,
 dda_application,
 G_TYPE_APPLICATION,);

static void
dda_application_class_init(DdaApplicationClass* klass)
{
}

static void
dda_application_init(DdaApplication* self)
{
}
