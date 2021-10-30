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
  [GtkTemplate (ui = "/org/hck/dotdashair/ui/textbox.ui")]
  public class Textbox : Gtk.Grid
  {
    [GtkChild]
    private Gtk.Label frame_label;
    [GtkChild]
    private Gtk.TextBuffer textbuffer1;
    [GtkChild]
    private Gtk.Revealer revealer1;
    [GtkChild]
    private Gtk.ToggleButton toggle1;
    private Dda.Morse.Converter converter = null;

  /*
   * Properties
   *
   */

    private string _label = "Textbox";
    public string label
    {get {
      return this._label;
      }
     set {
      frame_label.label = value;
      this._label = value;
      }}
    private bool _use_markup = false;
    public bool use_markup
    {get {
      return this._use_markup;
      }
     set {
      frame_label.use_markup = value;
      this._use_markup = value;
      }}
    private Dda.Morse.Charset _charset = null;
    public Dda.Morse.Charset charset
    {get {
      return this._charset;
      }
     set {
      converter.charset = value;
      this._charset = value;
      }}
    private bool _playing = false;
    public bool playing
    {get {
      return this._playing;
      }
     set {
      revealer1.set_reveal_child(value);
      this._playing = value;
      }}
    public bool pause
    {get {
      return toggle1.active;
      }
     set {
      toggle1.active = value;
      }}

  /*
   * Callbacks
   *
   */

    [GtkCallback]
    private void on_translate(Gtk.Button button)
    {
      Gtk.TextIter start, end;
      textbuffer1.get_start_iter(out start);
      textbuffer1.get_end_iter(out end);
      converter.reset();

      try
      {
        var result = Dda.Override.textbox_convert(converter, start.get_text(end));
        textbuffer1.set_text((string) result, result.length);
      }
      catch(GLib.Error e)
      {
        critical(@"$(e.domain): $(e.code): $(e.message)\r\n");
      }
    }

    [GtkCallback]
    private void on_clear(Gtk.Button button)
    {
      Gtk.TextIter start, end;
      textbuffer1.get_start_iter(out start);
      textbuffer1.get_end_iter(out end);
      textbuffer1.delete(ref start, ref end);
    }

    [GtkCallback]
    private void on_play_stop(Gtk.Button button)
    {
      pause = false;
      playing = (this._playing == false);

      var child = ((Gtk.Bin) button).get_child();
      var image = (child != null) ? (child as Gtk.Image) : null;
      assert(image != null);

      if(this._playing)
        image.icon_name = "media-playback-stop";
      else
        image.icon_name = "media-playback-start";
    }

    [GtkCallback]
    private void on_pause(Gtk.Button button)
    {
      pause = (toggle1.active);
    }

  /*
   * Construction
   *
   */

    construct
    {
      this.converter = new Dda.Morse.Converter(Dda.Morse.ConverterDirection.NONE, this._charset);
    }

    public Textbox()
    {
      Object();
    }

    public Textbox.with_label(string label)
    {
      Object(label : label, use_markup : false);
    }

    public Textbox.with_markup(string label)
    {
      Object(label : label, use_markup : true);
    }
  }
}
