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

namespace Dda
{
  [GtkTemplate (ui = "/org/hck/dotdashair/ui/window.ui")]
  public class Window : Gtk.Window
  {
    [GtkCallback]
    private bool on_delete_event(Gtk.Widget widget, Gdk.EventAny event)
    {
    return false;
    }

    [GtkCallback]
    private void on_preferences(Gtk.Button button)
    {
    }

    private static Gtk.AboutDialog __about__ = null;

    [GtkCallback]
    private void on_about(Gtk.Button button)
    {
      if(unlikely(__about__ == null))
      {
        __about__ = new Gtk.AboutDialog();
        ((Gtk.Window) __about__).set_transient_for((Gtk.Window)this);

        const
        string[] artists =
        {
          "MarcosHCK",
          null,
        };

        const
        string[] authors =
        {
          "MarcosHCK",
          null,
        };
        const
        string[] documenters =
        {
          "MarcosHCK",
          null,
        };

        const
        string copyright = "Copyright 2021-2023 MarcosHCK";

        __about__.title = (_("About %s")).printf(Config.PACKAGE_NAME);

        __about__.set_artists(artists);
        __about__.set_authors(authors);
        __about__.set_copyright(copyright);
        __about__.set_documenters(documenters);
        __about__.set_license("GNU GPLv3.0");
        __about__.set_license_type(Gtk.License.GPL_3_0);
        __about__.set_program_name(Config.PACKAGE_NAME);
        __about__.set_translator_credits(_("translator-credits"));
        __about__.set_version(Config.PACKAGE_VERSION);
        __about__.set_website(Config.PACKAGE_URL);
        __about__.set_website_label(_("Visit our website"));
        __about__.set_wrap_license(true);

        ((Gtk.Widget) __about__).delete_event.connect
        ((widget, event) =>
        {
          widget.hide();
          return false;
        });
      }

      ((Gtk.Dialog) __about__).run();
      ((Gtk.Widget) __about__).hide();
    }
  }
}
