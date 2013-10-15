# ScriptDev2 is an extension for mangos-zero providing enhanced features for
# area triggers, creatures, game objects, instances, items, and spells beyond
# the default database scripting in mangos-zero.
#
# Copyright (C) 2006-2013 ScriptDev2 <http://www.scriptdev2.com/>
#
# ***** BEGIN GPL LICENSE BLOCK *****
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
    ScriptDevMgr.cpp
    base/escort_ai.cpp
    base/follower_ai.cpp
    base/guard_ai.cpp
    base/pet_ai.cpp

    include/precompiled.cpp
    include/sc_creature.cpp
    include/sc_grid_searchers.cpp
    include/sc_instance.cpp

    system/MangosdRev.cpp
    system/ScriptLoader.cpp
    system/system.cpp

    scripts/eastern_kingdoms/alterac_mountains.cpp
    scripts/eastern_kingdoms/arathi_highlands.cpp
    scripts/eastern_kingdoms/blasted_lands.cpp
    scripts/eastern_kingdoms/boss_kazzak.cpp
    scripts/eastern_kingdoms/burning_steppes.cpp
    scripts/eastern_kingdoms/dun_morogh.cpp
    scripts/eastern_kingdoms/eastern_plaguelands.cpp
    scripts/eastern_kingdoms/elwynn_forest.cpp
    scripts/eastern_kingdoms/hinterlands.cpp
    scripts/eastern_kingdoms/ironforge.cpp
    scripts/eastern_kingdoms/loch_modan.cpp
    scripts/eastern_kingdoms/redridge_mountains.cpp
    scripts/eastern_kingdoms/searing_gorge.cpp
    scripts/eastern_kingdoms/silverpine_forest.cpp
    scripts/eastern_kingdoms/stormwind_city.cpp
    scripts/eastern_kingdoms/stranglethorn_vale.cpp
    scripts/eastern_kingdoms/swamp_of_sorrows.cpp
    scripts/eastern_kingdoms/tirisfal_glades.cpp
    scripts/eastern_kingdoms/undercity.cpp
    scripts/eastern_kingdoms/western_plaguelands.cpp
    scripts/eastern_kingdoms/westfall.cpp
    scripts/eastern_kingdoms/wetlands.cpp

    scripts/kalimdor/ashenvale.cpp
    scripts/kalimdor/azshara.cpp
    scripts/kalimdor/boss_azuregos.cpp
    scripts/kalimdor/darkshore.cpp
    scripts/kalimdor/desolace.cpp
    scripts/kalimdor/durotar.cpp
    scripts/kalimdor/dustwallow_marsh.cpp
    scripts/kalimdor/felwood.cpp
    scripts/kalimdor/feralas.cpp
    scripts/kalimdor/moonglade.cpp
    scripts/kalimdor/mulgore.cpp
    scripts/kalimdor/orgrimmar.cpp
    scripts/kalimdor/silithus.cpp
    scripts/kalimdor/stonetalon_mountains.cpp
    scripts/kalimdor/tanaris.cpp
    scripts/kalimdor/teldrassil.cpp
    scripts/kalimdor/the_barrens.cpp
    scripts/kalimdor/thousand_needles.cpp
    scripts/kalimdor/thunder_bluff.cpp
    scripts/kalimdor/ungoro_crater.cpp
    scripts/kalimdor/winterspring.cpp

    scripts/world/areatrigger_scripts.cpp
    scripts/world/bosses_emerald_dragons.cpp
    scripts/world/go_scripts.cpp
    scripts/world/guards.cpp
    scripts/world/item_scripts.cpp
    scripts/world/mob_generic_creature.cpp
    scripts/world/npc_professions.cpp
    scripts/world/npcs_special.cpp
    scripts/world/spell_scripts.cpp
    scripts/world/world_map_scripts.cpp

    scripts/battlegrounds/battleground.cpp

    scripts/eastern_kingdoms/blackrock_depths/blackrock_depths.cpp
    scripts/eastern_kingdoms/blackrock_depths/boss_ambassador_flamelash.cpp
    scripts/eastern_kingdoms/blackrock_depths/boss_emperor_dagran_thaurissan.cpp
    scripts/eastern_kingdoms/blackrock_depths/boss_general_angerforge.cpp
    scripts/eastern_kingdoms/blackrock_depths/boss_high_interrogator_gerstahn.cpp
    scripts/eastern_kingdoms/blackrock_depths/instance_blackrock_depths.cpp

    scripts/eastern_kingdoms/blackrock_spire/boss_gyth.cpp
    scripts/eastern_kingdoms/blackrock_spire/boss_overlord_wyrmthalak.cpp
    scripts/eastern_kingdoms/blackrock_spire/boss_pyroguard_emberseer.cpp
    scripts/eastern_kingdoms/blackrock_spire/instance_blackrock_spire.cpp

    scripts/eastern_kingdoms/blackwing_lair/boss_broodlord_lashlayer.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_chromaggus.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_ebonroc.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_firemaw.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_flamegor.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_nefarian.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_razorgore.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_vaelastrasz.cpp
    scripts/eastern_kingdoms/blackwing_lair/boss_victor_nefarius.cpp
    scripts/eastern_kingdoms/blackwing_lair/instance_blackwing_lair.cpp

    scripts/eastern_kingdoms/deadmines/boss_mr_smite.cpp
    scripts/eastern_kingdoms/deadmines/deadmines.cpp
    scripts/eastern_kingdoms/deadmines/instance_deadmines.cpp

    scripts/eastern_kingdoms/gnomeregan/boss_thermaplugg.cpp
    scripts/eastern_kingdoms/gnomeregan/gnomeregan.cpp
    scripts/eastern_kingdoms/gnomeregan/instance_gnomeregan.cpp

    scripts/eastern_kingdoms/molten_core/boss_baron_geddon.cpp
    scripts/eastern_kingdoms/molten_core/boss_garr.cpp
    scripts/eastern_kingdoms/molten_core/boss_gehennas.cpp
    scripts/eastern_kingdoms/molten_core/boss_golemagg.cpp
    scripts/eastern_kingdoms/molten_core/boss_lucifron.cpp
    scripts/eastern_kingdoms/molten_core/boss_magmadar.cpp
    scripts/eastern_kingdoms/molten_core/boss_majordomo_executus.cpp
    scripts/eastern_kingdoms/molten_core/boss_ragnaros.cpp
    scripts/eastern_kingdoms/molten_core/boss_shazzrah.cpp
    scripts/eastern_kingdoms/molten_core/boss_sulfuron_harbinger.cpp
    scripts/eastern_kingdoms/molten_core/instance_molten_core.cpp
    scripts/eastern_kingdoms/molten_core/molten_core.cpp

    scripts/eastern_kingdoms/naxxramas/boss_anubrekhan.cpp
    scripts/eastern_kingdoms/naxxramas/boss_faerlina.cpp
    scripts/eastern_kingdoms/naxxramas/boss_four_horsemen.cpp
    scripts/eastern_kingdoms/naxxramas/boss_gluth.cpp
    scripts/eastern_kingdoms/naxxramas/boss_gothik.cpp
    scripts/eastern_kingdoms/naxxramas/boss_grobbulus.cpp
    scripts/eastern_kingdoms/naxxramas/boss_heigan.cpp
    scripts/eastern_kingdoms/naxxramas/boss_kelthuzad.cpp
    scripts/eastern_kingdoms/naxxramas/boss_loatheb.cpp
    scripts/eastern_kingdoms/naxxramas/boss_maexxna.cpp
    scripts/eastern_kingdoms/naxxramas/boss_noth.cpp
    scripts/eastern_kingdoms/naxxramas/boss_patchwerk.cpp
    scripts/eastern_kingdoms/naxxramas/boss_razuvious.cpp
    scripts/eastern_kingdoms/naxxramas/boss_sapphiron.cpp
    scripts/eastern_kingdoms/naxxramas/boss_thaddius.cpp
    scripts/eastern_kingdoms/naxxramas/instance_naxxramas.cpp

    scripts/eastern_kingdoms/scarlet_monastery/boss_arcanist_doan.cpp
    scripts/eastern_kingdoms/scarlet_monastery/boss_herod.cpp
    scripts/eastern_kingdoms/scarlet_monastery/boss_mograine_and_whitemane.cpp
    scripts/eastern_kingdoms/scarlet_monastery/instance_scarlet_monastery.cpp

    scripts/eastern_kingdoms/scholomance/boss_darkmaster_gandling.cpp
    scripts/eastern_kingdoms/scholomance/boss_jandice_barov.cpp
    scripts/eastern_kingdoms/scholomance/instance_scholomance.cpp

    scripts/eastern_kingdoms/shadowfang_keep/instance_shadowfang_keep.cpp
    scripts/eastern_kingdoms/shadowfang_keep/shadowfang_keep.cpp

    scripts/eastern_kingdoms/stratholme/boss_baroness_anastari.cpp
    scripts/eastern_kingdoms/stratholme/boss_cannon_master_willey.cpp
    scripts/eastern_kingdoms/stratholme/boss_dathrohan_balnazzar.cpp
    scripts/eastern_kingdoms/stratholme/boss_maleki_the_pallid.cpp
    scripts/eastern_kingdoms/stratholme/instance_stratholme.cpp
    scripts/eastern_kingdoms/stratholme/stratholme.cpp

    scripts/eastern_kingdoms/sunken_temple/instance_sunken_temple.cpp
    scripts/eastern_kingdoms/sunken_temple/sunken_temple.cpp

    scripts/eastern_kingdoms/uldaman/boss_archaedas.cpp
    scripts/eastern_kingdoms/uldaman/instance_uldaman.cpp
    scripts/eastern_kingdoms/uldaman/uldaman.cpp

    scripts/eastern_kingdoms/zulgurub/boss_arlokk.cpp
    scripts/eastern_kingdoms/zulgurub/boss_hakkar.cpp
    scripts/eastern_kingdoms/zulgurub/boss_hazzarah.cpp
    scripts/eastern_kingdoms/zulgurub/boss_jeklik.cpp
    scripts/eastern_kingdoms/zulgurub/boss_jindo.cpp
    scripts/eastern_kingdoms/zulgurub/boss_mandokir.cpp
    scripts/eastern_kingdoms/zulgurub/boss_marli.cpp
    scripts/eastern_kingdoms/zulgurub/boss_renataki.cpp
    scripts/eastern_kingdoms/zulgurub/boss_thekal.cpp
    scripts/eastern_kingdoms/zulgurub/boss_venoxis.cpp
    scripts/eastern_kingdoms/zulgurub/instance_zulgurub.cpp

    scripts/kalimdor/blackfathom_deeps/instance_blackfathom_deeps.cpp

    scripts/kalimdor/dire_maul/dire_maul.cpp
    scripts/kalimdor/dire_maul/instance_dire_maul.cpp

    scripts/kalimdor/maraudon/boss_noxxion.cpp
    scripts/kalimdor/onyxias_lair/boss_onyxia.cpp
    scripts/kalimdor/onyxias_lair/instance_onyxias_lair.cpp

    scripts/kalimdor/razorfen_downs/razorfen_downs.cpp
    scripts/kalimdor/razorfen_kraul/instance_razorfen_kraul.cpp
    scripts/kalimdor/razorfen_kraul/razorfen_kraul.cpp

    scripts/kalimdor/ruins_of_ahnqiraj/boss_ayamiss.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/boss_buru.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/boss_kurinnaxx.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/boss_moam.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/boss_ossirian.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/boss_rajaxx.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/instance_ruins_of_ahnqiraj.cpp
    scripts/kalimdor/ruins_of_ahnqiraj/ruins_of_ahnqiraj.cpp

    scripts/kalimdor/temple_of_ahnqiraj/boss_bug_trio.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_cthun.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_fankriss.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_huhuran.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_ouro.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_sartura.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_skeram.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_twinemperors.cpp
    scripts/kalimdor/temple_of_ahnqiraj/boss_viscidus.cpp
    scripts/kalimdor/temple_of_ahnqiraj/instance_temple_of_ahnqiraj.cpp
    scripts/kalimdor/temple_of_ahnqiraj/mob_anubisath_sentinel.cpp

    scripts/kalimdor/wailing_caverns/instance_wailing_caverns.cpp
    scripts/kalimdor/wailing_caverns/wailing_caverns.cpp

    scripts/kalimdor/zulfarrak/boss_zumrah.cpp
    scripts/kalimdor/zulfarrak/instance_zulfarrak.cpp
    scripts/kalimdor/zulfarrak/zulfarrak.cpp
)

set(headers
    sd2_revision_nr.h
    sd2_revision_sql.h
    ScriptDevMgr.h
    base/escort_ai.h
    base/follower_ai.h
    base/guard_ai.h
    base/pet_ai.h

    include/precompiled.h
    include/sc_creature.h
    include/sc_gossip.h
    include/sc_grid_searchers.h
    include/sc_instance.h

    system/system.h
    system/ScriptLoader.h

    scripts/world/world_map_scripts.h

    scripts/eastern_kingdoms/blackrock_depths/blackrock_depths.h
    scripts/eastern_kingdoms/blackrock_spire/blackrock_spire.h
    scripts/eastern_kingdoms/blackwing_lair/blackwing_lair.h
    scripts/eastern_kingdoms/deadmines/deadmines.h
    scripts/eastern_kingdoms/gnomeregan/gnomeregan.h
    scripts/eastern_kingdoms/molten_core/molten_core.h
    scripts/eastern_kingdoms/naxxramas/naxxramas.h
    scripts/eastern_kingdoms/scarlet_monastery/scarlet_monastery.h
    scripts/eastern_kingdoms/scholomance/scholomance.h
    scripts/eastern_kingdoms/shadowfang_keep/shadowfang_keep.h
    scripts/eastern_kingdoms/stratholme/stratholme.h
    scripts/eastern_kingdoms/sunken_temple/sunken_temple.h
    scripts/eastern_kingdoms/uldaman/uldaman.h
    scripts/eastern_kingdoms/zulgurub/zulgurub.h

    scripts/kalimdor/blackfathom_deeps/blackfathom_deeps.h
    scripts/kalimdor/dire_maul/dire_maul.h
    scripts/kalimdor/onyxias_lair/onyxias_lair.h
    scripts/kalimdor/razorfen_kraul/razorfen_kraul.h
    scripts/kalimdor/ruins_of_ahnqiraj/ruins_of_ahnqiraj.h
    scripts/kalimdor/temple_of_ahnqiraj/temple_of_ahnqiraj.h
    scripts/kalimdor/wailing_caverns/wailing_caverns.h
    scripts/kalimdor/zulfarrak/zulfarrak.h
)

set(mangosscript_LIB_SRCS ${sources} ${headers})

mangos_source_group(${mangosscript_LIB_SRCS})

include_directories(
    ${ACE_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    # ${OPENSSL_INCLUDE_DIR}
    # ${ZLIB_INCLUDE_DIR}
    # ${CMAKE_SOURCE_DIR}/dep/include/g3dlite/
    # ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include/
    ${CMAKE_SOURCE_DIR}/src/framework/
    ${CMAKE_SOURCE_DIR}/src/shared/
    ${CMAKE_SOURCE_DIR}/src/game/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/base/
    ${CMAKE_CURRENT_SOURCE_DIR}/system/
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/src/shared/
)

#-----------------------------------------------------------------------------
# Dump generated headers and add custom target for version control information
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-sd2.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-sd2.h)

#-----------------------------------------------------------------------------
# Build the scriptdev2 library
add_library(mangos-scripts SHARED ${mangosscript_LIB_SRCS})

#-----------------------------------------------------------------------------
# Link the scriptdev2 library
#
# NOTE: this a hack, required for Windows to make it possible to actually use
#       the library. This will be dropped once we have Lua working.
if(WIN32 AND MSVC)
    target_link_libraries(mangos-scripts mangosd ${ACE_LIBRARIES}) # ${MYSQL_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES}
endif()

#-----------------------------------------------------------------------------
# Build and install the scriptdev2 files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scriptdev2.conf.dist.cmake ${CMAKE_CURRENT_BINARY_DIR}/scriptdev2.conf.dist)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/scriptdev2.conf.dist DESTINATION ${CONF_DIR})

install(TARGETS mangos-scripts
    DESTINATION ${LIBS_DIR}
    LIBRARY DESTINATION ${LIBS_DIR}
)
