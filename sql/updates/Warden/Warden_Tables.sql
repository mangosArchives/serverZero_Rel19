DROP TABLE IF EXISTS `warden_module`;
CREATE TABLE `warden_module` (
  `md5` char(32) NOT NULL default '',
  `chk0` tinyint(3) unsigned NOT NULL default '255',
  `chk1` tinyint(3) unsigned NOT NULL default '255',
  `chk2` tinyint(3) unsigned NOT NULL default '255',
  `chk3` tinyint(3) unsigned NOT NULL default '255',
  `chk4` tinyint(3) unsigned NOT NULL default '255',
  `chk5` tinyint(3) unsigned NOT NULL default '255',
  `chk6` tinyint(3) unsigned NOT NULL default '255',
  `chk7` tinyint(3) unsigned NOT NULL default '255',
  `chk8` tinyint(3) unsigned NOT NULL default '255',
  `end9` tinyint(3) unsigned NOT NULL default '255',
  PRIMARY KEY  (`md5`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Warden System';

DROP TABLE IF EXISTS `warden_check_driver`;
CREATE TABLE `warden_check_driver` (
  `Seed` int(10) unsigned NOT NULL,
  `SHA` char(40) NOT NULL,
  `String` char(15) NOT NULL,
  PRIMARY KEY (`Seed`,`SHA`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Warden system';

DROP TABLE IF EXISTS `warden_check_file`;
CREATE TABLE `warden_check_file` (
  `String` varchar(250) NOT NULL,
  `SHA` char(40) NOT NULL,
  PRIMARY KEY (`String`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Warden system';

DROP TABLE IF EXISTS `warden_check_lua`;
CREATE TABLE `warden_check_lua` (
  `String` varchar(250) NOT NULL,
  PRIMARY KEY (`String`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Warden system';

DROP TABLE IF EXISTS `warden_check_memory`;
CREATE TABLE `warden_check_memory` (
  `String` char(15) NOT NULL DEFAULT '',
  `Offset` int(10) unsigned NOT NULL,
  `Length` tinyint(3) unsigned NOT NULL,
  `Result` char(45) NOT NULL,
  `Comment` varchar(50) NOT NULL DEFAULT '',
  PRIMARY KEY (`Offset`,`Length`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Warden system';

DROP TABLE IF EXISTS `warden_check_page`;
CREATE TABLE `warden_check_page` (
  `Seed` int(10) unsigned NOT NULL,
  `SHA` char(40) NOT NULL,
  `Offset` int(10) unsigned NOT NULL,
  `Length` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY (`Seed`,`SHA`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Warden system';