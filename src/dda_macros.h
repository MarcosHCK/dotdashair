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
#ifndef __DDA_MACROS__
#define __DDA_MACROS__

#define _g_free0(var)             ((var == NULL) ? NULL : (var = (g_free (var), NULL)))
#define _g_object_ref0(var)       ((var == NULL) ? NULL : (var = (g_object_ref (var))))
#define _g_object_ref_sink0(var)  ((var == NULL) ? NULL : (var = (g_object_ref_sink (var))))
#define _g_object_unref0(var)     ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define goto_error() \
G_STMT_START { \
  g_warn_message(G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, "goto_error()"); \
  success = FALSE; \
  goto _error_; \
} G_STMT_END

#define goto_success() \
G_STMT_START { \
  success = TRUE; \
  goto _error_; \
} G_STMT_END

#define _TRIPLET(anything) anything,anything,anything

#endif // __DDA_MACROS__
