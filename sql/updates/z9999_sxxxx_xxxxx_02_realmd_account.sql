DROP TABLE IF EXISTS `warden_data_result`;

CREATE TABLE `warden_data_result` (
  `check` int(3) DEFAULT NULL,
  `data` tinytext,
  `str` tinytext,
  `address` int(8) DEFAULT NULL,
  `length` int(2) DEFAULT NULL,
  `result` tinytext,
  `comment` text
) ENGINE=MyISAM DEFAULT CHARSET=utf8;