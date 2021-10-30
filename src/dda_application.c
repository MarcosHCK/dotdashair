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
#include <dda_application.h>
#include <dda_backend.h>
#include <dda_macros.h>
#include <dda_morse_converter.h>
#include <dda_settings.h>
#include <dda_settings_windows.h>
#include <dda_window.h>
#include <gtk/gtk.h>
#include <portaudio/pa_backend.h>
#include <resources/dda_resources.h>

G_DEFINE_QUARK(dda-application-error-quark,
               dda_application_error);

static void
dda_application_g_initable_iface_init(GInitableIface* iface);

#define _g_string_freef0(var) ((var == NULL) ? NULL : (var = (g_string_free (var, FALSE), NULL)))
#define _g_string_freet0(var) ((var == NULL) ? NULL : (var = (g_string_free (var,  TRUE), NULL)))

/*
 * Object definition
 *
 *
 */

struct _DdaApplication
{
  GtkApplication parent_instance;

  /*<private>*/
  DdaSettings* dsettings;
  GSettings* gsettings;

  /*<private>*/
  DdaMorseCharset* charset;
  DdaMorseConverter* converter;

  /*<private>*/
  DdaBackend* backend;
  DdaBackendParameters i_parameters;
  DdaBackendParameters o_parameters;
  gdouble sample_rate;
  DdaInputStream* input;
  DdaOutputStream* output;

  /*<private>*/
  DdaSettingsWindow* settings;
  DdaWindow* window;
};

struct _DdaApplicationClass
{
  GtkApplicationClass parent_class;
};

G_DEFINE_TYPE_WITH_CODE
(DdaApplication,
 dda_application,
 GTK_TYPE_APPLICATION,
 G_IMPLEMENT_INTERFACE
 (G_TYPE_INITABLE,
  dda_application_g_initable_iface_init));

static void
on_changed_input_device(DdaSettingsWindow* settings, GParamSpec* pspec, DdaApplication* self)
{
  static guint throwing = FALSE;
  static gchar* last = NULL;
  gchar* current_ = NULL;
  gchar* current__ = NULL;
  guint current = 0;
  DdaBackendDevice* device = NULL;
  GError* tmp_err = NULL;

/*
 * Get device index
 *
 */

  if(throwing == TRUE)
    return;

  g_object_get(settings, "input-device", &current_, NULL);
  current__ = (gchar*) g_intern_string(current_);
  _g_free0(current_);

  if(current__ == last)
    return;
  else
    last = current__;

  current = (guint) g_strtod(current__, NULL);

/*
 * Get device
 *
 */

  device =
  dda_backend_get_nth_device(self->backend, current);
  g_assert(device != NULL);

  self->i_parameters.device = device;

/*
 * Create stream
 *
 */

  DdaInputStream* stream =
  dda_backend_read(self->backend, &(self->i_parameters), self->sample_rate, 0, DDA_BACKEND_FLAGS_NONE, &tmp_err);
  _g_object_unref0(device);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_critical
    ("(%s: %i): %s: %i: %s\r\n",
     G_STRFUNC,
     __LINE__,
     g_quark_to_string(tmp_err->domain),
     tmp_err->code,
     tmp_err->message);
    _g_error_free0(tmp_err);
    _g_object_unref0(stream);

    if(last == NULL)
      g_assert_not_reached();

    throwing = TRUE;
    g_object_set
    (settings,
     "input-device", last,
     NULL);
  }
  else
  {
    g_set_object(&(self->input), stream);
  }
}

static void
on_changed_output_device(DdaSettingsWindow* settings, GParamSpec* pspec, DdaApplication* self)
{
  static guint throwing = FALSE;
  static gchar* last = NULL;
  gchar* current_ = NULL;
  gchar* current__ = NULL;
  guint current = 0;
  DdaBackendDevice* device = NULL;
  GError* tmp_err = NULL;

/*
 * Get device index
 *
 */

  if(throwing == TRUE)
    return;

  g_object_get(settings, "output-device", &current_, NULL);
  current__ = (gchar*) g_intern_string(current_);
  _g_free0(current_);

  if(current__ == last)
    return;
  else
    last = current__;

  current = (guint) g_strtod(current__, NULL);

/*
 * Get device
 *
 */

  device =
  dda_backend_get_nth_device(self->backend, current);
  g_assert(device != NULL);

  self->o_parameters.device = device;

/*
 * Create stream
 *
 */

  DdaOutputStream* stream =
  dda_backend_write(self->backend, &(self->o_parameters), self->sample_rate, 0, DDA_BACKEND_FLAGS_NONE, &tmp_err);
  _g_object_unref0(device);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_critical
    ("(%s: %i): %s: %i: %s\r\n",
     G_STRFUNC,
     __LINE__,
     g_quark_to_string(tmp_err->domain),
     tmp_err->code,
     tmp_err->message);
    _g_error_free0(tmp_err);
    _g_object_unref0(stream);

    if(last == NULL)
      g_assert_not_reached();

    throwing = TRUE;
    g_object_set
    (settings,
     "output-device", last,
     NULL);
  }
  else
  {
    g_set_object(&(self->output), stream);
  }
}

static void
on_changed_state(DdaTextbox* textbox, DdaApplication* self)
{
  gboolean playing, pause;

  g_object_get
  (textbox,
   "playing", &playing,
   "pause", &pause,
   NULL);
}

static gboolean
dda_application_g_initable_iface_init_sync(GInitable* pself, GCancellable* cancellable, GError** error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;

  DdaApplication* self = (DdaApplication*) pself;
  GFile *current = NULL, *child = NULL;
  DdaSettings* dsettings = NULL;
  GSettings *gsettings, *msettings;
  DdaMorseCharset* charset = NULL;
  DdaMorseConverter* converter = NULL;
  DdaBackend* backend = NULL;
  GdkPixbuf* pixbuf = NULL;
  DdaSettingsWindow* settings = NULL;
  GtkListStore* input_devices = NULL;
  GtkListStore* output_devices = NULL;
  GString* idxbuilder = NULL;
  DdaBackendDevice* device = NULL;
  DdaWindow* window = NULL;

/*
 * Little trick to get $PWD (GIO is awesome)
 *
 */

  current = g_file_new_for_path(".");

/*
 * Common settings
 *
 */

#if DEVELOPER == 1
  g_set_object(&child, g_file_get_child(current, "settings/"));
  dsettings =
  dda_settings_new(g_file_peek_path(child), cancellable, &tmp_err);
#else // DEVELOPER
  dsettings =
  dda_settings_new(SCHEMASDIR, cancellable, &tmp_err);
#endif // DEVELOPER
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }
  else
  {
    self->dsettings = dsettings;
  }

  gsettings =
  dda_settings_get_settings(dsettings, GAPPNAME);
  if G_UNLIKELY(gsettings == NULL)
  {
    g_set_error_literal
    (error,
     DDA_APPLICATION_ERROR,
     DDA_APPLICATION_ERROR_GSETTINGS_INIT,
     "dda_settings_get_settings(): failed!\r\n");
    goto_error();
  }
  else
  {
    self->gsettings = gsettings;
  }

/*
 * Load charset and create
 * converter
 *
 */

#if DEVELOPER == 1
  g_set_object(&child, g_file_get_child(current, "settings/default_charset.cfg"));
  charset =
  dda_morse_charset_new(child, cancellable, &tmp_err);
#else
  gchar* charset_filename = NULL;

  charset_filename =
  g_settings_get_string
  (msettings,
   "charset-file");
  g_set_object
  (&child,
   g_file_new_for_path
   (charset_filename));
  _g_free0(charset_filename);

  charset =
  dda_morse_charset_new(child, cancellable, &tmp_err);
#endif // DEVELOPER
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }
  else
  {
    self->charset = charset;
  }

  self->converter = converter = (DdaMorseConverter*)
  dda_morse_converter_new(DDA_MORSE_CONVERTER_DIRECTION_NONE, charset);

/*
 * Backend
 *
 */

  backend =
  pa_backend_new(cancellable, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }
  else
  {
    self->backend = backend;
  }

/*
 * Icons
 *
 */

  pixbuf =
  gdk_pixbuf_new_from_resource(GRESNAME "/res/" GAPPNAME ".svg", &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_propagate_error(error, tmp_err);
    goto_error();
  }

  gtk_window_set_default_icon(pixbuf);
  g_object_unref(pixbuf);

/*
 * GUI
 *
 */

  settings =
  dda_settings_window_new();
  if G_LIKELY(settings != NULL)
  {
    g_object_ref_sink(settings);
    self->settings = settings;
  }

  window =
  dda_window_new();
  if G_LIKELY(window != NULL)
  {
    g_object_ref_sink(window);
    self->window = window;
  }

  g_signal_connect
  (settings,
   "delete-event",
   G_CALLBACK
   (gtk_widget_hide_on_delete),
   NULL);
  g_object_set
  (window,
   "settings-window", settings,
   NULL);

  dda_textbox_set_charset(window->inbox, charset);
  dda_textbox_set_charset(window->outbox, charset);

  g_settings_bind(gsettings,  "words-peer-minute", settings,  "words-peer-minute", G_SETTINGS_BIND_DEFAULT);
  g_settings_bind(gsettings, "length-sensitivity", settings, "length-sensitivity", G_SETTINGS_BIND_DEFAULT);
  g_settings_bind(gsettings, "volume-sensitivity", settings, "volume-sensitivity", G_SETTINGS_BIND_DEFAULT);
  g_settings_bind(gsettings,     "beep-frequency", settings,     "beep-frequency", G_SETTINGS_BIND_DEFAULT);

  g_object_get
  (settings,
   "input-devices", &input_devices,
   "output-devices", &output_devices,
   NULL);

  guint i, devices = dda_backend_get_n_devices(backend);
  idxbuilder = g_string_sized_new(16);
  for(i = 0;i < devices;i++)
  {
    device =
    dda_backend_get_nth_device(backend, i);
    g_string_printf(idxbuilder, "%i", i);

    if(dda_backend_device_get_input_channels(device) > 0)
    {
      GtkTreeIter iter;
      gtk_list_store_append(input_devices, &iter);
      gtk_list_store_set
      (input_devices,
       &iter,
       0, idxbuilder->str,
       1, dda_backend_device_get_display_name(device),
       -1);
    }

    if(dda_backend_device_get_output_channels(device) > 0)
    {
      GtkTreeIter iter;
      gtk_list_store_append(output_devices, &iter);
      gtk_list_store_set
      (output_devices,
       &iter,
       0, idxbuilder->str,
       1, dda_backend_device_get_display_name(device),
       -1);
    }

    _g_object_unref0(device);
  }

  g_signal_connect
  (settings,
   "notify::input-device",
   G_CALLBACK(on_changed_input_device),
   self);
  g_signal_connect
  (settings,
   "notify::output-device",
   G_CALLBACK(on_changed_output_device),
   self);
  g_signal_connect
  (window->inbox,
   "changed-state",
   G_CALLBACK(on_changed_state),
   self);
  g_signal_connect
  (window->outbox,
   "changed-state",
   G_CALLBACK(on_changed_state),
   self);

  G_STMT_START {
    guint default_ = dda_backend_get_default_input_device(backend);
    g_set_object(&device, dda_backend_get_nth_device(backend, default_));
    DdaBackendParameters* params = &(self->i_parameters);

    params->sample_type = DDA_SAMPLE_TYPE_FLOAT32;
    params->sample_bo = DDA_SAMPLE_BYTE_ORDER_NATIVE;
    params->channels = 1;
    params->latency = dda_backend_device_get_high_input_latency(device);

    g_string_printf(idxbuilder, "%i", default_);
    g_object_set(settings, "input-device", idxbuilder->str, NULL);
  } G_STMT_END;

  G_STMT_START {
    guint default_ = dda_backend_get_default_output_device(backend);
    g_set_object(&device, dda_backend_get_nth_device(backend, default_));
    DdaBackendParameters* params = &(self->o_parameters);

    params->sample_type = DDA_SAMPLE_TYPE_FLOAT32;
    params->sample_bo = DDA_SAMPLE_BYTE_ORDER_NATIVE;
    params->channels = 1;
    params->latency = dda_backend_device_get_high_output_latency(device);

    g_string_printf(idxbuilder, "%i", default_);
    g_object_set(settings, "output-device", idxbuilder->str, NULL);
  } G_STMT_END;

  gtk_window_set_application
  (GTK_WINDOW(window),
   GTK_APPLICATION(self));
  gtk_window_present
  (GTK_WINDOW(window));

/*
 * Just ensure resources are linked
 * with main executable
 *
 */

  GResource* resources =
  dda_resources_get_resource();
  if G_UNLIKELY(resources == NULL)
  {
    g_set_error_literal
    (error,
     DDA_APPLICATION_ERROR,
     DDA_APPLICATION_ERROR_FAILED,
     "Resources are not linked!\r\n");
    g_assert_not_reached();
  }

_error_:
  _g_object_unref0(current);
  _g_object_unref0(child);
  _g_object_unref0(input_devices);
  _g_object_unref0(output_devices);
  _g_string_freet0(idxbuilder);
  _g_object_unref0(device);
return success;
}

static void
dda_application_g_initable_iface_init(GInitableIface* iface)
{
  iface->init = dda_application_g_initable_iface_init_sync;
}

static void
dda_application_class_activate(GApplication* pself)
{
  DdaApplication* self = (DdaApplication*) pself;
  GError* tmp_err = NULL;
  gboolean success = TRUE;

/*
 * Initialize
 *
 */

  success =
  g_initable_init(G_INITABLE(pself), NULL, &tmp_err);
  if G_UNLIKELY(tmp_err != NULL)
  {
    g_critical
    ("(%s: %i): %s: %i: %s\r\n",
     G_STRFUNC,
     __LINE__,
     g_quark_to_string(tmp_err->domain),
     tmp_err->code,
     tmp_err->message);
    _g_error_free0(tmp_err);
    g_assert_not_reached();
  }
}

static void
dda_application_class_finalize(GObject* pself)
{
  DdaApplication* self = DDA_APPLICATION(pself);
G_OBJECT_CLASS(dda_application_parent_class)->finalize(pself);
}

#if DEVELOPER == 1
# define _clear_object0(var) ((var == NULL) ? NULL : (var = (g_assert_finalize_object (var), NULL)))
#else // DEVELOPER
# define _clear_object0(var) (_g_object_unref0 ((var)))
#endif // DEVELOPER

static void
dda_application_class_dispose(GObject* pself)
{
  DdaApplication* self = DDA_APPLICATION(pself);
  g_clear_object(&(self->dsettings));
  g_clear_object(&(self->gsettings));
  g_clear_object(&(self->charset));
  g_clear_object(&(self->converter));
  g_clear_object(&(self->backend));
  g_clear_object(&(self->output));
  g_clear_object(&(self->input));
  g_clear_object(&(self->settings));
  g_clear_object(&(self->window));
G_OBJECT_CLASS(dda_application_parent_class)->dispose(pself);
}

static void
dda_application_class_init(DdaApplicationClass* klass)
{
  GApplicationClass* aclass = G_APPLICATION_CLASS(klass);
  GObjectClass* oclass = G_OBJECT_CLASS(klass);

  aclass->activate = dda_application_class_activate;

  oclass->finalize = dda_application_class_finalize;
  oclass->dispose = dda_application_class_dispose;
}

static void
dda_application_init(DdaApplication* self)
{
}
