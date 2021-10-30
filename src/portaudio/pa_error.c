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
#include <glib-object.h>
#include <pa_error.h>

G_DEFINE_QUARK(pa-error-quark,
               pa_error);

GType
pa_gerror_get_type () G_GNUC_CONST;

static GEnumClass*
pa_error_get_class()
{
  static
  GEnumClass* klass = NULL;
  if G_UNLIKELY(klass == NULL)
  {
    GType g_type =
    pa_gerror_get_type ();

    klass =
    g_type_class_peek_static(g_type);
    if G_LIKELY(klass == NULL)
    {
      klass =
      g_type_class_ref(g_type);
      g_assert(klass != NULL);
    }
  }
return klass;
}

void
pa_error_propagate(GError** error,
                   PaError paer)
{
  g_return_if_fail(paer != paNoError);

  if(error != NULL)
  {
    GEnumValue* value =
    g_enum_get_value(pa_error_get_class(), paer);

    if(value != NULL)
      g_set_error
      (error,
       PA_ERROR,
       value->value,
       "%s: %s\r\n",
       value->value_nick,
       Pa_GetErrorText(paer));
    else
      g_set_error
      (error,
       PA_ERROR,
       PA_ERROR_FAILED,
       "Unknown error code %i (%s)\r\n",
       paer,
       Pa_GetErrorText(paer));
  }
}
