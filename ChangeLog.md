CHANGELOG for 0.18.x
====================

This changelog references the relevant changes (bug and security fixes) done
in 0.18 minor versions.

0.18.1 (2013-XX-XX)
-------------------
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

0.18.0 (2013-08-31)
-------------------
Major changes for this build which require your attention when upgrading include
awesome things such as these:

* A build fix for FreeBSD has been added, thanks to @bels. *mangos-zero* should
  now successfully build again.
* In-game channels *Local defense* and zone channels no longer have characters as
  owners.
* Creature emotes have been fixed, and work again.
* Weather updates for zones without any defined weather have been fixed. A zone
  without weather will no longer cause the client to play random sounds.
* Spell linking based on conditions has been added. The table `spell_linked`
  now allows you to cast additional spells when a spell was cast based on a set
  of conditions.
* The table `scripted_event_id` has been renamed to `scripted_event`.
* `dbscripts_...` received a new command: `SCRIPT_COMMAND_TURN_TO` allows to
  turn creatures towards a target.
* EventAI received a new action: `ACTION_T_SUMMON_UNIQUE` which allows to
  summon a unique creature, which means the summon target can only be summoned
  once.
* The Scripting API has been streamlined to use more consistent function naming
  for all exported functions.

The following highlights the changes to the Scripting API:

* `isVendor` renamed to `IsVendor`
* `isTrainer` renamed to `IsTrainer`
* `isQuestGiver` renamed to `IsQuestGiver`
* `isGossip` renamed to `IsGossip`
* `isTaxi` renamed to `IsTaxi`
* `isGuildMaster` renamed to `IsGuildMaster`
* `isBattleMaster` renamed to `IsBattleMaster`
* `isBanker` renamed to `IsBanker`
* `isInnkeeper` renamed to `IsInnkeeper`
* `isSpiritHealer` renamed to `IsSpiritHealer`
* `isSpiritGuide` renamed to `IsSpiritGuide`
* `isTabardDesigner` renamed to `IsTabardDesigner`
* `isAuctioneer` renamed to `IsAuctioneer`
* `isArmorer` renamed to `IsArmorer`
* `isServiceProvider` renamed to `IsServiceProvider`
* `isSpiritService` renamed to `IsSpiritService`
* `isInCombat` renamed to `IsInCombat`
* `isFeared` renamed to `IsFeared`
* `isInRoots` renamed to `IsInRoots`
* `isFrozen` renamed to `IsFrozen`
* `isTargetableForAttack` renamed to `IsTargetableForAttack`
* `isAlive` renamed to `IsAlive`
* `isDead` renamed to `IsDead`
* `getDeathState` renamed to `GetDeathState`
* `isCharmedOwnedByPlayerOrPlayer` renamed to `IsCharmedOwnedByPlayerOrPlayer`
* `isCharmed` renamed to `IsCharmed`
* `isVisibleForOrDetect` renamed to `IsVisibleForOrDetect`
* `canDetectInvisibilityOf` renamed to `CanDetectInvisibilityOf`
* `isVisibleForInState` renamed to `IsVisibleForInState`
* `isInvisibleForAlive` renamed to `IsInvisibleForAlive`
* `getThreatManager` renamed to `GetThreatManager`
* `addHatedBy` renamed to `AddHatedBy`
* `removeHatedBy` renamed to `RemoveHatedBy`
* `getHostileRefManager` renamed to `GetHostileRefManager`
* `setTransForm` renamed to `SetTransform`
* `getTransForm` renamed to `GetTransform`
* `isHover` renamed to `IsHover`
* `addFollower` renamed to `AddFollower`
* `removeFollower` renamed to `RemoveFollower`
* `propagateSpeedChange` renamed to `PropagateSpeedChange`

Also numerous minor fixes and improvements have been added, such as:

* We've continued our research on client data, and resolved another batch of
  unknown variables and flags with their proper values including spell families
  and item classes.
* A few compile time warnings have been resolved, as well as a number of
  possible security issues, thanks to @Coverity scanning service for OS
  projects!
* Spells rewarding spells, and/or casting spells on reward will now cast the
  proper spell. Also quest givers will be able to cast spells ignoring Mana
  rewuirements when they are out of combat on reward.
* Documentation for many parts of the source code has been extended.
* An issue in the realm list server has been fixed, where it would loose the
  connection to MySQL.
* When casting [Soothe Animal](http://www.wowhead.com/spell=2908), the level
  of the targetted creature will be checked.
* The map extratcor build for Linux was fixed, and builds properly again.
* A fix for applying speed for fleeing creatures was added.
