/*
 * Copyright (C) 2005-2013 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2013 MaNGOSZero <https:// github.com/mangos/zero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CONFIG_H
#define CONFIG_H
#endif
//#define WIN32

#ifdef WIN32
//#include <windows.h>
#define MANGOS_DLL_EXPORT extern "C" __declspec(dllexport)
#elif defined( __GNUC__ )
#define MANGOS_DLL_EXPORT extern "C"
#else
#define MANGOS_DLL_EXPORT extern "C" export
#endif
