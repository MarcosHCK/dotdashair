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
#ifndef __DDA_SETTINGS__
#define __DDA_SETTINGS__ 1
#include <gio/gio.h>

#define DDA_TYPE_SETTINGS             (dda_settings_get_type ())
#define DDA_SETTINGS(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDA_TYPE_SETTINGS, DdaSettings))
#define DDA_SETTINGS_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_SETTINGS, DdaSettingsClass))
#define DDA_IS_SETTINGS(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDA_TYPE_SETTINGS))
#define DDA_IS_SETTINGS_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_SETTINGS))
#define DDA_SETTINGS_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_SETTINGS, DdaSettingsClass))

typedef struct _DdaSettings       DdaSettings;
typedef struct _DdaSettingsClass  DdaSettingsClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
dda_settings_get_type ();

DdaSettings*
dda_settings_new (const gchar    *directory,
                  GCancellable   *cancellable,
                  GError        **error);
DdaSettings*
dda_settings_get_default (void);
GSettingsSchema*
dda_settings_get_schema (DdaSettings *self,
                         const gchar *schema_id);
GSettings*
dda_settings_get_settings (DdaSettings *self,
                           const gchar *schema_id);
gboolean
dda_settings_has_key (DdaSettings *self,
                      const gchar *schema_id,
                      const gchar *key);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (DdaSettings, g_object_unref)

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_SETTINGS__
