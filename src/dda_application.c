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
#include <dda_macros.h>
#include <dda_settings.h>
#include <gtk/gtk.h>

G_DEFINE_QUARK(dda-application-error-quark,
               dda_application_error);

static void
dda_application_g_initable_iface_init(GInitableIface* iface);

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
  GSettings* msettings;
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

static gboolean
dda_application_g_initable_iface_init_sync(GInitable* pself, GCancellable* cancellable, GError** error)
{
  gboolean success = TRUE;
  GError* tmp_err = NULL;

  DdaApplication* self = (DdaApplication*) pself;
  GFile *current = NULL, *child = NULL;
  DdaSettings* dsettings = NULL;
  GSettings *gsettings, *msettings;

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
  dda_settings_get_settings(dsettings, GAPPNAME ".gui");
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

  msettings =
  dda_settings_get_settings(dsettings, GAPPNAME ".morse");
  if G_UNLIKELY(msettings == NULL)
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
    self->msettings = msettings;
  }

_error_:
  _g_object_unref0(current);
  _g_object_unref0(child);
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
  DdaApplication* self = (DdaApplication*) self;
  GError* tmp_err = NULL;

/*
 * Initialize
 *
 */

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
    g_error_free(tmp_err);
    g_assert_not_reached();
  }
}

static void
dda_application_class_finalize(GObject* pself)
{
  DdaApplication* self = DDA_APPLICATION(pself);
G_OBJECT_CLASS(dda_application_parent_class)->finalize(pself);
}

static void
dda_application_class_dispose(GObject* pself)
{
  DdaApplication* self = DDA_APPLICATION(pself);
  g_clear_object(&(self->msettings));
  g_clear_object(&(self->gsettings));
  g_clear_object(&(self->dsettings));
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
