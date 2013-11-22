CHANGELOG for 0.19.x
====================

This change log references the relevant changes (bug and security fixes) done
in 0.19 minor versions.

0.19.0 (2013-12-XX)
-------------------
Major changes for this build which require your attention when upgrading include
awesome things such as these:

* By default we now ship [Lua](http://www.lua.org/) version 5.1 scripting instead
  of **ScriptDev2**. You can still enable SD2 during CMake confguration, but we
  highly recommend to port your C++ scripts to Lua, since SD2 will be removed in
  the next major release 0.20.0
* The default world server database has been replaced, with a clean, basic version
  containing everything required to create characters, and walk the world.

Also numerous minor fixes and improvements have been added, such as:

* Windows binaries will now be created in one directory instead of different
  output directories.
* By default, when configuring *mangos-zero* via CMake, we will create Release
  builds.
* [OpenSSL](http://www.openssl.org/) is now properly mentioned in the README, as
  we depend on it.
* A race condition in our threading implementation has been resolved.
* git_id will create SQL which looks more like the format which the original
  `mysqldump` command would create.
* The script command SCRIPT_COMMAND_EMOTE can now display a random emote, if
  multiple parameters are provided.
* *mangos-zero* will now properly report as *x86* architecture on 32 bit builds.
* Trap game objects will now despawn with their parent object. A special case for
  the quest Gordunni Cobalt has been added, along with script support.
