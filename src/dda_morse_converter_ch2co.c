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
#include <dda_macros.h>
#include <dda_morse_converter_private.h>

static GConverterResult
convert_char(DdaMorseConverter *self,
             gconstpointer      inbuf,
             gsize              n_inbuf,
             gpointer           outbuf,
             gsize              n_outbuf,
             gsize             *n_inbuf_read,
             gsize             *n_outbuf_wrote,
             GError           **error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  GString* partial = self->partial;
  GString* partial2 = self->partial2;
  const gchar *input, *last;
  const DdaMorseEntity* entity;
  gunichar char_;

/*
 * Validate input
 *
 */

  success =
  g_utf8_validate_len(inbuf, n_inbuf, &last);
  if G_UNLIKELY(success == FALSE)
  {
    g_set_error_literal
    (error,
     G_IO_ERROR,
     G_IO_ERROR_INVALID_DATA,
     "Invalid input data (not a UTF-8 sequence)");
     return G_CONVERTER_ERROR;
  }

/*
 * Convert
 *
 */

  for(input = inbuf;
      input != last && input[0] != '\0';
      input = g_utf8_next_char(input),
      (*n_inbuf_read)++)
  {
    char_ = g_utf8_get_char(input);

    entity =
    ds_morse_charset_get_entity_by_char(self->charset, char_);
    if G_UNLIKELY(entity == NULL)
    {
      g_set_error
      (&(self->partial_error[0]),
       DDA_MORSE_CONVERTER_ERROR,
       DDA_MORSE_CONVERTER_ERROR_UNKNOWN_CHARACTER,
       "Unknown character '0x%x'\r\n",
       char_);
      success =
      write_partial(self, outbuf, n_outbuf, n_outbuf_wrote, &tmp_err);
      if G_UNLIKELY(tmp_err != NULL)
      {
        g_propagate_error(error, tmp_err);
        push_partial_error(self);
        return G_CONVERTER_ERROR;
      }
      else
      {
        return G_CONVERTER_CONVERTED;
      }
    }
    else
    {
      if(input != inbuf)
      g_string_append_c(partial, ',');
      g_string_append_len(partial, entity->code, entity->n_code);
    }
  }

/*
 * Write output
 *
 */

  success =
  write_partial(self, outbuf, n_outbuf, n_outbuf_wrote, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    return G_CONVERTER_ERROR;
  }
return G_CONVERTER_CONVERTED;
}

GConverterResult
_dda_morse_conversor_char2code(DdaMorseConverter  *self,
                               gconstpointer       inbuf,
                               gsize               n_inbuf,
                               gpointer            outbuf,
                               gsize               n_outbuf,
                               GConverterFlags     flags,
                               gsize              *n_inbuf_read,
                               gsize              *n_outbuf_wrote,
                               GError            **error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  GConverterResult result;
  gboolean flush = FALSE;

  success =
  check_partial(self, outbuf, n_outbuf, n_outbuf_wrote, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    return G_CONVERTER_ERROR;
  }

  if(n_inbuf == 0)
  {
    if(   flags & G_CONVERTER_INPUT_AT_END
       || flags & G_CONVERTER_FLUSH)
    {
      flush = TRUE;
    }
    else
    {
      g_set_error_literal
      (error,
       G_IO_ERROR,
       G_IO_ERROR_PARTIAL_INPUT,
       "Incomplete string input");
      return G_CONVERTER_ERROR;
    }
  }

  if(flush)
  {
    success =
    write_partial(self, outbuf, n_outbuf, n_outbuf_wrote, &tmp_err);
    if G_UNLIKELY(tmp_err != NULL)
    {
      g_propagate_error(error, tmp_err);
      return G_CONVERTER_ERROR;
    }
  }
  else
  {
    result =
    convert_char(self, inbuf, n_inbuf, outbuf, n_outbuf, n_inbuf_read, n_outbuf_wrote, &tmp_err);
    if G_UNLIKELY(tmp_err != NULL)
    {
      g_propagate_error(error, tmp_err);
      return result;
    }
  }

_out_:
  result = G_CONVERTER_CONVERTED;
  if(flush && (flags & G_CONVERTER_INPUT_AT_END))
    result = G_CONVERTER_FINISHED;
  else
  if(flush && (flags & G_CONVERTER_FLUSH))
    result = G_CONVERTER_FLUSHED;
return result;
}
