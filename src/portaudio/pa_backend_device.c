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
#include <pa_backend_device.h>
#if G_OS_WINDOWS
# include <windows.h>
# if PA_USE_ASIO
#   include "pa_asio.h"
# endif
#endif // G_OS_WINDOWS

/*
 * Object definition
 *
 */

struct _PaBackendDevice
{
  DdaBackendDevice parent_instance;
  PaDeviceInfo* info;
  gchar* display_name;
};

struct _PaBackendDeviceClass
{
  DdaBackendDeviceClass parent_class;
};

G_DEFINE_TYPE
(PaBackendDevice,
 pa_backend_device,
 DDA_TYPE_BACKEND_DEVICE);

static const gchar*
pa_backend_device_class_get_display_name(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
  if G_UNLIKELY(self->display_name == NULL)
  {
#if G_OS_WINDOWS
    G_STMT_START {
      /* Windows uses wide char (UTF-16) encoding for its   */
      /* devices, so translate it to UTF-8 suitable for GTK */
      GError* tmp_err = NULL;

      self->display_name =
      g_utf16_to_utf8((const gunichar2*) self->info->name, -1, NULL, NULL, &tmp_err);
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
        _g_free0(self->display_name);
        self->display_name =
        g_strdup("(error translating)");
      }
    } G_STMT_END;
#else
    self->display_name =
    g_strdup(self->info->name);
#endif // G_OS_WINDOWS
  }
return self->display_name;
}

static const gchar*
pa_backend_device_class_get_name(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return self->info->name;
}

static guint
pa_backend_device_class_get_input_channels(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return self->info->maxInputChannels;
}

static guint
pa_backend_device_class_get_output_channels(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return self->info->maxOutputChannels;
}

static gdouble
pa_backend_device_class_get_high_input_latency(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return (gdouble) self->info->defaultHighInputLatency;
}

static gdouble
pa_backend_device_class_get_high_output_latency(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return (gdouble) self->info->defaultHighOutputLatency;
}

static gdouble
pa_backend_device_class_get_low_input_latency(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return (gdouble) self->info->defaultLowInputLatency;
}

static gdouble
pa_backend_device_class_get_low_output_latency(DdaBackendDevice* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
return (gdouble) self->info->defaultLowOutputLatency;
}

static void
pa_backend_device_class_finalize(GObject* pself)
{
  PaBackendDevice* self = PA_BACKEND_DEVICE(pself);
  _g_free0(self->display_name);
G_OBJECT_CLASS(pa_backend_device_parent_class)->finalize(pself);
}

static void
pa_backend_device_class_init(PaBackendDeviceClass* klass)
{
  DdaBackendDeviceClass* dclass = DDA_BACKEND_DEVICE_CLASS(klass);
  GObjectClass* oclass = G_OBJECT_CLASS(klass);

  dclass->get_display_name = pa_backend_device_class_get_display_name;
  dclass->get_name = pa_backend_device_class_get_name;
  dclass->get_input_channels = pa_backend_device_class_get_input_channels;
  dclass->get_output_channels = pa_backend_device_class_get_output_channels;
  dclass->get_high_input_latency = pa_backend_device_class_get_high_input_latency;
  dclass->get_high_output_latency = pa_backend_device_class_get_high_output_latency;
  dclass->get_low_input_latency = pa_backend_device_class_get_low_input_latency;
  dclass->get_low_output_latency = pa_backend_device_class_get_low_output_latency;

  oclass->finalize = pa_backend_device_class_finalize;
}

static void
pa_backend_device_init(PaBackendDevice* self)
{
  self->display_name = NULL;
}

/*
 * Object methods
 *
 */

void
pa_backend_device_set_info(PaBackendDevice *device,
                           PaDeviceInfo    *info)
{
  g_return_if_fail(PA_IS_BACKEND_DEVICE(device));
  device->info = info;
}
