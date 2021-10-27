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
#ifndef __DDA_STREAM__
#define __DDA_STREAM__ 1
#include <gio/gio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

GType
dda_stream_get_type ();

//G_DEFINE_AUTOPTR_CLEANUP_FUNC (DdaStream, g_object_unref)

#if __cplusplus
}
#endif // __cplusplus

#endif // __DDA_STREAM__
