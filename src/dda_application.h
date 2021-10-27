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
#ifndef __DDA_APPLICATION__
#define __DDA_APPLICATION__ 1
#include <gio/gio.h>

/**
 * DDA_APPLICATION_ERROR:
 *
 * Error domain for DDA_APPLICATION. Errors in this domain will be from the #DdaApplicationError enumeration.
 * See #GError for more information on error domains.
 */
#define DDA_APPLICATION_ERROR (dda_application_error_quark())

/**
 * DdaApplicationError:
 * @DDA_APPLICATION_ERROR_FAILED: generic error condition.
 * @DDA_APPLICATION_ERROR_GSETTINGS_INIT: main settings initialization error.
 *
 * Error code returned by DdaApplication API.
 * Note that %DDA_APPLICATION_ERROR_FAILED is here only for compatibility with
 * error domain definition paradigm as defined on GLib documentation.
 */
typedef enum
{
  DDA_APPLICATION_ERROR_FAILED,
  DDA_APPLICATION_ERROR_GSETTINGS_INIT,
} DdaApplicationError;

#define DDA_TYPE_APPLICATION             (dda_application_get_type())
#define DDA_APPLICATION(object)          (G_TYPE_CHECK_INSTANCE_CAST((object), DDA_TYPE_APPLICATION, DdaApplication))
#define DDA_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), DDA_TYPE_APPLICATION, DdaApplicationClass))
#define DDA_IS_APPLICATION(object)       (G_TYPE_CHECK_INSTANCE_TYPE((object), DDA_TYPE_APPLICATION))
#define DDA_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), DDA_TYPE_APPLICATION))
#define DDA_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), DDA_TYPE_APPLICATION, DdaApplicationClass))

typedef struct _DdaApplication        DdaApplication;
typedef struct _DdaApplicationPrivate DdaApplicationPrivate;
typedef struct _DdaApplicationClass   DdaApplicationClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
dda_application_error_quark ();
GType
dda_application_get_type ();

G_DEFINE_AUTOPTR_CLEANUP_FUNC (DdaApplication, g_object_unref)

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_APPLICATION__
