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
#ifndef __DDA_MORSE_CONVERTER__
#define __DDA_MORSE_CONVERTER__
#include <dda_morse_charset.h>
#include <gio/gio.h>

/**
 * DDA_MORSE_CONVERTER_ERROR:
 *
 * Error domain for DDA_MORSE_CONVERTER. Errors in this domain will be from the #DdaMorseConverterError enumeration.
 * See #GError for more information on error domains.
 */
#define DDA_MORSE_CONVERTER_ERROR (dda_morse_converter_error_quark ())

/**
 * DdaMorseConverterError:
 * @DDA_MORSE_CONVERTER_ERROR_FAILED: generic error condition.
 * @DDA_MORSE_CONVERTER_ERROR_UNGUESSABLE_INPUT: unguessable input.
 * @DDA_MORSE_CONVERTER_ERROR_NOT_UTF8_INPUT: input data is not a valid UTF-8
 * sequence.
 * @DDA_MORSE_CONVERTER_ERROR_UNKNOWN_CHARACTER: unknown character present
 * on input, usually a not ASCII letter (remember morse code only defines
 * ASCII Latin code page).
 *
 * Error code returned by DdaMorseConverter API.
 * Note that %DDA_MORSE_CONVERTER_ERROR_FAILED is here only for compatibility with
 * error domain definition paradigm as defined on GLib documentation.
 */
typedef enum
{
  DDA_MORSE_CONVERTER_ERROR_FAILED,
  DDA_MORSE_CONVERTER_ERROR_UNGUESSABLE_INPUT,
  DDA_MORSE_CONVERTER_ERROR_NOT_UTF8_INPUT,
  DDA_MORSE_CONVERTER_ERROR_UNKNOWN_CHARACTER,
} DdaMorseConverterError;

#define DDA_TYPE_MORSE_CONVERTER_DIRECTION (dda_morse_converter_direction_get_type ())

/**
 * DdaMorseConverterDirection:
 * @DDA_MORSE_CONVERTER_DIRECTION_NONE: conversion direction is undefined (every state  will guess direction right from input).
 * @DDA_MORSE_CONVERTER_DIRECTION_CODE2CHAR: conversion direction is fixed from morse code to string.
 * @DDA_MORSE_CONVERTER_DIRECTION_CHAR2CODE: conversion direction is fixed from string to morse code.
 *
 * Set conversion direction between morse code and strings.
 */
typedef enum
{
  DDA_MORSE_CONVERTER_DIRECTION_NONE,
  DDA_MORSE_CONVERTER_DIRECTION_CODE2CHAR,
  DDA_MORSE_CONVERTER_DIRECTION_CHAR2CODE,
} DdaMorseConverterDirection;

#define DDA_TYPE_MORSE_CONVERTER            (dda_morse_converter_get_type ())
#define DDA_MORSE_CONVERTER(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), DDA_TYPE_MORSE_CONVERTER, DdaMorseConverter))
#define DDA_MORSE_CONVERTER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_MORSE_CONVERTER, DdaMorseConverterClass))
#define DDA_IS_MORSE_CONVERTER(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), DDA_TYPE_MORSE_CONVERTER))
#define DDA_IS_MORSE_CONVERTER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_MORSE_CONVERTER))
#define DDA_MORSE_CONVERTER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_MORSE_CONVERTER, DdaMorseConverterClass))

typedef struct _DdaMorseConverter       DdaMorseConverter;
typedef struct _DdaMorseConverterClass  DdaMorseConverterClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GQuark
dda_morse_converter_error_quark ();
GType
dda_morse_converter_get_type ();
GType
dda_morse_converter_direction_get_type ();

GConverter*
dda_morse_converter_new(DdaMorseConverterDirection direction,
                        DdaMorseCharset* charset);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (DdaMorseConverter, g_object_unref)

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_MORSE_CONVERTER__
