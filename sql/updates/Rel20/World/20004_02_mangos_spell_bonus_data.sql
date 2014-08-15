-- Seal of Righteousness must get 12,5% spell bonus for 2-handed weapon and 10% spell bonus for 1-handed weapon.
-- Trigerred spell must have 0% coeff.
UPDATE `mangos`.`spell_bonus_data` SET `entry`='20154', `direct_bonus`='0', `one_hand_direct_bonus`='0.125', `two_hand_direct_bonus`='0.1' ,`ap_bonus`='0' WHERE `entry`='25742';


