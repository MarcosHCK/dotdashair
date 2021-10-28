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
#include <dda_morse_charset.h>
#include <dda_morse_converter.h>
#include <dda_morse_converter_private.h>

G_DEFINE_QUARK(dda-morse-converter-error-quark,
               dda_morse_converter_error);

#define _g_regex_unref0(var) ((var == NULL) ? NULL : (var = (g_regex_unref (var), NULL)))

static void
dda_morse_converter_g_converter_iface_init(GConverterIface* iface);

/*
 * Enumeration types
 *
 */

GType
dda_morse_converter_direction_get_type ()
{
  static volatile
  gsize g_enum_type_id__volatile;
  if (g_once_init_enter (&g_enum_type_id__volatile))
  {
    static const
    GEnumValue values[] =
    {
      {DDA_MORSE_CONVERTER_DIRECTION_NONE, "DDA_MORSE_CONVERTER_DIRECTION_NONE", "none"},
      {DDA_MORSE_CONVERTER_DIRECTION_CODE2CHAR, "DDA_MORSE_CONVERTER_DIRECTION_CODE2CHAR", "code2char"},
      {DDA_MORSE_CONVERTER_DIRECTION_CHAR2CODE, "DDA_MORSE_CONVERTER_DIRECTION_CHAR2CODE", "char2code"},
      { 0, NULL, NULL }
    };

    GType g_enum_type_id =
    g_enum_register_static(g_intern_static_string("DdaMorseConverterDirection"), values);
    g_once_init_leave (&g_enum_type_id__volatile, g_enum_type_id);
  }
return g_enum_type_id__volatile;
}

/*
 * Object definition
 *
 */

enum
{
  prop_0,
  prop_direction,
  prop_charset,
  prop_suppress_unknown_code_error,
  prop_number,
};

static
GParamSpec* properties[prop_number] = {0};

G_DEFINE_TYPE_WITH_CODE
(DdaMorseConverter,
 dda_morse_converter,
 G_TYPE_OBJECT,
 G_IMPLEMENT_INTERFACE
 (G_TYPE_CONVERTER,
  dda_morse_converter_g_converter_iface_init));

static GConverterResult
dda_morse_converter_g_converter_iface_convert(GConverter       *pself,
                                              gconstpointer     inbuf,
                                              gsize             n_inbuf,
                                              gpointer          outbuf,
                                              gsize             n_outbuf,
                                              GConverterFlags   flags,
                                              gsize            *n_inbuf_read,
                                              gsize            *n_outbuf_wrote,
                                              GError          **error)
{
  DdaMorseConverter* self = DDA_MORSE_CONVERTER(pself);
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  const gchar *input, *last;
  gunichar unichar;

  if G_UNLIKELY(self->charset == NULL)
  {
    g_set_error_literal
    (error,
     G_IO_ERROR,
     G_IO_ERROR_NOT_INITIALIZED,
     "Install a charset first");
    g_warning
    ("Install a charset first\r\n");
    return G_CONVERTER_ERROR;
  }

/*
 * Do some work
 *
 */

#define step() \
  return self->conversor(self, inbuf, n_inbuf, outbuf, n_outbuf, flags, n_inbuf_read, n_outbuf_wrote, error);

  if(self->conversor == NULL)
  {
    const guint     n_guess_chars = 4;
          gunichar  guess_chars[n_guess_chars];

    if(n_inbuf < n_guess_chars)
    {
      g_set_error_literal
      (error,
       DDA_MORSE_CONVERTER_ERROR,
       DDA_MORSE_CONVERTER_ERROR_UNGUESSABLE_INPUT,
       "Input too short to guess format");
      goto_error();
    }
    else
    {
      success =
      g_utf8_validate_len(inbuf, n_guess_chars, &last);
      if G_UNLIKELY(success == FALSE)
      {
        g_set_error_literal
        (error,
         G_IO_ERROR,
         G_IO_ERROR_INVALID_DATA,
         "Invalid input data (not a UTF-8 sequence)");
        return G_CONVERTER_ERROR;
      }

      for(input = inbuf;
          input != NULL && input != last;
          input = g_utf8_next_char(input))
      {
        unichar = g_utf8_get_char(input);
        if(!( unichar == L'.'
           || unichar == L'-'
           || unichar == L','
           || unichar == L' '))
        {
          self->conversor = _dda_morse_conversor_char2code;
          step();
        }
      }

      self->conversor = _dda_morse_conversor_code2char;
      step();
    }
  }
  else
  {
    step();
  }

#undef step

_error_:
return success;
}

static void
dda_morse_converter_g_converter_iface_reset(GConverter* pself)
{
  DdaMorseConverter* self = DDA_MORSE_CONVERTER(pself);

  if(   has_partial_error(self, 0)
     || has_partial_error(self, 1))
  {
    g_warning("(%s: %i): partial error left when resetting converter state\r\n", G_STRFUNC, __LINE__);
    _g_error_free0(self->partial_error[0]);
    _g_error_free0(self->partial_error[1]);
  }

  g_string_erase(self->partial, 0, self->partial->len);
  g_string_erase(self->partial2, 0, self->partial2->len);

  switch(self->direction)
  {
  case DDA_MORSE_CONVERTER_DIRECTION_NONE:
    self->conversor = NULL;
    break;
  case DDA_MORSE_CONVERTER_DIRECTION_CODE2CHAR:
    self->conversor = _dda_morse_conversor_code2char;
    break;
  case DDA_MORSE_CONVERTER_DIRECTION_CHAR2CODE:
    self->conversor = _dda_morse_conversor_char2code;
    break;
  }
}

static void
dda_morse_converter_g_converter_iface_init(GConverterIface* iface)
{
  iface->convert = dda_morse_converter_g_converter_iface_convert;
  iface->reset = dda_morse_converter_g_converter_iface_reset;
}

static void
dda_morse_converter_class_set_property(GObject* pself, guint prop_id, const GValue* value, GParamSpec* pspec)
{
  DdaMorseConverter* self = DDA_MORSE_CONVERTER(pself);

  switch(prop_id)
  {
  case prop_direction:
    self->direction = g_value_get_enum(value);
    break;
  case prop_charset:
    dda_morse_converter_set_charset(self, g_value_get_object(value));
    break;
  case prop_suppress_unknown_code_error:
    self->suppress_unknown_code_error = g_value_get_boolean(value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(pself, prop_id, pspec);
    break;
  }
}

static void
dda_morse_converter_class_constructed(GObject* pself)
{
  G_OBJECT_CLASS(dda_morse_converter_parent_class)->constructed(pself);
  DdaMorseConverterClass* klass = DDA_MORSE_CONVERTER_GET_CLASS(pself);
  DdaMorseConverter* self = DDA_MORSE_CONVERTER(pself);

  if G_UNLIKELY(klass->ltt2mrs == NULL)
  {
    GError* tmp_err = NULL;

    klass->ltt2mrs =
    g_regex_new(".", G_REGEX_DOTALL, 0, &tmp_err);
    if G_UNLIKELY(tmp_err != NULL)
    {
      g_critical
      ("(%s: %i): %s: %i: %s\r\n",
       G_STRFUNC,
       __LINE__,
       g_quark_to_string(tmp_err->domain),
       tmp_err->code,
       tmp_err->message);
      _g_regex_unref0(klass->ltt2mrs);
      _g_error_free0(tmp_err);
      g_assert_not_reached();
    }
  }

  if G_UNLIKELY(klass->mrschck == NULL)
  {
    GError* tmp_err = NULL;

    klass->mrschck =
    g_regex_new(".", G_REGEX_DOTALL, 0, &tmp_err);
    if G_UNLIKELY(tmp_err != NULL)
    {
      g_critical
      ("(%s: %i): %s: %i: %s\r\n",
       G_STRFUNC,
       __LINE__,
       g_quark_to_string(tmp_err->domain),
       tmp_err->code,
       tmp_err->message);
      _g_regex_unref0(klass->mrschck);
      _g_error_free0(tmp_err);
      g_assert_not_reached();
    }
  }

  dda_morse_converter_g_converter_iface_reset(G_CONVERTER(self));
}

static void
dda_morse_converter_class_finalize(GObject* pself)
{
  DdaMorseConverter* self = DDA_MORSE_CONVERTER(pself);

  g_string_free(self->partial, TRUE);

  guint count_ =
  g_type_get_instance_count(G_TYPE_FROM_INSTANCE(pself));
  if G_UNLIKELY(count_ == 0)
  {
    DdaMorseConverterClass* klass =
    DDA_MORSE_CONVERTER_GET_CLASS(pself);

    _g_regex_unref0(klass->ltt2mrs);
    _g_regex_unref0(klass->mrschck);
  }

G_OBJECT_CLASS(dda_morse_converter_parent_class)->finalize(pself);
}

static void
dda_morse_converter_class_dispose(GObject* pself)
{
  DdaMorseConverter* self = DDA_MORSE_CONVERTER(pself);
  dda_morse_converter_g_converter_iface_reset(G_CONVERTER(self));
G_OBJECT_CLASS(dda_morse_converter_parent_class)->dispose(pself);
}

static void
dda_morse_converter_class_init(DdaMorseConverterClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS(klass);

  oclass->set_property = dda_morse_converter_class_set_property;
  oclass->constructed = dda_morse_converter_class_constructed;
  oclass->finalize = dda_morse_converter_class_finalize;
  oclass->dispose = dda_morse_converter_class_dispose;

  properties[prop_direction] =
    g_param_spec_enum
    (_TRIPLET("direction"),
     DDA_TYPE_MORSE_CONVERTER_DIRECTION,
     DDA_MORSE_CONVERTER_DIRECTION_NONE,
     G_PARAM_WRITABLE
     | G_PARAM_CONSTRUCT_ONLY
     | G_PARAM_STATIC_STRINGS);

  properties[prop_charset] =
    g_param_spec_object
    (_TRIPLET("charset"),
     DDA_TYPE_MORSE_CHARSET,
     G_PARAM_WRITABLE
     | G_PARAM_CONSTRUCT
     | G_PARAM_STATIC_STRINGS);

  properties[prop_suppress_unknown_code_error] =
    g_param_spec_boolean
    (_TRIPLET("suppress-unknown-code-error"),
     FALSE,
     G_PARAM_WRITABLE
     | G_PARAM_CONSTRUCT
     | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties
  (oclass,
   prop_number,
   properties);
}

static void
dda_morse_converter_init(DdaMorseConverter* self)
{
  self->partial = g_string_sized_new(0);
  self->partial2 = g_string_sized_new(0);
}

/*
 * Object method
 *
 */

GConverter*
dda_morse_converter_new(DdaMorseConverterDirection direction,
                        DdaMorseCharset* charset)
{
  return (GConverter*)
  g_object_new
  (DDA_TYPE_MORSE_CONVERTER,
   "direction", direction,
   "charset", charset,
   NULL);
}

void
dda_morse_converter_set_charset(DdaMorseConverter  *converter,
                                DdaMorseCharset    *charset)
{
  g_return_if_fail(DDA_IS_MORSE_CONVERTER(converter));
  g_return_if_fail(DDA_IS_MORSE_CHARSET(charset) || charset == NULL);
  g_set_object(&(converter->charset), charset);
}
