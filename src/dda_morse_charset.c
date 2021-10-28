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

G_DEFINE_QUARK(dda-morse-charset-error-quark,
               dda_morse_charset_error);

#define _g_bytes_unref0(var)    ((var == NULL) ? NULL : (var = (g_bytes_unref (var), NULL)))
#define _g_key_file_unref0(var) ((var == NULL) ? NULL : (var = (g_key_file_unref (var), NULL)))
#define _g_strfreev0(var)       ((var == NULL) ? NULL : (var = (g_strfreev (var), NULL)))
#define _g_array_unref0(var)    ((var == NULL) ? NULL : (var = (g_array_unref (var), NULL)))
#define _g_tree_unref0(var)     ((var == NULL) ? NULL : (var = (g_tree_unref (var), NULL)))

static void
dda_morse_charset_g_initable_iface_init(GInitableIface* iface);

#define MORSE_CHARSET "MorseCharset"

/*
 * Object definition
 *
 */

struct _DdaMorseCharset
{
  GObject parent_instance;

  /*<private>*/
  GFile* charset_file;
  DdaMorseEntity* alphabet;
  guint n_alphabet;
  GTree* code_tree; /* lookup code from char */
  GTree* char_tree; /* lookup char from code */
};

struct _DdaMorseCharsetClass
{
  GObjectClass parent_class;
};

enum
{
  prop_0,
  prop_charset_file,
  prop_number,
};

static
GParamSpec* properties[prop_number] = {0};

G_DEFINE_TYPE_WITH_CODE
(DdaMorseCharset,
 dda_morse_charset,
 G_TYPE_OBJECT,
 G_IMPLEMENT_INTERFACE
 (G_TYPE_INITABLE,
  dda_morse_charset_g_initable_iface_init));

static gboolean
unichar_strcmp(gunichar* a_, gunichar* b_)
{
return (*a_) - (*b_);
}

static gboolean
generate_code_tree(DdaMorseCharset* self, GError** error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  GTree* tree = NULL;
  guint i;

  tree = g_tree_new((GCompareFunc) unichar_strcmp);

  for(i = 0;
      i < self->n_alphabet;
      i++)
  {
    g_tree_insert(tree, (gpointer) &(self->alphabet[i].char_), GUINT_TO_POINTER(i));
  }

  self->code_tree = g_steal_pointer(&tree);
_error_:
  _g_tree_unref0(tree);
return success;
}

static gboolean
generate_char_tree(DdaMorseCharset* self, GError** error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  GTree* tree = NULL;
  guint i;

  tree = g_tree_new((GCompareFunc) g_strcmp0);

  for(i = 0;
      i < self->n_alphabet;
      i++)
  {
    g_tree_insert(tree, self->alphabet[i].code, GUINT_TO_POINTER(i));
  }

  self->char_tree = g_steal_pointer(&tree);
_error_:
  _g_tree_unref0(tree);
return success;
}

static gboolean
dda_morse_charset_g_initable_iface_init_sync(GInitable* pself, GCancellable* cancellable, GError** error)
{
  DdaMorseCharset* self = DDA_MORSE_CHARSET(pself);
  gboolean success = TRUE;
  GError* tmp_err = NULL;
  GKeyFile* charset_keys = NULL;
  GBytes* charset_bytes = NULL;
  gchar** chars = NULL;
  gsize n_chars = 0;
  GArray* entries = NULL;
  gchar *key, *value;
  gsize n_value;
  guint i;

/*
 * Load charset definition
 *
 */

  charset_keys =
  g_key_file_new();

  charset_bytes =
  g_file_load_bytes(self->charset_file, cancellable, NULL, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  success =
  g_key_file_load_from_bytes(charset_keys, charset_bytes, G_KEY_FILE_NONE, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  _g_bytes_unref0(charset_bytes);

/*
 * Interpret charset definition
 *
 */

  chars =
  g_key_file_get_keys(charset_keys, MORSE_CHARSET, &n_chars, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  entries =
  g_array_sized_new(FALSE, TRUE, sizeof(DdaMorseEntity), n_chars + 1);
  G_STMT_START {
    DdaMorseEntity entity =
    {
      (DdaMorseChar) L' ',
      (DdaMorseCode)  " ",
      1,
    };

    g_array_append_vals(entries, &entity, 1);
  } G_STMT_END;

  for(i = 0;
      i < n_chars;
      i++)
  {
    key = chars[i];
    if G_UNLIKELY
      (g_utf8_strlen(chars[i], -1) != 1)
    {
      g_set_error_literal
      (error,
       DDA_MORSE_CHARSET_ERROR,
       DDA_MORSE_CHARSET_ERROR_CHARACTER_TOO_LONG,
       "Character are supposed to be one-character long\r\n");
      goto_error();
    }

    value =
    g_key_file_get_string(charset_keys, MORSE_CHARSET, chars[i], &tmp_err);
    if G_UNLIKELY(tmp_err != NULL)
    {
      g_propagate_error(error, tmp_err);
      goto_error();
    }
    else
    {
      n_value = g_utf8_strlen(value, -1);
    }

    DdaMorseEntity entry =
    {
      g_utf8_get_char(key),
      g_steal_pointer(&value),
      n_value,
    };

    g_array_append_vals(entries, &entry, 1);
  }

  self->alphabet = g_array_steal(entries, &n_value);
  self->n_alphabet = n_value;

/*
 * Generate trees
 *
 */

  success =
  generate_code_tree(self, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  success =
  generate_char_tree(self, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

_error_:
  _g_bytes_unref0(charset_bytes);
  _g_key_file_unref0(charset_keys);
  _g_strfreev0(chars);
  _g_array_unref0(entries);
  _g_free0(value);
  g_clear_object(&(self->charset_file));
return success;
}

static void
dda_morse_charset_g_initable_iface_init(GInitableIface* iface)
{
  iface->init = dda_morse_charset_g_initable_iface_init_sync;
}

static void
dda_morse_charset_class_set_property(GObject* pself, guint prop_id, const GValue* value, GParamSpec* pspec)
{
  DdaMorseCharset* self = DDA_MORSE_CHARSET(pself);

  switch(prop_id)
  {
  case prop_charset_file:
    g_set_object(&(self->charset_file), g_value_get_object(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(pself, prop_id, pspec);
    break;
  }
}

static void
dda_morse_charset_class_finalize(GObject* pself)
{
  DdaMorseCharset* self = DDA_MORSE_CHARSET(pself);

  DdaMorseCode code;
  guint i;

  for(i = 0;
      i < self->n_alphabet;
      i++)
  {
    code = self->alphabet[i].code;
    _g_free0(code);
  }

  _g_free0(self->alphabet);
G_OBJECT_CLASS(dda_morse_charset_parent_class)->finalize(pself);
}

static void
dda_morse_charset_class_dispose(GObject* pself)
{
  DdaMorseCharset* self = DDA_MORSE_CHARSET(pself);
G_OBJECT_CLASS(dda_morse_charset_parent_class)->dispose(pself);
}

static void
dda_morse_charset_class_init(DdaMorseCharsetClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS(klass);

  oclass->set_property = dda_morse_charset_class_set_property;
  oclass->finalize = dda_morse_charset_class_finalize;
  oclass->dispose = dda_morse_charset_class_dispose;

  properties[prop_charset_file] =
    g_param_spec_object
    (_TRIPLET("charset-file"),
     G_TYPE_FILE,
     G_PARAM_WRITABLE
     | G_PARAM_CONSTRUCT_ONLY
     | G_PARAM_STATIC_STRINGS);

  g_object_class_install_properties
  (oclass,
   prop_number,
   properties);
}

static void
dda_morse_charset_init(DdaMorseCharset* self)
{
}

/*
 * Object methods
 *
 */

DdaMorseCharset*
dda_morse_charset_new(GFile* charset_file, GCancellable* cancellable, GError** error)
{
  return (DdaMorseCharset*)
  g_initable_new
  (DDA_TYPE_MORSE_CHARSET,
   cancellable,
   error,
   "charset-file", charset_file,
   NULL);
}

const DdaMorseEntity*
ds_morse_charset_get_entity_by_char(DdaMorseCharset* morse, DdaMorseChar char_)
{
  g_return_val_if_fail(DDA_IS_MORSE_CHARSET(morse), NULL);
  gpointer idx_ = NULL;
  gboolean found;

  found =
  g_tree_lookup_extended(morse->code_tree, &char_, NULL, &idx_);
  if G_LIKELY(found == TRUE)
  {
    return morse->alphabet + GPOINTER_TO_UINT(idx_);
  }
return NULL;
}

const DdaMorseEntity*
ds_morse_charset_get_entity_by_code(DdaMorseCharset* morse, DdaMorseCode code)
{
  g_return_val_if_fail(DDA_IS_MORSE_CHARSET(morse), NULL);
  gpointer idx_ = NULL;
  gboolean found;

  found =
  g_tree_lookup_extended(morse->char_tree, code, NULL, &idx_);
  if G_LIKELY(found == TRUE)
  {
    return morse->alphabet + GPOINTER_TO_UINT(idx_);
  }
return NULL;
}
