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
#ifndef __DDA_MORSE_CONVERTER_PRIVATE__
#define __DDA_MORSE_CONVERTER_PRIVATE__
#include <dda_morse_converter.h>

typedef GConverterResult (*MorseConversor) (DdaMorseConverter  *self,
                                            const void         *inbuf,
                                            gsize               inbuf_size,
                                            void               *outbuf,
                                            gsize               outbuf_size,
                                            GConverterFlags     flags,
                                            gsize              *bytes_read,
                                            gsize              *bytes_written,
                                            GError            **error);

struct _DdaMorseConverter
{
  GObject parent_instance;

  /*<private>*/
  DdaMorseCharset* charset;                       /* charset helper                                               */
  DdaMorseConverterDirection direction;           /* default conversion direction                                 */
  gboolean suppress_unknown_code_error;           /* self explicative                                             */

  /*<private>*/
  MorseConversor conversor;                       /* conversion function for current direction                    */
  GString* partial;                               /* partial data storage                                         */
  GString* partial2;                              /* partial data storage used by code to char routine            */
  GError* partial_error[2];                       /* partial errors (note that converter architecture makes my    */
                                                  /* delay in-conversion error throwing until all internal state  */
                                                  /* is flushed, process which may throw an error for it own)     */
};

struct _DdaMorseConverterClass
{
  GObjectClass parent_class;

  /*<private>*/
  GRegex* ltt2mrs;
  GRegex* mrschck;
};

#define push_partial_error(self) \
  G_STMT_START { \
    if((self)->partial_error[0] == NULL) \
      g_warning("(%s: %i): pushing a non existent error\r\n", G_STRFUNC, __LINE__); \
    if((self)->partial_error[1] != NULL) \
    { \
      g_warning("(%s: %i): there was an error already on error stack\r\n", G_STRFUNC, __LINE__); \
      _g_error_free0((self)->partial_error[1]); \
    } \
    (self)->partial_error[1] = g_steal_pointer(&( (self)->partial_error[0] )); \
  } G_STMT_END
#define pop_partial_error(self) \
  G_STMT_START { \
    if((self)->partial_error[1] == NULL) \
      g_warning("(%s: %i): poping a non existent error\r\n", G_STRFUNC, __LINE__); \
    if((self)->partial_error[0] != NULL) \
    { \
      g_warning("(%s: %i): there was an error already on error stack\r\n", G_STRFUNC, __LINE__); \
      _g_error_free0((self)->partial_error[0]); \
    } \
    (self)->partial_error[0] = g_steal_pointer(&( (self)->partial_error[1] )); \
  } G_STMT_END
#define has_partial_error(self, level) \
  (G_UNLIKELY ((self)->partial_error[(level)] != NULL))
#define get_partial_error(self, level) \
  (g_steal_pointer(&( (self)->partial_error[(level)] )))
#define propagate_partial_error(self, level) \
  G_STMT_START { \
    g_propagate_error(error, get_partial_error(self, level)); \
  } G_STMT_END

#if __cplusplus
extern "C" {
#endif // __cplusplus

G_GNUC_INTERNAL
GConverterResult
_dda_morse_conversor_char2code(DdaMorseConverter  *self,
                               gconstpointer       inbuf,
                               gsize               n_inbuf,
                               gpointer            outbuf,
                               gsize               n_outbuf,
                               GConverterFlags     flags,
                               gsize              *n_inbuf_read,
                               gsize              *n_outbuf_wrote,
                               GError            **error);
G_GNUC_INTERNAL
GConverterResult
_dda_morse_conversor_code2char(DdaMorseConverter  *self,
                               gconstpointer       inbuf,
                               gsize               n_inbuf,
                               gpointer            outbuf,
                               gsize               n_outbuf,
                               GConverterFlags     flags,
                               gsize              *n_inbuf_read,
                               gsize              *n_outbuf_wrote,
                               GError            **error);

static gboolean inline
write_partial(DdaMorseConverter  *self,
              gpointer            outbuf,
              gsize               n_outbuf,
              gsize              *n_outbuf_wrote,
              GError            **error)
{
  GString* partial = NULL;
  partial = self->partial;

  if(partial->len > 0)
  {
    if(partial->len > n_outbuf)
    {
      g_set_error_literal
      (error,
       G_IO_ERROR,
       G_IO_ERROR_NO_SPACE,
       "Not enough space!\r\n");
      return FALSE;
    }
    else
    {
      gsize sz = partial->len;
      memcpy(outbuf, partial->str, sz);
      g_string_erase(partial, 0, sz);
      *n_outbuf_wrote = sz;
    }
  }
return TRUE;
}

static gboolean inline
check_partial(DdaMorseConverter  *self,
              gpointer            outbuf,
              gsize               n_outbuf,
              gsize              *n_outbuf_wrote,
              GError            **error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;

  if(has_partial_error(self, 1))
  {
    success =
    write_partial(self, outbuf, n_outbuf, n_outbuf_wrote, &tmp_err);
    if G_UNLIKELY(tmp_err != NULL)
    {
      g_propagate_error(error, tmp_err);
      return success;
    }
    else
    {
      pop_partial_error(self);
      return success;
    }
  }

  if(has_partial_error(self, 0))
  {
    propagate_partial_error(self, 0);
    return FALSE;
  }
return TRUE;
}

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_MORSE_CONVERTER_PRIVATE__
