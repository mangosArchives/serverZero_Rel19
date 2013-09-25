CHANGELOG for 0.18.x
====================

This changelog references the relevant changes (bug and security fixes) done
in 0.18 minor versions.

* 0.18.1 (2013-XX-XX)

Major changes for this build which require your attention when upgrading include
awesome things such as these:

 * The *mangos-zero* build system has been overhauled, and we are now using CMake
   only. For Linux and FreeBSD users this means you can *always* use packages as
   provided by your distribution, and for Windows users this means you'll now
   have to download and install dependencies just once. Build times for all of
   the supported platforms should have noticeable reduced.
 * The tools for map extraction and generation from the game client are finally
   first class citizens when you build *mangos-zero*, and will be built, too.
 * SOAP bindings for the world server are now optional, and will be disabled by
   default when building *mangos-zero*. If you need them, there is a CMake switch
   available to enable the bindings.
 * Documentation has been rewritten and converted to **Markdown** format, which
   is readable and converts nicely to HTML when viewing in the repository browser.
 * Player movement has been rewritten, and now factors in possible issues such as
   lag when sending out character movement. This also means, looting when moving
   is no longer possible, and will be cancelled.
 * EventAI is now more verbose, and will validate targets for commands upon server
   start-up. It's very likely that you will see many more errors now. Additionally
   the `npc aiinfo` command will display more useful info.

Also numerous minor fixes and improvements have been added, such as:

 * Using potions for power types not used by a class will now raise the correct
   error messages, e.g. Warriors can no longer consume Mana potions.
 * Hunter pets will receive full experience when their masters are grouped.
 * Mobs fleeing will do so now in normal speed, instead of crazy speed.
 * The world server will now provide improved, readable output on start-up, and
   less confusing messages for indentical issues.
 * In-game commands `goname` and `namego` have been replaced with `appear` and
   `summon`. If you happen to find other commands with weird naming, let us know!
 * We've done extensive house-keeping and removed many TBC specific code parts,
   and replaced TBC specific values with the proper vanilla WoW counterparts.
   This includes the TBC spell modifiers, which now have been dropped and are no
   longer available.

* 0.18.0 (2013-08-31)

 * Get rid of GCC warnings about comment style.
 * Renamed unknown spell family due to spells being environmental changes.
 * m-2436: Added better fix for #112.
 * NPC textemote fix
 * Removed comment. Quest types are correct, and can be found in QuestInfo.dbc.
 * m-2435: Updated the list of valid spell families, and removed invalid families.
 * Removed unwanted database name in update query.
 * m-2434: Renamed table scripted_event_id to scripted_event.
 * m-2433: Fixes #112.
 * missing part of UNK7
 * discovered SPELL_ATTR_UNK7
 * Lots of changes to function names: find . -type f -print0 | xargs -0 sed -i 's/isVendor/IsVendor/g' find . -type f -print0 | xargs -0 sed -i 's/isTrainer/IsTrainer/g' find . -type f -print0 | xargs -0 sed -i 's/isQuestGiver/IsQuestGiver/g' find . -type f -print0 | xargs -0 sed -i 's/isGossip/IsGossip/g' find . -type f -print0 | xargs -0 sed -i 's/isTaxi/IsTaxi/g' find . -type f -print0 | xargs -0 sed -i 's/isGuildMaster/IsGuildMaster/g' find . -type f -print0 | xargs -0 sed -i 's/isBattleMaster/IsBattleMaster/g' find . -type f -print0 | xargs -0 sed -i 's/isBanker/IsBanker/g' find . -type f -print0 | xargs -0 sed -i 's/isInnkeeper/IsInnkeeper/g' find . -type f -print0 | xargs -0 sed -i 's/isSpiritHealer/IsSpiritHealer/g' find . -type f -print0 | xargs -0 sed -i 's/isSpiritGuide/IsSpiritGuide/g' find . -type f -print0 | xargs -0 sed -i 's/isTabardDesigner/IsTabardDesigner/g' find . -type f -print0 | xargs -0 sed -i 's/isAuctioneer/IsAuctioneer/g' find . -type f -print0 | xargs -0 sed -i 's/isArmorer/IsArmorer/g' find . -type f -print0 | xargs -0 sed -i 's/isServiceProvider/IsServiceProvider/g' find . -type f -print0 | xargs -0 sed -i 's/isSpiritService/IsSpiritService/g' find . -type f -print0 | xargs -0 sed -i 's/isInCombat/IsInCombat/g' find . -type f -print0 | xargs -0 sed -i 's/isFeared/IsFeared/g' find . -type f -print0 | xargs -0 sed -i 's/isInRoots/IsInRoots/g' find . -type f -print0 | xargs -0 sed -i 's/isFrozen/IsFrozen/g' find . -type f -print0 | xargs -0 sed -i 's/isTargetableForAttack/IsTargetableForAttack/g' find . -type f -print0 | xargs -0 sed -i 's/isAlive/IsAlive/g' find . -type f -print0 | xargs -0 sed -i 's/isDead/IsDead/g' find . -type f -print0 | xargs -0 sed -i 's/getDeathState/GetDeathState/g' find . -type f -print0 | xargs -0 sed -i 's/isCharmedOwnedByPlayerOrPlayer/IsCharmedOwnedByPlayerOrPlayer/g' find . -type f -print0 | xargs -0 sed -i 's/isCharmed/IsCharmed/g' find . -type f -print0 | xargs -0 sed -i 's/isVisibleForOrDetect/IsVisibleForOrDetect/g' find . -type f -print0 | xargs -0 sed -i 's/canDetectInvisibilityOf/CanDetectInvisibilityOf/g' find . -type f -print0 | xargs -0 sed -i 's/isVisibleForInState/IsVisibleForInState/g' find . -type f -print0 | xargs -0 sed -i 's/isInvisibleForAlive/IsInvisibleForAlive/g' find . -type f -print0 | xargs -0 sed -i 's/getThreatManager/GetThreatManager/g' find . -type f -print0 | xargs -0 sed -i 's/addHatedBy/AddHatedBy/g' find . -type f -print0 | xargs -0 sed -i 's/removeHatedBy/RemoveHatedBy/g' find . -type f -print0 | xargs -0 sed -i 's/getHostileRefManager/GetHostileRefManager/g' find . -type f -print0 | xargs -0 sed -i 's/setTransForm/SetTransform/g' find . -type f -print0 | xargs -0 sed -i 's/getTransForm/GetTransform/g' find . -type f -print0 | xargs -0 sed -i 's/isHover/IsHover/g' find . -type f -print0 | xargs -0 sed -i 's/addFollower/AddFollower/g' find . -type f -print0 | xargs -0 sed -i 's/removeFollower/RemoveFollower/g' find . -type f -print0 | xargs -0 sed -i 's/propagateSpeedChange/PropagateSpeedChange/g'
 * Style change
 * Update ChangeLog.md
 * Add issues and contributions
 * Added ChangeLog template.
 * m-2432: Add fix for building on FreeBSD by @bels, thanks!
 * m-2431: Update to fix a channel issue where you wouldn't properly change channels upon landing after a flight path. Also add a small fix to the join code where we lookup if it's a static channel or not by using snprintf instead of printf
 * m-2430: Small update to fix #83 aswell, hopefully
 * m-2429: Attempt to fix #82 by looking up id's for the channels being joined which seems to have fixed it, also add a enum with id's for all channels that are special
 * m-2428: Small update to #82 so that players with .gm on can speak in LocalDefense and WorldDefense
 * Updated the list of ignored files and directories.
 * Fixed Coverity issue CID 1010430: CWE-476: NULL Pointer Dereference
 * revert old weather fix and added a better solution
 * RewSpell fix
 * weather sound fix
 * eventai.txt updated
 * added function 47 action_t_summon_unique to creatureeventai
 * ignore manarequirements for questgivers OOC
 * Update realmd.sql
 * m-2427: Add fix for building on FreeBSD by bels, thanks!
 * Added missing command SCRIPT_COMMAND_TURN_TO.
 * Removed TBC Darkmoon Fair holiday.
 * Increase the experience set
 * Custom pet experience
 * Custom pet experience
 * Custom pet experience
 * Update ExtractResources.sh
 * Update ExtractResources.sh
 * spelling corrections and explained options a little more
 * Aligned related columns to allow for proper relations.
 * m-doc: Move documentation for OpcodesList down in the document as suggested in 8f8970efa
 * m-doc: Small add to documentation of some turning functions and some about death
 * Should fix 1010380 and 1010379 in coverity
 * m-2425: Update realm daemon so that a lost mysql connection is reconnected instead of realmd stoppig to accept connections
 * Tiny fix, adding more checks.
 * m-doc: Small update to documentation, external docs for at least opcodes coming in soon
 * Removed definitions handled by CMake, and ensure WIN32 specific defs are only used there.
 * Replaced invalid character.
 * m-doc: Small documentation about how some of the packet processing works and a misc about items
 * m-doc: Add more documentation to 2 opcodes
 * m-doc: Document some opcodes to some extent, need to know if what's written is right
 * m-doc: Small misc changes here and there, add some comments from source to be parsed by doxygen
 * m-doc: Add some smaller docs to all the CastSpell that are very like each other
 * m-doc: Added https://github.com/mangoswiki/Wiki/wiki/Coding-Standards to the doxygen generated documentation aswell
 * m-doc: Update some of the conventions and fix small spelling mistakes
 * m-doc: Small fixes here and there to make doxygen at least parse some more data
 * m-doc: Small doc to accessibility and water
 * adding script command turn to
 * m-doc: Update documentation for Unit, add some more functions and some more questionmarks and todos
 * m-doc: Update AuctionHouse documentation to be included as files aswell
 * m-doc: Update some old documentation to use ref function etc
 * m-doc: Small misc updates to documentation
 * Update Doxyfile.in to include the DocStructure which is the main page and add some more groups to documentation. Also add some info about code style, not done at all, just a draft.
 * Some documentation clean up from /// to /** and more info added on some methods etc for the auction house
 * m-2424: sync'd realmd version with other cores
 * Minor changes to vs projects to match others
 * Update some of the AHbot docs to hopefully be parsed by Doxygen, will update this with some more docs soon enough aswell
 * some more docs in Unit
 * renamed an sql update file to match expected filename
 * Added some more doxygen doc headers
 * Add \todo tags instead of TODO:
 * Add doxygen to cmake, now it's possible to 'make doc'
 * Fix small error in doc
 * fixed typo in mangos.sql
 * Fix windows commandline build
 * m-2423: Now also check the level when casting soothe animal
 * m-2422: Fix mob fleeing speed
 * m-2421: fix soothe animal not working as intended
 * r-2420: add spell_linked table thanks to rsa and all other authors
 * m-2419:  adjust HandleModHitChance according to EquippedItemClass for spells like 22780
 * Adding some docs about dodge block parry critical chance
 * re-added gitignore files
 * fix build error caused by previous commit
 * Added some docs to SpellHits in different ways
 * More Doxygen fixes
 * Added some docs about calculating damage
 * Fixed doxygen doc flags
 * Added lots of additional notes and comments
 * removed some vc9 reminents
 * m-2418: Fix extractor for Linux.
 * m-2417: Do not use verbose builds by default.
 * m-2416: Updated console URL
 * zipped up ancient update sql
 * more code layout cleanup
 * minor formatting cleanup
 * m-2415: fix Potential buffer overflow in ad(extractor)
 * Some Visual Studio 2010 project file fixes
 * FastMM exclude platform specific version
 * Get rid of warning in game project
 * Get rid of warning in stdsoap2.cpp
 * Fix method call in g3dmath + typo
 * Revert "Correct use of false method in g3dmath"
 * Correct use of false method in g3dmath
 * Prevent commit of ReSharper directories
