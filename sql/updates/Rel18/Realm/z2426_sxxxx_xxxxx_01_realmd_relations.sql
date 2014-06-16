ALTER TABLE  `account` CHANGE  `id`  `id` INT( 11 ) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT  'Account identifier';
ALTER TABLE  `account_banned` CHANGE  `id`  `id` INT( 11 ) UNSIGNED NOT NULL COMMENT  'Account identifier';
ALTER TABLE  `realmcharacters` CHANGE  `realmid`  `realmid` INT( 11 ) UNSIGNED NOT NULL COMMENT  'Account identifier', CHANGE  `acctid`  `acctid` INT( 11 ) UNSIGNED NOT NULL COMMENT  'Realm identifier';
ALTER TABLE  `realmlist` CHANGE  `id`  `id` INT( 11 ) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT  'Realm identifier';
ALTER TABLE  `uptime` CHANGE  `realmid`  `realmid` INT( 11 ) UNSIGNED NOT NULL COMMENT  'Realm identifier';

ALTER TABLE realmd_db_version CHANGE COLUMN required_c12484_02_realmd_account_access required_z2426_01_realmd_relations BIT;
