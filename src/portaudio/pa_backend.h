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
#ifndef __PA_BACKEND_INCLUDED__
#define __PA_BACKEND_INCLUDED__
#include <dda_backend.h>

#define PA_TYPE_BACKEND            (pa_backend_get_type ())
#define PA_BACKEND(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PA_TYPE_BACKEND, PaBackend))
#define PA_BACKEND_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PA_TYPE_BACKEND, PaBackendClass))
#define PA_IS_BACKEND(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PA_TYPE_BACKEND))
#define PA_IS_BACKEND_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PA_TYPE_BACKEND))
#define PA_BACKEND_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PA_TYPE_BACKEND, PaBackendClass))

typedef struct _PaBackend       PaBackend;
typedef struct _PaBackendClass  PaBackendClass;

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
pa_backend_get_type () G_GNUC_CONST;
DdaBackend*
pa_backend_new(GCancellable* cancellable, GError** error);

#if __cplusplus
}
#endif // __cplusplus

#endif // __PA_BACKEND_INCLUDED__
