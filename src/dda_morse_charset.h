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
#ifndef __DDA_MORSE__
#define __DDA_MORSE__
#include <gio/gio.h>

/**
 * DDA_MORSE_CHARSET_ERROR:
 *
 * Error domain for DDA_MORSE_CHARSET. Errors in this domain will be from the #DdaMorseCharsetError enumeration.
 * See #GError for more information on error domains.
 */
#define DDA_MORSE_CHARSET_ERROR (dda_morse_charset_error_quark ())

/**
 * DdaMorseCharsetError:
 * @DDA_MORSE_CHARSET_ERROR_FAILED: generic error condition.
 * @DDA_MORSE_CHARSET_ERROR_CHARACTER_TOO_LONG: key file key longer then one character.
 *
 * Error code returned by DdaMorseCharset API.
 * Note that %DDA_MORSE_CHARSET_ERROR_FAILED is here only for compatibility with
 * error domain definition paradigm as defined on GLib documentation.
 */
typedef enum
{
  DDA_MORSE_CHARSET_ERROR_FAILED,
  DDA_MORSE_CHARSET_ERROR_CHARACTER_TOO_LONG,
} DdaMorseCharsetError;

#define DDA_TYPE_MORSE_CHARSET            (dda_morse_charset_get_type ())
#define DDA_MORSE_CHARSET(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), DDA_TYPE_MORSE_CHARSET, DdaMorseCharset))
#define DDA_MORSE_CHARSET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_MORSE_CHARSET, DdaMorseCharsetClass))
#define DDA_IS_MORSE_CHARSET(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), DDA_TYPE_MORSE_CHARSET))
#define DDA_IS_MORSE_CHARSET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_MORSE_CHARSET))
#define DDA_MORSE_CHARSET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_MORSE_CHARSET, DdaMorseCharsetClass))

typedef struct _DdaMorseCharset       DdaMorseCharset;
typedef struct _DdaMorseCharsetClass  DdaMorseCharsetClass;
typedef struct _DdaMorseEntity        DdaMorseEntity;

/*
 * Morse code goes as:
 * - '.' represents a dot (I din't expect that!)
 * - '-' represents a dash (This keep surprising me)
 * - ',' represents an space between characters (Ok, this is weird, but there isn't another way)
 * - ' ' represents an space between words (Same than above, life is tough)
 *
 * Remenber:
 * - char prefix is used for any morse stuff (like ".-")
 * - code prefix is used for any string stuff (like "a")
 *
 *
 */

typedef gunichar DdaMorseChar;
typedef gchar   *DdaMorseCode;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
dda_morse_charset_error_quark ();
GType
dda_morse_charset_get_type ();

struct _DdaMorseEntity
{
  const DdaMorseChar char_;
  const DdaMorseCode code;
  gsize n_code;
};

DdaMorseCharset*
dda_morse_charset_new(GFile* charset_file, GCancellable* cancellable, GError** error);
const DdaMorseEntity*
ds_morse_charset_get_entity_by_char (DdaMorseCharset* morse, DdaMorseChar char_);

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_MORSE__
