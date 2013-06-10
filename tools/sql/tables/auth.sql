CREATE TABLE IF NOT EXISTS `account` (
      `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
      `username` varchar(32) NOT NULL DEFAULT '',
      `password` varchar(40) NOT NULL DEFAULT '',
      `email` varchar(254) NOT NULL DEFAULT '',
      PRIMARY KEY (`id`),
      UNIQUE KEY `idx_username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Account System';

CREATE TABLE IF NOT EXISTS `account_access` (
      `id` int(10) unsigned NOT NULL,
      `access_level` tinyint(3) unsigned NOT NULL,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
