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

#ifndef __SQLDELAYTHREAD_H
#define __SQLDELAYTHREAD_H

#include <ace/Thread_Mutex.h>
#include "LockedQueue.h"
#include "Threading.h"

class Database;
class SqlOperation;
class SqlConnection;

/**
 * @brief
 *
 */
class SqlDelayThread : public ACE_Based::Runnable
{
        /**
         * @brief
         *
         */
        typedef ACE_Based::LockedQueue<SqlOperation*, ACE_Thread_Mutex> SqlQueue;

    private:
        SqlQueue m_sqlQueue;                                /**< Queue of SQL statements */
        Database* m_dbEngine;                               /**< Pointer to used Database engine */
        SqlConnection* m_dbConnection;                      /**< Pointer to DB connection */
        volatile bool m_running; /**< TODO */

        /**
         * @brief process all enqueued requests
         *
         */
        void ProcessRequests();

    public:
        /**
         * @brief
         *
         * @param db
         * @param conn
         */
        SqlDelayThread(Database* db, SqlConnection* conn);
        /**
         * @brief
         *
         */
        ~SqlDelayThread();

        /// Put sql statement to delay queue
        bool Delay(SqlOperation* sql) { m_sqlQueue.add(sql); return true; }

        /**
         * @brief Stop event
         *
         */
        virtual void Stop();
        /**
         * @brief Main Thread loop
         *
         */
        virtual void run();
};
#endif                                                      //__SQLDELAYTHREAD_H
