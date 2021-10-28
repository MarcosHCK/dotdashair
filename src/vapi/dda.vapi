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
  namespace Morse
  {
    [CCode (cheader_filename = "dda_morse_charset.h", type_id="DDA_TYPE_MORSE_CHARSET")]
    public class Charset : GLib.Object, GLib.Initable
    {
      public Charset(GLib.File charset_file, GLib.Cancellable? cancellable = null) throws GLib.Error;
      public GLib.File charset_file {construct;}
    }

    [CCode (cheader_filename = "dda_morse_converter.h")]
    public enum ConverterDirection
    {
      NONE,
      CODE2CHAR,
      CHAR2CODE,
    }

    [CCode (cheader_filename = "dda_morse_converter.h")]
    public errordomain ConverterError
    {
      FAILED,
      UNGUESSABLE_INPUT,
      NOT_UTF8_INPUT,
      UNKNOWN_CHARACTER,
      UNKNOWN_CODE;
      public static GLib.Quark quark();
    }

    [CCode (cheader_filename = "dda_morse_converter.h", type_id="DDA_TYPE_MORSE_CONVERTER")]
    public class Converter : GLib.Object, GLib.Converter
    {
      [CCode (has_construct_function = false, type = "GConverter*")]
      public Converter(Dda.Morse.ConverterDirection direction, Dda.Morse.Charset charset);
      public Dda.Morse.Charset charset {set;}
    }
  }

  public class Application : Gtk.Application
  {
    public Dda.Morse.Charset charset;
    public Dda.Morse.Converter converter;
  }
}
