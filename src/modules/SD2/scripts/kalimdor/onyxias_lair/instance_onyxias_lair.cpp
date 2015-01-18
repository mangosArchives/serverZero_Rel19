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

/**
 * ScriptData
 * SDName:      Instance_Onyxias_Lair
 * SD%Complete: 50
 * SDComment:   None
 * SDCategory:  Onyxia's Lair
 * EndScriptData
 */

#include "precompiled.h"
#include "onyxias_lair.h"

instance_onyxias_lair::instance_onyxias_lair(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_onyxias_lair::Initialize()
{
    m_uiEncounter = NOT_STARTED;
    m_tPhaseTwoStart = time(NULL);
}

bool instance_onyxias_lair::IsEncounterInProgress() const
{
    return m_uiEncounter == IN_PROGRESS || m_uiEncounter >= DATA_LIFTOFF;
}

void instance_onyxias_lair::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_ONYXIA_TRIGGER:
            if (m_uiEncounter == DONE)
            {
                pCreature->Despawn();
                break;
            }
        case NPC_ONYXIA:
            if (m_uiEncounter == DONE)
            {
                pCreature->Despawn();
                break;
            }
            m_uiEncounter = NOT_STARTED;
            m_mNpcEntryGuidStore[NPC_ONYXIA_TRIGGER] = pCreature->GetObjectGuid();
            break;
    }
}

void instance_onyxias_lair::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_uiEncounter;

    if (m_uiEncounter == IN_PROGRESS)
    {
        m_uiEncounter = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

void instance_onyxias_lair::SetData(uint32 uiType, uint32 uiData)
{
    if (uiType != TYPE_ONYXIA)
    {
        return;
    }

    m_uiEncounter = uiData;

    if (uiData == DATA_LIFTOFF)
    {
        m_tPhaseTwoStart = time(NULL);
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_uiEncounter << " ";

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }

    // Currently no reason to save anything
}

uint32 instance_onyxias_lair::GetData(uint32 uiType) const
{
    if (uiType)
    {
        return m_uiEncounter;
    }
    return 0;
}

InstanceData* GetInstanceData_instance_onyxias_lair(Map* pMap)
{
    return new instance_onyxias_lair(pMap);
}

void AddSC_instance_onyxias_lair()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_onyxias_lair";
    pNewScript->GetInstanceData = &GetInstanceData_instance_onyxias_lair;
    pNewScript->RegisterSelf();
}
