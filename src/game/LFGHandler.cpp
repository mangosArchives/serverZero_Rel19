/**
 * This code is part of MaNGOS. Contributor & Copyright details are in AUTHORS/THANKS.
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

#include "Common.h"
#include "WorldPacket.h"
#include "Opcodes.h"
#include "Log.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldSession.h"
#include "Object.h"
#include "Chat.h"
#include "Language.h"
#include "ScriptMgr.h"
#include "World.h"
#include "Group.h"
#include "LFGHandler.h"

void WorldSession::HandleMeetingStoneJoinOpcode(WorldPacket & recv_data)
{
    ObjectGuid guid;

    recv_data >> guid;

    DEBUG_LOG("WORLD: Recvd CMSG_MEETINGSTONE_JOIN Message guid: %s", guid.GetString().c_str());

    // ignore for remote control state
    if (!_player->IsSelfMover())
        return;

    GameObject *obj = GetPlayer()->GetMap()->GetGameObject(guid);

    if (!obj)
        return;

    // Never expect this opcode for some type GO's
    if (obj->GetGoType() != GAMEOBJECT_TYPE_MEETINGSTONE)
    {
        sLog.outError("HandleMeetingStoneJoinOpcode: CMSG_MEETINGSTONE_JOIN for not allowed GameObject type %u (Entry %u), didn't expect this to happen.", obj->GetGoType(), obj->GetEntry());
        return;
    }

    if (Group *grp = _player->GetGroup())
    {
        if (!grp->IsLeader(_player->GetGUID()))
        {
            SendMeetingstoneFailed(MEETINGSTONE_FAIL_PARTYLEADER);

            obj->Use(_player);
            return;
        }

        if (grp->isRaidGroup())
        {
            SendMeetingstoneFailed(MEETINGSTONE_FAIL_RAID_GROUP);

            obj->Use(_player);
            return;
        }

        if (grp->IsFull())
        {
            SendMeetingstoneFailed(MEETINGSTONE_FAIL_FULL_GROUP);

            obj->Use(_player);
            return;
        }
    }

    GameObjectInfo const *gInfo = ObjectMgr::GetGameObjectInfo(obj->GetEntry());

    SendMeetingstoneSetqueue(gInfo->meetingstone.areaID, MEETINGSTONE_STATUS_JOINED_QUEUE);
    obj->Use(_player);
}

void WorldSession::HandleMeetingStoneLeaveOpcode(WorldPacket & recv_data)
{
    DEBUG_LOG("WORLD: Recvd CMSG_MEETINGSTONE_LEAVE");

    SendMeetingstoneSetqueue(0, MEETINGSTONE_STATUS_NONE);
}

void WorldSession::SendMeetingstoneFailed(uint8 status)
{
    WorldPacket data(SMSG_MEETINGSTONE_JOINFAILED, 1);
    data << uint8(status);
    SendPacket(&data);
}

void WorldSession::SendMeetingstoneSetqueue(uint32 areaid, uint8 status)
{
    WorldPacket data(SMSG_MEETINGSTONE_SETQUEUE, 5);
    data << uint32(areaid);
    data << uint8(status);
    SendPacket(&data);
}
