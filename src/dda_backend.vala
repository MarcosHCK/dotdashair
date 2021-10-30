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
  public abstract class Backend : GLib.Object
  {
    public abstract Dda.BackendDevice get_nth_device(uint index);
    public abstract uint get_n_devices();
    public abstract uint get_default_input_device();
    public abstract uint get_default_output_device();
    public abstract Dda.InputStream read(Dda.BackendParameters parameters, double sample_rate, uint frame_per_call, Dda.BackendFlags flags) throws GLib.Error;
    public abstract Dda.OutputStream write(Dda.BackendParameters parameters, double sample_rate, uint frame_per_call, Dda.BackendFlags flags) throws GLib.Error;
  }

  public abstract class BackendDevice : GLib.Object
  {
    public weak Dda.Backend backend;
    private uint index;

    public abstract unowned string get_display_name();
    public abstract unowned string get_name();
    public abstract uint get_input_channels();
    public abstract uint get_output_channels();
    public abstract double get_high_input_latency();
    public abstract double get_high_output_latency();
    public abstract double get_low_input_latency();
    public abstract double get_low_output_latency();
    public abstract double[] list_sample_rates(Dda.BackendParameters? input_parameters, Dda.BackendParameters? output_parameters);
  }

  public struct BackendParameters
  {
    public unowned Dda.BackendDevice device;
    Dda.SampleType sample_type;
    Dda.SampleByteOrder sample_bo;
    int channels;
    double latency;
  }

  public enum BackendFlags
  {
    NONE = 0,
    CLIP_OFF,
  }

  public enum SampleType
  {
    UNKNOWN = 0,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT24,
    UINT24,
    INT32,
    UINT32,
    FLOAT32,
    FLOAT64,
    IEC958,
    MPEG,
  }

  public enum SampleByteOrder
  {
    NATIVE = 0,
    LITTLE_ENDIAN,
    BIG_ENDIAN,
  }
}
