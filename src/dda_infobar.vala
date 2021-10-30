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
  [GtkTemplate (ui = "/org/hck/dotdashair/ui/infobar.ui")]
  public class InfoBar : Gtk.Box
  {
    [GtkChild]
    private Gtk.Label label;
    [GtkChild]
    private Gtk.Revealer revealer;

  /*
   * Properties
   *
   */

    private bool _revealed = false;
    public bool revealed
    {get {
      return this._revealed;
      }
     set {
      revealer.set_reveal_child(value);
      this._revealed = value;
      }}
    private string _message = null;
    public string message
    {get {
      return this._message;
      }
     set {
      label.set_label(value);
      this._message = value;
      }}
    private Gtk.MessageType _message_type;
    public Gtk.MessageType message_type
    {get {
      return this._message_type;
      }
     set {
      var context = ((Gtk.Widget) this).get_style_context();
      context.remove_class(Dda.Override.infobar_style_classes[this._message_type]);
      var accessible = ((Gtk.Widget) this).get_accessible();
      ((Gtk.Widget) this).queue_draw();

      this._message_type = value;
      context.add_class(Dda.Override.infobar_style_classes[this._message_type]);
      accessible.set_role(Atk.Role.INFO_BAR);

      switch (message_type)
      {
      case Gtk.MessageType.INFO:
        accessible.set_name(_("Information"));
        break;
      case Gtk.MessageType.QUESTION:
        accessible.set_name(_("Question"));
        break;
      case Gtk.MessageType.WARNING:
        accessible.set_name(_("Warning"));
        break;
      case Gtk.MessageType.ERROR:
        accessible.set_name(_("Error"));
        break;
      case Gtk.MessageType.OTHER:
        break;
      default:
        warning(@"Unknown GtkMessageType $(message_type)");
        break;
      }}}

  /*
   * Callback
   *
   */

    [GtkCallback]
    private void on_close(Gtk.Button button)
    {
      revealed = false;
    }

  /*
   * Methods
   *
   */

    private void @logv(GLib.LogLevelFlags level, string format, va_list l)
    {
      switch(level)
      {
      case GLib.LogLevelFlags.LEVEL_DEBUG:
      case GLib.LogLevelFlags.LEVEL_INFO:
      case GLib.LogLevelFlags.LEVEL_MESSAGE:
        message_type = Gtk.MessageType.INFO;
        break;
      case GLib.LogLevelFlags.LEVEL_WARNING:
      case GLib.LogLevelFlags.LEVEL_CRITICAL:
        message_type = Gtk.MessageType.WARNING;
        break;
      case GLib.LogLevelFlags.LEVEL_ERROR:
        message_type = Gtk.MessageType.ERROR;
        break;
      default:
        assert_not_reached();
      }

      var string_ = format.vprintf(l);

      message = string_;
      revealed = true;
    }

    [PrintfFormat]
    public void @debug(string format, ...)
    {
      va_list l = va_list();
      this.logv(GLib.LogLevelFlags.LEVEL_DEBUG, format, l);
    }

    [PrintfFormat]
    public void @info(string format, ...)
    {
      va_list l = va_list();
      this.logv(GLib.LogLevelFlags.LEVEL_INFO, format, l);
    }

    [PrintfFormat]
    public void @print(string format, ...)
    {
      va_list l = va_list();
      this.logv(GLib.LogLevelFlags.LEVEL_MESSAGE, format, l);
    }

    [PrintfFormat]
    public void @warning(string format, ...)
    {
      va_list l = va_list();
      this.logv(GLib.LogLevelFlags.LEVEL_WARNING, format, l);
    }

    [PrintfFormat]
    public void @critical(string format, ...)
    {
      va_list l = va_list();
      this.logv(GLib.LogLevelFlags.LEVEL_CRITICAL, format, l);
    }

    [PrintfFormat]
    public void @error(string format, ...)
    {
      va_list l = va_list();
      this.logv(GLib.LogLevelFlags.LEVEL_ERROR, format, l);
      ((GLib.Application) GLib.Application.get_default()).quit();
    }

  /*
   * Construct
   *
   */

    construct
    {
      message_type = Gtk.MessageType.OTHER;
      message = null;
      revealed = false;
    }

    class construct
    {
      var klass_name =
      Dda.Override.infobar_get_css_class();
      assert(klass_name != null);
      set_css_name(klass_name);
    }

    public InfoBar()
    {
      Object();
    }
  }
}
