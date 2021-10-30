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
  [GtkTemplate (ui = "/org/hck/dotdashair/ui/settings.ui")]
  public class SettingsWindow : Gtk.Window
  {
    [GtkChild]
    private Gtk.Adjustment adjustment1;
    [GtkChild]
    private Gtk.Adjustment adjustment2;
    [GtkChild]
    private Gtk.Adjustment adjustment3;
    [GtkChild]
    private Gtk.Adjustment adjustment4;
    [GtkChild]
    private Gtk.ComboBox combobox1;
    [GtkChild]
    private Gtk.ComboBox combobox2;
    [GtkChild]
    private Gtk.ListStore liststore1;
    [GtkChild]
    private Gtk.ListStore liststore2;

  /*
   * Properties
   *
   */

    public int words_peer_minute
    {get {
      return (int) adjustment1.value;
      }
    set {
      adjustment1.value = (double) value;
      }}
    public int length_sensitivity
    {get {
      return (int) adjustment2.value;
      }
    set {
      adjustment2.value = (double) value;
      }}
    public int volume_sensitivity
    {get {
      return (int) adjustment3.value;
      }
    set {
      adjustment3.value = (double) value;
      }}
    public int beep_frequency
    {get {
      return (int) adjustment4.value;
      }
    set {
      adjustment4.value = (double) value;
      }}
    public Gtk.ListStore input_devices
    {get {
      return liststore1;
      }}
    public Gtk.ListStore output_devices
    {get {
      return liststore2;
      }}
    public unowned string input_device
    {get {
      return combobox1.get_active_id();
      }
     set {
      combobox1.set_active_id(value);
      }}
    public unowned string output_device
    {get {
      return combobox2.get_active_id();
      }
     set {
      combobox2.set_active_id(value);
      }}

  /*
   * Callbacks
   *
   */

    [GtkCallback]
    private void on_adjustment1_value_changed(Gtk.Adjustment adjustment)
    {
      ((GLib.Object) this).notify_property("words-peer-minute");
    }

    [GtkCallback]
    private void on_adjustment2_value_changed(Gtk.Adjustment adjustment)
    {
      ((GLib.Object) this).notify_property("length-sensitivity");
    }

    [GtkCallback]
    private void on_adjustment3_value_changed(Gtk.Adjustment adjustment)
    {
      ((GLib.Object) this).notify_property("volume-sensitivity");
    }

    [GtkCallback]
    private void on_adjustment4_value_changed(Gtk.Adjustment adjustment)
    {
      ((GLib.Object) this).notify_property("beep-frequency");
    }

    [GtkCallback]
    private void on_combobox1_changed(Gtk.ComboBox combobox)
    {
      ((GLib.Object) this).notify_property("input-device");
    }

    [GtkCallback]
    private void on_combobox2_changed(Gtk.ComboBox combobox)
    {
      ((GLib.Object) this).notify_property("input-device");
    }

  /*
   * Construction
   *
   */

    public SettingsWindow()
    {
      Object();
    }
  }
}
