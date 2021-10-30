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
  [CCode (cprefix = "_Dda", lower_case_cprefix = "_dda_", cheader_filename = "dda_override.h")]
  namespace Override
  {
    [CCode (array_length_cexpr = "G_N_ELEMENTS(_dda_infobar_style_classes)")]
    public static unowned string[] infobar_style_classes;
    public static unowned string infobar_get_css_class();
    [CCode (array_length_pos = 2.1, array_length_type = "gsize")]
    public static uint8[] textbox_convert(GLib.Converter converter, string text, GLib.Cancellable? cancellable = null) throws GLib.Error;
  }
}
