/**
 * mangos-zero is a full featured server for World of Warcraft in its vanilla
 * version, supporting clients for patch 1.12.x.
 *
 * Copyright (C) 2005-2014  MaNGOS project <http://getmangos.eu>
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

/// \addtogroup realmd
/// @{
/// \file

#ifndef _REALMLIST_H
#define _REALMLIST_H

#include "Common.h"

/**
 * @brief
 *
 */
struct RealmBuildInfo
{
    int build; /**< TODO */
    int major_version; /**< TODO */
    int minor_version; /**< TODO */
    int bugfix_version; /**< TODO */
    int hotfix_version; /**< TODO */
};

/**
 * @brief
 *
 * @param _build
 * @return const RealmBuildInfo
 */
RealmBuildInfo const* FindBuildInfo(uint16 _build);

/**
 * @brief
 *
 */
typedef std::set<uint32> RealmBuilds;

/// Storage object for a realm
/**
 * @brief
 *
 */
struct Realm
{
    std::string address; /**< TODO */
    uint8 icon; /**< TODO */
    RealmFlags realmflags;                                  /**< realmflags */
    uint8 timezone; /**< TODO */
    uint32 m_ID; /**< TODO */
    AccountTypes allowedSecurityLevel;                      /**< current allowed join security level (show as locked for not fit accounts) */
    float populationLevel; /**< TODO */
    RealmBuilds realmbuilds;                                /**< list of supported builds (updated in DB by mangosd) */
    RealmBuildInfo realmBuildInfo;                          /**< build info for show version in list */
};

/**
 * @brief Storage object for the list of realms on the server
 *
 */
class RealmList
{
    public:
        /**
         * @brief
         *
         */
        typedef std::map<std::string, Realm> RealmMap;

        /**
         * @brief
         *
         * @return RealmList
         */
        static RealmList& Instance();

        /**
         * @brief
         *
         */
        RealmList();
        /**
         * @brief
         *
         */
        ~RealmList() {}

        /**
         * @brief
         *
         * @param updateInterval
         */
        void Initialize(uint32 updateInterval);

        /**
         * @brief
         *
         */
        void UpdateIfNeed();

        /**
         * @brief
         *
         * @return RealmMap::const_iterator
         */
        RealmMap::const_iterator begin() const { return m_realms.begin(); }
        /**
         * @brief
         *
         * @return RealmMap::const_iterator
         */
        RealmMap::const_iterator end() const { return m_realms.end(); }
        /**
         * @brief
         *
         * @return uint32
         */
        uint32 size() const { return m_realms.size(); }
    private:
        /**
         * @brief
         *
         * @param init
         */
        void UpdateRealms(bool init);
        /**
         * @brief
         *
         * @param ID
         * @param name
         * @param address
         * @param port
         * @param icon
         * @param realmflags
         * @param timezone
         * @param allowedSecurityLevel
         * @param popu
         * @param builds
         */
        void UpdateRealm(uint32 ID, const std::string& name, const std::string& address, uint32 port, uint8 icon, RealmFlags realmflags, uint8 timezone, AccountTypes allowedSecurityLevel, float popu, const std::string& builds);
    private:
        RealmMap m_realms;                                  /**< Internal map of realms */
        uint32   m_UpdateInterval; /**< TODO */
        time_t   m_NextUpdateTime; /**< TODO */
};

#define sRealmList RealmList::Instance()

#endif
/// @}
