/**
 * ScriptDev2 is an extension for mangos providing enhanced features for
 * area triggers, creatures, game objects, instances, items, and spells beyond
 * the default database scripting in mangos.
 *
 * Copyright (C) 2006-2013  ScriptDev2 <http://www.scriptdev2.com/>
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
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef SC_CONFIG_H
#define SC_CONFIG_H

#include "Platform/CompilerDefs.h"
#include "revision.h"
#include "sd2_revision_nr.h"

#ifdef WIN32
  #define MANGOS_DLL_EXPORT extern "C" __declspec(dllexport)
#elif defined( __GNUC__ )
  #define MANGOS_DLL_EXPORT extern "C"
#else
  #define MANGOS_DLL_EXPORT extern "C" export
#endif

#ifndef _VERSION
  #define _VERSION "Revision [" SD2_REVISION_NR "] (" REVISION_ID ") " REVISION_DATE " " REVISION_TIME
#endif

// The path to config files
#ifndef SYSCONFDIR
  #define SYSCONFDIR ""
#endif

#if PLATFORM == PLATFORM_WINDOWS
  #ifdef _WIN64
    #define MANGOS_FULLVERSION _VERSION " (Win64)"
  #else
    #define MANGOS_FULLVERSION _VERSION " (Win32)"
  #endif
#else
  #define MANGOS_FULLVERSION _VERSION " (Unix)"
#endif

#endif
