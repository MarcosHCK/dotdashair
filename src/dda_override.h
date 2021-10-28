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
#ifndef __DDA_WINDOW_OVERRIDE__
#define __DDA_WINDOW_OVERRIDE__ 1
#include <gtk/gtk.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

#define goto_error() \
  G_STMT_START { \
    success = TRUE; \
    goto _error_; \
  } G_STMT_END
#define _g_object_unref0(var)     ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

static inline gchar*
_dda_textbox_convert(GConverter* converter, const gchar* text, gsize* size_p, GCancellable* cancellable, GError** error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  GOutputStream* process = NULL;
  GOutputStream* backend = NULL;
  glong size_ = -1;
  gpointer result = NULL;

  backend = g_memory_output_stream_new_resizable();
  process = g_converter_output_stream_new(backend, converter);
  size_ = g_utf8_strlen(text, -1);

  success =
  g_output_stream_write(process, text, size_, cancellable, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  success =
  g_output_stream_flush(process, cancellable, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    if(g_error_matches(tmp_err, G_IO_ERROR, G_IO_ERROR_PARTIAL_INPUT))
    {
      g_clear_error(&tmp_err);

      success =
      g_output_stream_write(process, ",", 1, cancellable, &tmp_err);
      if G_UNLIKELY(tmp_err != NULL)
      {
        g_propagate_error(error, tmp_err);
        goto_error();
      }

      success =
      g_output_stream_flush(process, cancellable, &tmp_err);
      if G_UNLIKELY(tmp_err != NULL)
      {
        g_propagate_error(error, tmp_err);
        goto_error();
      }
    }
    else
    {
      g_propagate_error(error, tmp_err);
      goto_error();
    }
  }

  success =
  g_output_stream_close(process, cancellable, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  success =
  g_output_stream_close(backend, cancellable, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  *size_p =
  g_memory_output_stream_get_data_size
  ((GMemoryOutputStream*)
   backend);
  result =
  g_memory_output_stream_steal_data
  ((GMemoryOutputStream*)
   backend);

_error_:
  _g_object_unref0(backend);
  _g_object_unref0(process);
return result;
}

#undef _g_object_unref0

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_WINDOW_OVERRIDE__
