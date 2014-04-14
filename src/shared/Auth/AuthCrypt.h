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

#ifndef _AUTHCRYPT_H
#define _AUTHCRYPT_H

#include "Common.h"
#include <vector>

class BigNumber;

/**
 * @brief
 *
 */
class AuthCrypt
{
    public:
        /**
         * @brief
         *
         */
        AuthCrypt();
        /**
         * @brief
         *
         */
        ~AuthCrypt();

        const static size_t CRYPTED_SEND_LEN = 4; /**< TODO */
        const static size_t CRYPTED_RECV_LEN = 6; /**< TODO */

        /**
         * @brief
         *
         */
        void Init();

        /**
         * @brief
         *
         * @param key
         * @param len
         */
        void SetKey(uint8* key, size_t len);

        /**
         * @brief
         *
         * @param
         * @param size_t
         */
        void DecryptRecv(uint8*, size_t);
        /**
         * @brief
         *
         * @param
         * @param size_t
         */
        void EncryptSend(uint8*, size_t);

        /**
         * @brief
         *
         * @return bool
         */
        bool IsInitialized() { return _initialized; }

        /**
         * @brief
         *
         * @param
         * @param
         */
        static void GenerateKey(uint8*, BigNumber*);

    private:
        std::vector<uint8> _key; /**< TODO */
        uint8 _send_i, _send_j, _recv_i, _recv_j; /**< TODO */
        bool _initialized; /**< TODO */
};
#endif
