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
  public class Settings : GLib.Object, GLib.Initable
  {
    private GLib.SettingsSchemaSource source = null;
    private GLib.HashTable<string,GLib.SettingsSchema> schemas =
    new GLib.HashTable<string, GLib.SettingsSchema>(GLib.str_hash, GLib.str_equal);
    public string schemas_directory {get; construct;}

    public bool init(GLib.Cancellable? cancellable = null) throws GLib.Error
    {
      try
      {
        source = new GLib.SettingsSchemaSource.from_directory
        (this._schemas_directory,
         GLib.SettingsSchemaSource.get_default(),
         true);
      }
      catch(GLib.Error e)
      {
        throw e;
      }
    return true;
    }

  /*
   * API
   *
   */

    public GLib.SettingsSchema? get_schema(string schema_id)
    {
      var schema = schemas.lookup(schema_id);
      if(unlikely(schema == null))
      {
        schema = source.lookup(schema_id, true);
        if(unlikely(schema == null))
          return null;

        schemas.insert(schema_id, schema);
      }
    return schema;
    }

    public GLib.Settings? get_settings(string schema_id)
    {
      var schema = this.get_schema(schema_id);
      if(unlikely(schema == null))
        return null;
    return new GLib.Settings.full(schema, null, null);
    }

    public bool has_key(string schema_id, string key)
    {
      var schema = this.get_schema(schema_id);
      if(unlikely(schema == null))
        return false;
    return schema.has_key(key);
    }

    private static weak Dda.Settings __default__ = null;
    public static unowned Dda.Settings get_default()
    {
      return __default__;
    }

    public Settings(string directory, GLib.Cancellable? cancellable = null) throws GLib.Error
    {
      Object(schemas_directory : directory);
      this.init(cancellable);
      __default__ = this;
    }
    ~Settings()
    {
      __default__ = null;
    }
  }
}
