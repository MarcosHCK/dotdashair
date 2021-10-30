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
#ifndef __DDA_TEXTBOX__
#define __DDA_TEXTBOX__ 1
#include <gtk/gtk.h>

#define DDA_TYPE_TEXTBOX            (dda_textbox_get_type ())
#define DDA_TEXTBOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDA_TYPE_TEXTBOX, DdaTextbox))
#define DDA_TEXTBOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_TEXTBOX, DdaTextboxClass))
#define DDA_IS_TEXTBOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDA_TYPE_TEXTBOX))
#define DDA_IS_TEXTBOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_TEXTBOX))
#define DDA_TEXTBOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_TEXTBOX, DdaTextboxClass))

typedef struct _DdaTextbox        DdaTextbox;
typedef struct _DdaTextboxPrivate DdaTextboxPrivate;
typedef struct _DdaTextboxClass   DdaTextboxClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
dda_textbox_get_type () G_GNUC_CONST;

DdaTextbox*
dda_textbox_new (void);
DdaTextbox*
dda_textbox_new_with_label (const gchar* label);
DdaTextbox*
dda_textbox_new_with_markup (const gchar* label);
const gchar*
dda_textbox_get_label (DdaTextbox* self);
void
dda_textbox_set_label (DdaTextbox* self,
                       const gchar* value);
gboolean
dda_textbox_get_use_markup (DdaTextbox* self);
void
dda_textbox_set_use_markup (DdaTextbox* self,
                            gboolean value);
DdaMorseCharset*
dda_textbox_get_charset (DdaTextbox* self);
void
dda_textbox_set_charset (DdaTextbox* self,
                         DdaMorseCharset* value);
gboolean
dda_textbox_get_playing (DdaTextbox* self);
void
dda_textbox_set_playing (DdaTextbox* self,
                         gboolean value);
gboolean
dda_textbox_get_pause (DdaTextbox* self);
void
dda_textbox_set_pause (DdaTextbox* self,
                       gboolean value);

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_TEXTBOX__
