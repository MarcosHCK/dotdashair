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
#ifndef __DDA_BACKEND__
#define __DDA_BACKEND__ 1
#include <glib-object.h>

G_BEGIN_DECLS

#define DDA_TYPE_BACKEND            (dda_backend_get_type ())
#define DDA_BACKEND(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDA_TYPE_BACKEND, DdaBackend))
#define DDA_BACKEND_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_BACKEND, DdaBackendClass))
#define DDA_IS_BACKEND(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDA_TYPE_BACKEND))
#define DDA_IS_BACKEND_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_BACKEND))
#define DDA_BACKEND_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_BACKEND, DdaBackendClass))

typedef struct _DdaBackend        DdaBackend;
typedef struct _DdaBackendPrivate DdaBackendPrivate;
typedef struct _DdaBackendClass   DdaBackendClass;

struct _DdaBackend
{
  GObject parent_instance;
  DdaBackendPrivate * priv;
};

struct _DdaBackendClass
{
  GObjectClass parent_class;
  DdaBackendDevice* (*get_nth_device) (DdaBackend* self, guint index);
  guint (*get_n_device) (DdaBackend* self);
};

GType
dda_backend_get_type ();
DdaBackendDevice*
dda_backend_get_nth_device (DdaBackend* self,
                            guint index);
guint
dda_backend_get_n_device (DdaBackend* self);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (DdaBackend, g_object_unref)

#define DDA_TYPE_BACKEND_DEVICE             (dda_backend_device_get_type ())
#define DDA_BACKEND_DEVICE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), DDA_TYPE_BACKEND_DEVICE, DdaBackendDevice))
#define DDA_BACKEND_DEVICE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), DDA_TYPE_BACKEND_DEVICE, DdaBackendDeviceClass))
#define DDA_IS_BACKEND_DEVICE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DDA_TYPE_BACKEND_DEVICE))
#define DDA_IS_BACKEND_DEVICE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), DDA_TYPE_BACKEND_DEVICE))
#define DDA_BACKEND_DEVICE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), DDA_TYPE_BACKEND_DEVICE, DdaBackendDeviceClass))

typedef struct _DdaBackendDevice        DdaBackendDevice;
typedef struct _DdaBackendDevicePrivate DdaBackendDevicePrivate;
typedef struct _DdaBackendDeviceClass   DdaBackendDeviceClass;

struct _DdaBackendDevice {
  GObject parent_instance;
  DdaBackendDevicePrivate * priv;
};

struct _DdaBackendDeviceClass {
  GObjectClass parent_class;
  gchar* (*get_display_name) (DdaBackendDevice* self);
  gchar* (*get_name) (DdaBackendDevice* self);
  guint (*get_input_channels) (DdaBackendDevice* self);
  guint (*get_output_channels) (DdaBackendDevice* self);
  gdouble (*get_high_input_latency) (DdaBackendDevice* self);
  gdouble (*get_high_output_latency) (DdaBackendDevice* self);
  gdouble (*get_low_input_latency) (DdaBackendDevice* self);
  gdouble (*get_low_output_latency) (DdaBackendDevice* self);
  gdouble* (*list_sample_rates) (DdaBackendDevice* self, DdaBackendParameters* input_parameters, DdaBackendParameters* output_parameters, gint* result_length1);
};

GType
dda_backend_device_get_type ();
gchar*
dda_backend_device_get_display_name (DdaBackendDevice* self);
gchar*
dda_backend_device_get_name (DdaBackendDevice* self);
guint
dda_backend_device_get_input_channels (DdaBackendDevice* self);
guint
dda_backend_device_get_output_channels (DdaBackendDevice* self);
gdouble
dda_backend_device_get_high_input_latency (DdaBackendDevice* self);
gdouble
dda_backend_device_get_high_output_latency (DdaBackendDevice* self);
gdouble
dda_backend_device_get_low_input_latency (DdaBackendDevice* self);
gdouble
dda_backend_device_get_low_output_latency (DdaBackendDevice* self);
gdouble*
dda_backend_device_list_sample_rates (DdaBackendDevice* self,
                                      DdaBackendParameters* input_parameters,
                                      DdaBackendParameters* output_parameters,
                                      gint* result_length1);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (DdaBackendDevice, g_object_unref)

#define DDA_TYPE_SAMPLE_TYPE (dda_sample_type_get_type ())

typedef enum
{
  DDA_SAMPLE_TYPE_UNKNOWN,
  DDA_SAMPLE_TYPE_INT8,
  DDA_SAMPLE_TYPE_UINT8,
  DDA_SAMPLE_TYPE_INT16,
  DDA_SAMPLE_TYPE_UINT16,
  DDA_SAMPLE_TYPE_INT32,
  DDA_SAMPLE_TYPE_UINT32,
  DDA_SAMPLE_TYPE_FLOAT32,
  DDA_SAMPLE_TYPE_FLOAT64
} DdaSampleType;

GType
dda_sample_type_get_type ();

#define DDA_TYPE_BACKEND_PARAMETERS (dda_backend_parameters_get_type ())

struct _DdaBackendParameters
{
  DdaBackendDevice* device;
  DdaSampleType sample_type;
  gint channels;
  gdouble latency;
};

GType
dda_backend_parameters_get_type ();

G_END_DECLS

#endif // __DDA_BACKEND__
