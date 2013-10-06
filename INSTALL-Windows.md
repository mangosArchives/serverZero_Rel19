Installation in Windows
=======================
This guide describes how to build and install *mangos-zero* on the Windows platform.
With the recent changes to the build, the build now should require approximately
30 minutes to complete, and also may require roughly 15 minutes to prepare and
install packages such as the MySQL database server on which *mangos-zero* depends.

Introduction
------------
*mangos-zero* server supports a wide range of operating systems, and various
compiler platforms. In order to do that, we use various free cross-platform
libraries and use [CMake][19] to provide a cross-platform build system which
adapts to your chosen operating system and compiler.

Please use a version equal to or newer than CMake 2.8.11. Earlier versions may
have issues with Visual Studio 2012/2013.

In addition please install [Git][34]. If you prefer visual clients instead of
the Git command line, there is [github for Windows][35], and [SourceTree][36]
which supports both Git and Mercurial.

Compilers
---------
Building *mangos-zero* is currently possible with these compilers:

* **Microsoft Visual Studio (Express[^1])**, 32 bit and 64 bit. Both
  [Visual Studio][30] and the Express editions of [Visual Studio][31]
  are supported.
* **Microsoft Windows SDK**, 32 bit and 64 bit. The [Windows 7 SDK][32] is
  recommeded, as older versions lack compiler features required to build
  the server.

We do recommend to use *Visual Studio*, unless you are comfortable with using
the Windows command line and *nmake*.

[^1]: Visual Studio Express versions prior to the 2012 release can only
      build 32 bit applications, unless you install the Windows SDK.

[1]: http://blizzard.com/ "Blizzard Entertainment Inc. · we love you!"
[2]: http://blizzard.com/games/wow/ "World of Warcraft · Classic / Vanilla"
[3]: http://wowpedia.org/Beta#World_of_Warcraft "World of Warcraft - Classic Beta"
[4]: http://www.wowpedia.org/Patch_1.12.0 "Vanilla WoW · Patch 1.12.0 release notes"
[5]: http://www.wowpedia.org/Patch_1.12.1 "Vanilla WoW · Patch 1.12.1 release notes"
[6]: http://www.wowpedia.org/Patch_1.12.2 "Vanilla WoW · Patch 1.12.2 release notes"
[7]: http://www.cppreference.com/ "C / C++ reference"

[10]: http://getmangos.com/ "mangos · project site"
[11]: http://community.getmangos.co.uk/ "mangos · discussion forums"
[12]: http://github.com/mangoszero "mangos-zero · github organization"
[13]: http://github.com/mangoszero/server "mangos zero · server repository"
[14]: http://github.com/mangoszero/scripts "mangos zero · script extensions repository"
[15]: http://github.com/mangoszero/database "mangos zero · content database repository"
[16]: https://travis-ci.org/mangoszero/server "Travis CI · mangos-zero build status"
[17]: https://scan.coverity.com/ "Coverity Scan · Static Code Analysis"

[19]: http://www.cmake.org/ "CMake · Cross Platform Make"
[20]: http://windows.microsoft.com/ "Microsoft Windows · that OS, yes."
[21]: http://www.debian.org/ "Debian · The Universal Operating System"
[22]: http://www.ubuntu.com/ "Ubuntu · The world's most popular free OS"
[23]: http://www.freebsd.org/ "FreeBSD · The Power To Serve"
[24]: http://www.netbsd.org/ "NetBSD · The NetBSD Project"
[25]: http://www.openbsd.org/ "OpenBSD · Free, functional and secure"
[26]: http://www.dragonflybsd.org/ "DragonFlyBSD"

[30]: http://www.microsoft.com/visualstudio/eng/ "Visual Studio 2012"
[31]: http://www.microsoft.com/visualstudio/eng/products/visual-studio-express-products "Visual Studio Express 2012 for Windows Desktop"
[32]: http://www.microsoft.com/en-us/download/details.aspx?id=8279 "Windows SDK for Windows 7 and .NET Framework 4"
[33]: http://clang.llvm.org/ "clang · a C language family frontend for LLVM"
[34]: http://git-scm.com/ "Git · Distributed version control system"
[35]: http://windows.github.com/ "github · windows client"
[36]: http://www.sourcetreeapp.com/ "SourceTree · Free Mercurial and Git Client for Windows/Mac"

[40]: http://www.mysql.com/ "MySQL · The world's most popular open source database"
[41]: http://www.mariadb.org/ "MariaDB · An enhanced, drop-in replacement for MySQL"
[42]: http://www.postgresql.org/ "PostgreSQL · The world's most advanced open source database"
[43]: http://www.cs.wustl.edu/~schmidt/ACE.html "ACE · The ADAPTIVE Communication Environment"
[44]: http://github.com/memononen/recastnavigation "Recast · Navigation-mesh Toolset for Games"
[45]: http://sourceforge.net/projects/g3d/ "G3D · G3D Innovation Engine"
[46]: http://github.com/ge0rg/libmpq "libmpq · A library for reading data from MPQ archives"
[47]: http://www.threadingbuildingblocks.org/ "Intel Threading Building Blocks · TBB"
[48]: http://www.openssl.org/ "OpenSSL · The Open Source toolkit for SSL/TLS"
[49]: http://www.stack.nl/~dimitri/doxygen/ "Doxygen · API documentation generator"
[50]: http://www.lua.org/ "Lua · The Programming Language"
[51]: http://gnuwin32.sourceforge.net/packages/zlib.htm "Zlib for Windows"
[52]: http://gnuwin32.sourceforge.net/packages/bzip2.htm "Bzip2 for Windows"
