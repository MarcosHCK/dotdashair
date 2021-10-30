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
#ifndef __PA_BACKEND_DEVICE__
#define __PA_BACKEND_DEVICE__
#include <dda_backend.h>
#include <portaudio.h>

#define PA_TYPE_BACKEND_DEVICE            (pa_backend_device_get_type ())
#define PA_BACKEND_DEVICE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PA_TYPE_BACKEND_DEVICE, PaBackendDevice))
#define PA_BACKEND_DEVICE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PA_TYPE_BACKEND_DEVICE, PaBackendDeviceClass))
#define PA_IS_BACKEND_DEVICE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PA_TYPE_BACKEND_DEVICE))
#define PA_IS_BACKEND_DEVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PA_TYPE_BACKEND_DEVICE))
#define PA_BACKEND_DEVICE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PA_TYPE_BACKEND_DEVICE, PaBackendDeviceClass))

typedef struct _PaBackendDevice       PaBackendDevice;
typedef struct _PaBackendDeviceClass  PaBackendDeviceClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
pa_backend_device_get_type () G_GNUC_CONST;

void
pa_backend_device_set_info(PaBackendDevice *device,
                           PaDeviceInfo    *info);

#if __cplusplus
}
#endif // __cplusplus

#endif // __PA_BACKEND_DEVICE__
