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
#include <glib/gi18n-lib.h>

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "");
  bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);

  GApplication* app = NULL;
  int status = 0;

  app = (GApplication*)
  g_object_new
  (DDA_TYPE_APPLICATION,
   "application-id", GAPPNAME,
   "flags", G_APPLICATION_FLAGS_NONE,
   NULL);

  g_application_set_default(app);

  status =
  g_application_run(app, argc, argv);
#if DEVELOPER == 1
  g_assert_finalize_object(app);              /* Finally destroy application object                               */
#else
  g_object_unref(app);
#endif // DEVELOPER
return status;
}
