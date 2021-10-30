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
    [GtkChild]
    public Dda.Textbox inbox;
    [GtkChild]
    public Dda.Textbox outbox;

    private Gtk.Window _settings_window = null;
    public Gtk.Window settings_window
    {get {
      return this._settings_window;
      }
     set {
      this._settings_window = value;
      }}
    private Gtk.Window _about_window = null;
    public Gtk.Window about_window
    {get {
      return this._about_window;
      }
     set {
      this._about_window = value;
      }}

    [GtkCallback]
    private bool on_delete_event(Gtk.Widget widget, Gdk.EventAny event)
    {
    return false;
    }

    [GtkCallback]
    private void on_preferences(Gtk.Button button)
    {
      var __dialg__ = (Dda.SettingsWindow) settings_window;

      if(unlikely(settings_window == null))
      {
        settings_window = new Dda.SettingsWindow ();
        ((Gtk.Window) settings_window).set_transient_for((Gtk.Window) this);
        __dialg__ = (Dda.SettingsWindow) settings_window;
      }

      ((Gtk.Window) __dialg__).present();
      //((Gtk.Widget) __dialg__).hide();
    }

    [GtkCallback]
    private void on_about(Gtk.Button button)
    {
      var __dialg__ = (Gtk.AboutDialog) about_window;

      if(unlikely(about_window == null))
      {
        about_window = new Gtk.AboutDialog();
        ((Gtk.Window) about_window).set_transient_for((Gtk.Window) this);
        __dialg__ = (Gtk.AboutDialog) about_window;

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

        __dialg__.title = (_("About %s")).printf(Config.PACKAGE_NAME);
        __dialg__.set_artists(artists);
        __dialg__.set_authors(authors);
        __dialg__.set_copyright(copyright);
        __dialg__.set_documenters(documenters);
        __dialg__.set_license("GNU GPLv3.0");
        __dialg__.set_license_type(Gtk.License.GPL_3_0);
        __dialg__.set_program_name(Config.PACKAGE_NAME);
        __dialg__.set_translator_credits(_("translator-credits"));
        __dialg__.set_version(Config.PACKAGE_VERSION);
        __dialg__.set_website(Config.PACKAGE_URL);
        __dialg__.set_website_label(_("Visit our website"));
        __dialg__.set_wrap_license(true);

        ((Gtk.Widget) __dialg__).delete_event.connect
        ((widget, event) =>
        {
          widget.hide();
          return false;
        });
      }

      ((Gtk.Dialog) __dialg__).run();
      ((Gtk.Widget) __dialg__).hide();
    }
  }
}
