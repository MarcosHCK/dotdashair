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
#include <pa_backend.h>
#include <pa_backend_device.h>
#include <pa_error.h>
#include <portaudio.h>

static void
pa_backend_g_initable_iface_init(GInitableIface* iface);

/*
 * Object definition
 *
 */

struct _PaBackend
{
  DdaBackend parent_instance;
  DdaBackendDevice** devices;
  guint n_devices;
};

struct _PaBackendClass
{
  DdaBackendClass parent_class;
  gboolean pa_initialized;      /* zeroed at class construction */
  guint instances;
};

G_DEFINE_TYPE_WITH_CODE
(PaBackend,
 pa_backend,
 DDA_TYPE_BACKEND,
 G_IMPLEMENT_INTERFACE
 (G_TYPE_INITABLE,
  pa_backend_g_initable_iface_init));

static gboolean
pa_backend_g_initable_iface_init_sync(GInitable* pself, GCancellable* cancellable, GError** error)
{
  PaBackend* self = PA_BACKEND(pself);
  gboolean success = TRUE;
  GError* tmp_err = NULL;

  if G_UNLIKELY
    (PA_BACKEND_GET_CLASS(self)->pa_initialized == FALSE)
  {
    PaError paer = Pa_Initialize();
    if G_UNLIKELY(paer != paNoError)
    {
      pa_error_propagate(error, paer);
      goto_error();
    }
  }

  G_STMT_START {
    PaDeviceIndex i, devices;
    DdaBackendDevice* device;
    devices = Pa_GetDeviceCount();
    self->devices = g_new(DdaBackendDevice*, devices);
    self->n_devices = (guint) devices;

    for(i = 0;
        i < devices;
        i++)
    {
      device =
      g_object_new(PA_TYPE_BACKEND_DEVICE, NULL);
      pa_backend_device_set_info
      ((PaBackendDevice*)
       device,
       (PaDeviceInfo*)
       Pa_GetDeviceInfo(i));

      self->devices[i] = device;
    }
  } G_STMT_END;

_error_:
return success;
}

static void
pa_backend_g_initable_iface_init(GInitableIface* iface)
{
  iface->init = pa_backend_g_initable_iface_init_sync;
}

static DdaBackendDevice*
pa_backend_class_get_nth_device(DdaBackend* pself, guint index)
{
  PaBackend* self = PA_BACKEND(pself);
  g_return_val_if_fail(index < self->n_devices, NULL);
return g_object_ref(self->devices[index]);
}

static guint
pa_backend_class_n_devices(DdaBackend* pself)
{
  PaBackend* self = PA_BACKEND(pself);
return self->n_devices;
}

static void
pa_backend_class_finalize(GObject* pself)
{
  PaBackend* self = PA_BACKEND(pself);
  _g_free0(self->devices);

  if((-- PA_BACKEND_GET_CLASS(self)->instances) == 0)
  {
    PaError paer = Pa_Terminate();
    if G_UNLIKELY(paer != paNoError)
    {
      g_warning
      ("(%s: %i): %s: %s\r\n",
       G_STRFUNC,
       __LINE__,
       "wait",
       Pa_GetErrorText(paer));
    }
  }
G_OBJECT_CLASS(pa_backend_parent_class)->finalize(pself);
}

static void
pa_backend_class_dispose(GObject* pself)
{
  PaBackend* self = PA_BACKEND(pself);
  G_STMT_START {
    PaDeviceIndex i, devices;
    devices = Pa_GetDeviceCount();

    for(i = 0;
        i < devices;
        i++)
    {
      _g_object_unref0(self->devices[i]);
    }
  } G_STMT_END;
G_OBJECT_CLASS(pa_backend_parent_class)->dispose(pself);
}

static void
pa_backend_class_init(PaBackendClass* klass)
{
  DdaBackendClass* bclass = DDA_BACKEND_CLASS(klass);
  GObjectClass* oclass = G_OBJECT_CLASS(klass);
  klass->pa_initialized = FALSE;

  bclass->get_nth_device = pa_backend_class_get_nth_device;
  bclass->get_n_devices = pa_backend_class_n_devices;
  bclass->get_default_input_device = (guint (*) (DdaBackend*)) Pa_GetDefaultInputDevice;
  bclass->get_default_output_device = (guint (*) (DdaBackend*)) Pa_GetDefaultOutputDevice;

  oclass->finalize = pa_backend_class_finalize;
  oclass->dispose = pa_backend_class_dispose;
}

static void
pa_backend_init(PaBackend* self)
{
  PA_BACKEND_GET_CLASS(self)->instances++;
}

/*
 * Object methods
 *
 */

DdaBackend*
pa_backend_new(GCancellable* cancellable, GError** error)
{
  return (DdaBackend*)
  g_initable_new
  (PA_TYPE_BACKEND,
   cancellable,
   error,
   NULL);
}
