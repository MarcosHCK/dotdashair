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
#ifndef __DDA_SETTINGS_WINDOWS__
#define __DDA_SETTINGS_WINDOWS__
#include <gtk/gtk.h>

#define DDA_TYPE_SETTINGS_WINDOW            (dda_settings_window_get_type ())
#define DDA_SETTINGS_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDA_TYPE_SETTINGS_WINDOW, DdaSettingsWindow))
#define DDA_SETTINGS_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_SETTINGS_WINDOW, DdaSettingsWindowClass))
#define DDA_IS_SETTINGS_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDA_TYPE_SETTINGS_WINDOW))
#define DDA_IS_SETTINGS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_SETTINGS_WINDOW))
#define DDA_SETTINGS_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_SETTINGS_WINDOW, DdaSettingsWindowClass))

typedef struct _DdaSettingsWindow       DdaSettingsWindow;
typedef struct _DdaSettingsWindowClass  DdaSettingsWindowClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
dda_settings_window_get_type ();

DdaSettingsWindow*
dda_settings_window_new (void);

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_SETTINGS_WINDOWS__
