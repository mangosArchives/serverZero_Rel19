ALTER TABLE  `db_version` CHANGE `required_r2420_01_mangos_spell_linked` `required_r2434_01_mangos_scripted_event` BIT(1) NULL DEFAULT NULL;

RENAME TABLE  `zp_world_full`.`scripted_event_id` TO  `zp_world_full`.`scripted_event` ;
