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
#include <dda_output_stream.h>

/*
 * Object definition
 *
 */

struct _DdaOutputStream
{
  GOutputStream parent_instance;
};

struct _DdaOutputStreamClass
{
  GOutputStreamClass parent_class;
};

G_DEFINE_TYPE_WITH_CODE
(DdaOutputStream,
 dda_output_stream,
 G_TYPE_OUTPUT_STREAM,);

static void
dda_output_stream_class_finalize(GObject* pself)
{
  DdaOutputStream* self = DDA_OUTPUT_STREAM(pself);
G_OBJECT_CLASS(dda_output_stream_parent_class)->finalize(pself);
}

static void
dda_output_stream_class_dispose(GObject* pself)
{
  DdaOutputStream* self = DDA_OUTPUT_STREAM(pself);
G_OBJECT_CLASS(dda_output_stream_parent_class)->dispose(pself);
}

static void
dda_output_stream_class_init(DdaOutputStreamClass* klass)
{
  GObjectClass* oclass = G_OBJECT_CLASS(klass);

  oclass->finalize = dda_output_stream_class_finalize;
  oclass->dispose = dda_output_stream_class_dispose;
}

static void
dda_output_stream_init(DdaOutputStream* self)
{
}
