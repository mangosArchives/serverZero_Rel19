#
# Copyright (C) 2005-2014 MaNGOS <http://getmangos.eu/>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# ***** END GPL LICENSE BLOCK *****
#
# World of Warcraft, and all World of Warcraft or Warcraft art, images,
# and lore are copyrighted by Blizzard Entertainment, Inc.

include(MacroMangosSourceGroup)

#-----------------------------------------------------------------------------
# Define the scriptdev2 library
set(sources
    sd2_revision_nr.h
    sd2_revision_sql.h
    ScriptDevMgr.cpp
    ScriptDevMgr.h
    base/escort_ai.cpp
    base/escort_ai.h
    base/follower_ai.cpp
    base/follower_ai.h
    base/guard_ai.cpp
    base/guard_ai.h
    base/pet_ai.cpp
    base/pet_ai.h

    include/precompiled.cpp
    include/precompiled.h
    include/sc_creature.cpp
    include/sc_creature.h
    include/sc_grid_searchers.cpp
    include/sc_grid_searchers.h
    include/sc_instance.cpp
    include/sc_instance.h
    include/sc_gossip.h

    system/MangosdRev.cpp
    system/ScriptLoader.cpp
    system/ScriptLoader.h
    system/system.cpp
    system/system.h
)

#Battleground Scripts
file(GLOB sources_battlegrounds_files scripts/battlegrounds/*.cpp)
    set(sources_battlegrounds
        ${sources_battlegrounds_files}
    )

#World Scripts
file(GLOB sources_world_files scripts/world/*.cpp scripts/world/*.h)
    set(sources_world
        ${sources_world_files}
    )
	
#Eastern Kingdom Scripts
file(GLOB sources_eastern_kingdoms_files scripts/eastern_kingdoms/*.cpp scripts/eastern_kingdoms/*.h)
    set(sources_eastern_kingdoms
        ${sources_eastern_kingdoms_files}
    )

#Kalimdor Scripts
file(GLOB sources_kalimdor_files scripts/kalimdor/*.cpp scripts/kalimdor/*.h)
    set(sources_kalimdor
        ${sources_kalimdor_files}
    )

#Instance: Blackrock Depths Scripts
file(GLOB sources_instance_ek_brd_files scripts/eastern_kingdoms/blackrock_mountain/blackrock_depths/*.cpp scripts/eastern_kingdoms/blackrock_mountain/blackrock_depths/*.h)
    set(sources_instance_ek_brd
        ${sources_instance_ek_brd_files}
    )

#Instance: Blackrock Spire Scripts
file(GLOB sources_instance_ek_brs_files scripts/eastern_kingdoms/blackrock_mountain/blackrock_spire/*.cpp scripts/eastern_kingdoms/blackrock_mountain/blackrock_spire/*.h)
    set(sources_instance_ek_brs
        ${sources_instance_ek_brs_files}
    )

#Instance: Deadmines Scripts
file(GLOB sources_instance_ek_tdm_files scripts/eastern_kingdoms/deadmines/*.cpp scripts/eastern_kingdoms/deadmines/*.h)
    set(sources_instance_ek_tdm
        ${sources_instance_ek_tdm_files}
    )

#Instance: Gnomeregan Scripts
file(GLOB sources_instance_ek_gno_files scripts/eastern_kingdoms/gnomeregan/*.cpp scripts/eastern_kingdoms/gnomeregan/*.h)
    set(sources_instance_ek_gno
        ${sources_instance_ek_gno_files}
    )

#Instance: Scarlet Monastery Scripts
file(GLOB sources_instance_ek_sm_files scripts/eastern_kingdoms/scarlet_monastery/*.cpp scripts/eastern_kingdoms/scarlet_monastery/*.h)
    set(sources_instance_ek_sm
        ${sources_instance_ek_sm_files}
    )

#Instance: Scholomance Scripts
file(GLOB sources_instance_ek_scholo_files scripts/eastern_kingdoms/scholomance/*.cpp scripts/eastern_kingdoms/scholomance/*.h)
    set(sources_instance_ek_scholo
        ${sources_instance_ek_scholo_files}
    )

#Instance: Uldaman Scripts
file(GLOB sources_instance_ek_uld_files scripts/eastern_kingdoms/uldaman/*.cpp scripts/eastern_kingdoms/uldaman/*.h)
    set(sources_instance_ek_uld
        ${sources_instance_ek_uld_files}
    )

#Instance: Shadowfang Keep Scripts
file(GLOB sources_instance_ek_sfk_files scripts/eastern_kingdoms/shadowfang_keep/*.cpp scripts/eastern_kingdoms/shadowfang_keep/*.h)
    set(sources_instance_ek_sfk
        ${sources_instance_ek_sfk_files}
    )
	
#Instance: Sunken Temple Scripts
file(GLOB sources_instance_ek_st_files scripts/eastern_kingdoms/sunken_temple/*.cpp scripts/eastern_kingdoms/sunken_temple/*.h)
    set(sources_instance_ek_st
        ${sources_instance_ek_st_files}
    )
	
#Instance: Stratholme Scripts
file(GLOB sources_instance_ek_strat_files scripts/eastern_kingdoms/stratholme/*.cpp scripts/eastern_kingdoms/stratholme/*.h)
    set(sources_instance_ek_strat
        ${sources_instance_ek_strat_files}
    )

#Raid: Molten Core Scripts
file(GLOB sources_raid_ek_mc_files scripts/eastern_kingdoms/blackrock_mountain/molten_core/*.cpp scripts/eastern_kingdoms/blackrock_mountain/molten_core/*.h)
    set(sources_raid_ek_mc
        ${sources_raid_ek_mc_files}
    )
	
#Raid: Blackwing Lair Scripts
file(GLOB sources_raid_ek_bwl_files scripts/eastern_kingdoms/blackrock_mountain/blackwing_lair/*.cpp scripts/eastern_kingdoms/blackrock_mountain/blackwing_lair/*.h)
    set(sources_raid_ek_bwl
        ${sources_raid_ek_bwl_files}
    )
	
#Raid: Naxxramas Scripts
file(GLOB sources_raid_ek_naxx_files scripts/eastern_kingdoms/naxxramas/*.cpp scripts/eastern_kingdoms/naxxramas/*.h)
    set(sources_raid_ek_naxx
        ${sources_raid_ek_naxx_files}
    )

#Raid: Zul Gurub Scripts
file(GLOB sources_raid_ek_zg_files scripts/eastern_kingdoms/zulgurub/*.cpp scripts/eastern_kingdoms/zulgurub/*.h)
    set(sources_raid_ek_zg
        ${sources_raid_ek_zg_files}
    )
	
#Instance: Blackfathom Deeps Scripts
file(GLOB sources_instance_k_bdf_files scripts/kalimdor/blackfathom_deeps/*.cpp scripts/kalimdor/blackfathom_deeps/*.h)
    set(sources_instance_k_bdf
        ${sources_instance_k_bdf_files}
    )
	
#Instance: Dire Maul Scripts
file(GLOB sources_instance_k_dm_files scripts/kalimdor/dire_maul/*.cpp scripts/kalimdor/dire_maul/*.h)
    set(sources_instance_k_dm
        ${sources_instance_k_dm_files}
    )
	
#Instance: Maraudon Scripts
file(GLOB sources_instance_k_mara_files scripts/kalimdor/maraudon/*.cpp scripts/kalimdor/maraudon/*.h)
    set(sources_instance_k_mara
        ${sources_instance_k_mara_files}
    )

#Instance: Razorfen Downs Scripts
file(GLOB sources_instance_k_rfd_files scripts/kalimdor/razorfen_downs/*.cpp scripts/kalimdor/razorfen_downs/*.h)
    set(sources_instance_k_rfd
        ${sources_instance_k_rfd_files}
    )
	
#Instance: Razorfen Kraul Scripts
file(GLOB sources_instance_k_rfk_files scripts/kalimdor/razorfen_kraul/*.cpp scripts/kalimdor/razorfen_kraul/*.h)
    set(sources_instance_k_rfk
        ${sources_instance_k_rfk_files}
    )

#Instance: Wailing Caverns Scripts
file(GLOB sources_instance_k_wc_files scripts/kalimdor/wailing_caverns/*.cpp scripts/kalimdor/wailing_caverns/*.h)
    set(sources_instance_k_wc
        ${sources_instance_k_wc_files}
    )
	
#Instance: Zul Farrak Scripts
file(GLOB sources_instance_k_zf_files scripts/kalimdor/zulfarrak/*.cpp scripts/kalimdor/zulfarrak/*.h)
    set(sources_instance_k_zf
        ${sources_instance_k_zf_files}
    )
	
#Raid: Onyxias Lair Scripts
file(GLOB sources_raid_k_ony_files scripts/kalimdor/onyxias_lair/*.cpp scripts/kalimdor/onyxias_lair/*.h)
    set(sources_raid_k_ony
        ${sources_raid_k_ony_files}
    )

#Raid: Ruins of AQ Scripts
file(GLOB sources_raid_k_raq_files scripts/kalimdor/ruins_of_ahnqiraj/*.cpp scripts/kalimdor/ruins_of_ahnqiraj/*.h)
    set(sources_raid_k_raq
        ${sources_raid_k_raq_files}
    )

#Raid: Temple of AQ Scripts
file(GLOB sources_raid_k_taq_files scripts/kalimdor/temple_of_ahnqiraj/*.cpp scripts/kalimdor/temple_of_ahnqiraj/*.h)
    set(sources_raid_k_taq
        ${sources_raid_k_taq_files}
    )

## magic to include revision data in SD2 version string
# revision.h: FORCE
#   $(top_builddir)/src/tools/genrevision/genrevision $(srcdir)

file(GLOB_RECURSE mangosscript_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.cpp *.h)

source_group("Other"
  REGULAR_EXPRESSION .*
)
	
set(mangosscript_LIB_SRCS
    ${sources}
    ${sources_battlegrounds}
    ${sources_world}
    ${sources_eastern_kingdoms}
    ${sources_kalimdor}
    ${sources_instance_ek_brd}
    ${sources_instance_ek_brs}
    ${sources_instance_ek_tdm}
    ${sources_instance_ek_gno}
    ${sources_instance_ek_sm}
    ${sources_instance_ek_scholo}
    ${sources_instance_ek_sfk}
    ${sources_instance_ek_strat}
    ${sources_instance_ek_st}
    ${sources_instance_ek_uld}
    ${sources_raid_ek_mc}
    ${sources_raid_ek_bwl}
    ${sources_raid_ek_naxx}
    ${sources_raid_ek_zg}
    ${sources_instance_k_bdf}
    ${sources_instance_k_dm}
    ${sources_instance_k_mara}
    ${sources_instance_k_rfd}
    ${sources_instance_k_rfk}
    ${sources_instance_k_wc}
    ${sources_instance_k_zf}
    ${sources_raid_k_ony}
    ${sources_raid_k_raq}
    ${sources_raid_k_taq}
)

mangos_source_group(${mangosscript_LIB_SRCS})

# mangos_source_group_topic(${sources_battlegrounds} "Battlegrounds")
# mangos_source_group_topic(${sources_world} "Generic")
# mangos_source_group_topic(${sources_eastern_kingdoms} "Eastern Kingdoms")
# mangos_source_group_topic(${sources_kalimdor} "Kalimdor")
# mangos_source_group_topic(${sources_instance_ek_brd} "Instances\\Blackrock Depths")
# mangos_source_group_topic(${sources_instance_ek_brs} "Instances\\Blackrock Spire")
# mangos_source_group_topic(${sources_instance_ek_tdm} "Instances\\The Deadmines")
# mangos_source_group_topic(${sources_instance_ek_gno} "Instances\\Gnomeregan")
# mangos_source_group_topic(${sources_instance_ek_sm} "Instances\\Scarlet Monastery")
# mangos_source_group_topic(${sources_instance_ek_scholo} "Instances\\Scholomance")
# mangos_source_group_topic(${sources_instance_ek_sfk} "Instances\\Shadowfang Keep")
# mangos_source_group_topic(${sources_instance_ek_strat} "Instances\\Stratholme")
# mangos_source_group_topic(${sources_instance_ek_st} "Instances\\Sunken Temple")
# mangos_source_group_topic(${sources_instance_ek_uld} "Instances\\Uldaman")
# mangos_source_group_topic(${sources_raid_ek_mc} "Raids\\Molten Core")
# mangos_source_group_topic(${sources_raid_ek_bwl} "Raids\\Blackwing Lair")
# mangos_source_group_topic(${sources_raid_ek_naxx} "Raids\\Naxxramas")
# mangos_source_group_topic(${sources_raid_ek_zg} "Raids\\Zul Gurub")
# mangos_source_group_topic(${sources_instance_k_bdf} "Instances\\Blackfathom Deeps")
# mangos_source_group_topic(${sources_instance_k_dm} "Instances\\Dire Maul")
# mangos_source_group_topic(${sources_instance_k_mara} "Instances\\Maraudon")
# mangos_source_group_topic(${sources_instance_k_rfd} "Instances\\Razorfen Downs")
# mangos_source_group_topic(${sources_instance_k_rfk} "Instances\\Razorfen Kraul")
# mangos_source_group_topic(${sources_instance_k_wc} "Instances\\Wailing Caverns")
# mangos_source_group_topic(${sources_instance_k_zf} "Instances\\Zul Farrak")
# mangos_source_group_topic(${sources_raid_k_ony} "Raids\\Onyxias Lair")
# mangos_source_group_topic(${sources_raid_k_raq} "Raids\\Ruins of AhnQiraj")
# mangos_source_group_topic(${sources_raid_k_taq} "Raids\\Temple of AhnQiraj")

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/base"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/src/shared"
  "${CMAKE_SOURCE_DIR}/src/framework"
  "${CMAKE_SOURCE_DIR}/src/game/Server"
  "${CMAKE_SOURCE_DIR}/src/game/BattleGround"
  "${CMAKE_SOURCE_DIR}/src/game/WorldHandlers"
  "${CMAKE_SOURCE_DIR}/src/game/Object"
  "${CMAKE_SOURCE_DIR}/src/game/References"
  "${CMAKE_SOURCE_DIR}/src/game/MotionGenerators"
  "${CMAKE_SOURCE_DIR}/src/game/vmap"
  "${CMAKE_SOURCE_DIR}/dep/include"
  "${CMAKE_BINARY_DIR}"
  "${CMAKE_BINARY_DIR}/src/shared"
  "${ACE_INCLUDE_DIR}"
  "${MYSQL_INCLUDE_DIR}"
  "${CMAKE_SOURCE_DIR}/src/mangosd"
)

if(PCH)
  include_directories(
    "${CMAKE_CURRENT_BINARY_DIR}"
  )
endif()

add_library(mangosscript SHARED
  ${mangosscript_LIB_SRCS}
)

add_dependencies(mangosscript revision.h)
if(NOT ACE_USE_EXTERNAL)
  add_dependencies(mangosscript ace)
endif()

target_link_libraries(mangosscript 
  ${ZLIB_LIBRARIES}
  ${ACE_LIBRARIES}
)

if(WIN32)
  add_dependencies(mangosscript mangosd)
  target_link_libraries(mangosscript
    ${CMAKE_BINARY_DIR}/src/mangosd/Release/mangosd.lib
  )
  #if(WIN32 AND PLATFORM MATCHES X86)
  #  target_link_libraries(mangosscript 
  #    debug ${WIN_DEBUGLIBS}
  #  )
  #endif()
endif()

if(UNIX)
  set(mangosscript_LINK_FLAGS "-pthread")
  if(APPLE)
    set(mangosscript_LINK_FLAGS "-framework Carbon ${mangosscript_LINK_FLAGS}")
    # Needed for the linking because of the missing symbols
    set(mangosscript_LINK_FLAGS "-Wl,-undefined -Wl,dynamic_lookup ${mangosscript_LINK_FLAGS}")
  endif()

  if(APPLE)
    set(mangosscript_PROPERTIES INSTALL_NAME_DIR "${LIBS_DIR}")
  else()
    set(mangosscript_PROPERTIES INSTALL_RPATH ${LIBS_DIR})
  endif()

  # Run out of build tree
  set(mangosscript_PROPERTIES
    ${mangosscript_PROPERTIES}
    BUILD_WITH_INSTALL_RPATH OFF
  )

  set_target_properties(mangosscript PROPERTIES
    LINK_FLAGS ${mangosscript_LINK_FLAGS}
    ${mangosscript_PROPERTIES}
  )
endif()

# Because size for linker is to big - seriously ?!
if(WIN32)
  set_target_properties(mangosscript PROPERTIES
      LINK_FLAGS_DEBUG "/DEBUG /INCREMENTAL:NO"
  )
endif()

## libtool settings
#  API versioning
#  Link against dependencies
#  How to increase version info:
#  - only bug fixes implemented:
#    bump the version to LTMANGOS_CURRENT:LTMANGOS_REVISION+1:LTMANGOS_AGE
#  - augmented the interface:
#    bump the version to LTMANGOS_CURRENT+1:0:LTMANGOS_AGE+1
#  - broken old interface:
#    bump the version to LTMANGOS_CURRENT+1:0:0
# set(LTMANGOS_CURRENT 0)
# set(LTMANGOS_REVISION 0)
# set(LTMANGOS_AGE 0)
# set_target_properties(script PROPERTIES LINK_FLAGS
#   "-version-info ${LTMANGOS_CURRENT}:${LTMANGOS_REVISION}:${LTMANGOS_AGE}"
# )

# Generate precompiled header
if(PCH)
  if(MSVC OR XCODE)
    if(MSVC)
      set(mangosscript_pch "${CMAKE_CURRENT_SOURCE_DIR}/include/precompiled.cpp")
    endif()
    add_native_precompiled_header(mangosscript "${CMAKE_CURRENT_SOURCE_DIR}/include/precompiled.h")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    add_precompiled_header(mangosscript "${CMAKE_CURRENT_SOURCE_DIR}/include/precompiled.h")
  endif()
endif()

# LIBRARY = dyld / so, RUNTIME = dll
install(TARGETS mangosscript 
  LIBRARY DESTINATION "${LIBS_DIR}"
  RUNTIME DESTINATION "${LIBS_DIR}"
)