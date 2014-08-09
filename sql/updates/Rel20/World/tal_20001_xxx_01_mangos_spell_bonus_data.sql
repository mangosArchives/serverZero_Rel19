-- Update table structure for one-hand/two-hand custom spell coeff.
ALTER TABLE `mangos`.`spell_bonus_data`
ADD COLUMN `one_hand_direct_bonus` FLOAT NOT NULL DEFAULT 0 AFTER `direct_bonus`,
ADD COLUMN `two_hand_direct_bonus` FLOAT NOT NULL DEFAULT 0 AFTER `one_hand_direct_bonus`;