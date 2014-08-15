-- Update table structure for one-hand/two-hand custom spell coeff.
-- Add also support of custom coeff for done/taken damage.
ALTER TABLE `mangos`.`spell_bonus_data`
ADD COLUMN `one_hand_direct_bonus` FLOAT NOT NULL DEFAULT 0 AFTER `direct_bonus`,
ADD COLUMN `two_hand_direct_bonus` FLOAT NOT NULL DEFAULT 0 AFTER `one_hand_direct_bonus`,
ADD COLUMN `direct_bonus_done` FLOAT NOT NULL DEFAULT 0 AFTER `two_hand_direct_bonus`,
ADD COLUMN `one_hand_direct_bonus_done` FLOAT NOT NULL DEFAULT 0 AFTER `direct_bonus_done`,
ADD COLUMN `one_hand_direct_bonus_done` FLOAT NOT NULL DEFAULT 0 AFTER `one_hand_direct_bonus_done`,
ADD COLUMN `direct_bonus_taken` FLOAT NOT NULL DEFAULT 0 AFTER `two_hand_direct_bonus_done`,
ADD COLUMN `one_hand_direct_bonus_taken` FLOAT NOT NULL DEFAULT 0 AFTER `direct_bonus_taken`,
ADD COLUMN `two_hand_direct_bonus_taken` FLOAT NOT NULL DEFAULT 0 AFTER `one_hand_direct_bonus_taken`;