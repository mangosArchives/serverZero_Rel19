/**
 * This code is part of MaNGOS. Contributor & Copyright details are in AUTHORS/THANKS.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef AUCTION_HOUSE_BOT_H
#define AUCTION_HOUSE_BOT_H

#include "World.h"
#include "Config/Config.h"
#include "AuctionHouseMgr.h"
#include "SharedDefines.h"
#include "Item.h"

// shadow of ItemQualities with skipped ITEM_QUALITY_HEIRLOOM, anything after ITEM_QUALITY_ARTIFACT(6) in fact
enum AuctionQuality
{
    AUCTION_QUALITY_GREY   = ITEM_QUALITY_POOR,
    AUCTION_QUALITY_WHITE  = ITEM_QUALITY_NORMAL,
    AUCTION_QUALITY_GREEN  = ITEM_QUALITY_UNCOMMON,
    AUCTION_QUALITY_BLUE   = ITEM_QUALITY_RARE,
    AUCTION_QUALITY_PURPLE = ITEM_QUALITY_EPIC,
    AUCTION_QUALITY_ORANGE = ITEM_QUALITY_LEGENDARY,
    AUCTION_QUALITY_YELLOW = ITEM_QUALITY_ARTIFACT,
};

#define MAX_AUCTION_QUALITY 7

enum AuctionBotConfigUInt32Values
{
    CONFIG_UINT32_AHBOT_MAXTIME,
    CONFIG_UINT32_AHBOT_MINTIME,
    CONFIG_UINT32_AHBOT_ITEMS_PER_CYCLE_BOOST,
    CONFIG_UINT32_AHBOT_ITEMS_PER_CYCLE_NORMAL,
    CONFIG_UINT32_AHBOT_ALLIANCE_ITEM_AMOUNT_RATIO,
    CONFIG_UINT32_AHBOT_HORDE_ITEM_AMOUNT_RATIO,
    CONFIG_UINT32_AHBOT_NEUTRAL_ITEM_AMOUNT_RATIO,
    CONFIG_UINT32_AHBOT_ITEM_MIN_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_ITEM_MAX_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_ITEM_MIN_REQ_LEVEL,
    CONFIG_UINT32_AHBOT_ITEM_MAX_REQ_LEVEL,
    CONFIG_UINT32_AHBOT_ITEM_MIN_SKILL_RANK,
    CONFIG_UINT32_AHBOT_ITEM_MAX_SKILL_RANK,
    CONFIG_UINT32_AHBOT_ITEM_GREY_AMOUNT,
    CONFIG_UINT32_AHBOT_ITEM_WHITE_AMOUNT,
    CONFIG_UINT32_AHBOT_ITEM_GREEN_AMOUNT,
    CONFIG_UINT32_AHBOT_ITEM_BLUE_AMOUNT,
    CONFIG_UINT32_AHBOT_ITEM_PURPLE_AMOUNT,
    CONFIG_UINT32_AHBOT_ITEM_ORANGE_AMOUNT,
    CONFIG_UINT32_AHBOT_ITEM_YELLOW_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_CONSUMABLE_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_CONTAINER_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_WEAPON_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_GEM_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_ARMOR_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_REAGENT_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_PROJECTILE_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_TRADEGOOD_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_GENERIC_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_RECIPE_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_QUIVER_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_QUEST_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_KEY_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_MISC_AMOUNT,
    CONFIG_UINT32_AHBOT_CLASS_GLYPH_AMOUNT,
    CONFIG_UINT32_AHBOT_ALLIANCE_PRICE_RATIO,
    CONFIG_UINT32_AHBOT_HORDE_PRICE_RATIO,
    CONFIG_UINT32_AHBOT_NEUTRAL_PRICE_RATIO,
    CONFIG_UINT32_AHBOT_BUYER_CHANCE_RATIO_ALLIANCE,
    CONFIG_UINT32_AHBOT_BUYER_CHANCE_RATIO_HORDE,
    CONFIG_UINT32_AHBOT_BUYER_CHANCE_RATIO_NEUTRAL,
    CONFIG_UINT32_AHBOT_BUYER_RECHECK_INTERVAL,
    CONFIG_UINT32_AHBOT_CLASS_MISC_MOUNT_MIN_REQ_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_MISC_MOUNT_MAX_REQ_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_MISC_MOUNT_MIN_SKILL_RANK,
    CONFIG_UINT32_AHBOT_CLASS_MISC_MOUNT_MAX_SKILL_RANK,
    CONFIG_UINT32_AHBOT_CLASS_GLYPH_MIN_REQ_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_GLYPH_MAX_REQ_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_GLYPH_MIN_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_GLYPH_MAX_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_TRADEGOOD_MIN_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_TRADEGOOD_MAX_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_CONTAINER_MIN_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_CLASS_CONTAINER_MAX_ITEM_LEVEL,
    CONFIG_UINT32_AHBOT_UINT32_COUNT
};

enum AuctionBotConfigBoolValues
{
    CONFIG_BOOL_AHBOT_BUYER_ALLIANCE_ENABLED,
    CONFIG_BOOL_AHBOT_BUYER_HORDE_ENABLED,
    CONFIG_BOOL_AHBOT_BUYER_NEUTRAL_ENABLED,
    CONFIG_BOOL_AHBOT_ITEMS_VENDOR,
    CONFIG_BOOL_AHBOT_ITEMS_LOOT,
    CONFIG_BOOL_AHBOT_ITEMS_MISC,
    CONFIG_BOOL_AHBOT_BIND_NO,
    CONFIG_BOOL_AHBOT_BIND_PICKUP,
    CONFIG_BOOL_AHBOT_BIND_EQUIP,
    CONFIG_BOOL_AHBOT_BIND_USE,
    CONFIG_BOOL_AHBOT_BIND_QUEST,
    CONFIG_BOOL_AHBOT_BUYPRICE_SELLER,
    CONFIG_BOOL_AHBOT_BUYPRICE_BUYER,
    CONFIG_BOOL_AHBOT_DEBUG_SELLER,
    CONFIG_BOOL_AHBOT_DEBUG_BUYER,
    CONFIG_BOOL_AHBOT_SELLER_ENABLED,
    CONFIG_BOOL_AHBOT_BUYER_ENABLED,
    CONFIG_BOOL_AHBOT_LOCKBOX_ENABLED,
    CONFIG_UINT32_AHBOT_BOOL_COUNT
};

// All basic config data used by other AHBot classes for self-configure.
class AuctionBotConfig
{
    public:
        AuctionBotConfig();

        void        SetConfigFileName(char const* filename) { m_configFileName = filename; }
        bool        Initialize();
        const char* GetAHBotIncludes() const { return m_AHBotIncludes.c_str(); }
        const char* GetAHBotExcludes() const { return m_AHBotExcludes.c_str(); }

        uint32      getConfig(AuctionBotConfigUInt32Values index) const { return m_configUint32Values[index]; }
        bool        getConfig(AuctionBotConfigBoolValues index) const { return m_configBoolValues[index]; }
        void        setConfig(AuctionBotConfigBoolValues index, bool value) { m_configBoolValues[index] = value; }
        void        setConfig(AuctionBotConfigUInt32Values index, uint32 value) { m_configUint32Values[index] = value; }

        /** 
         * Gets the config item amount ratio.
         * 
         * @param houseType Type of the house.
         * @return 
         */
        uint32 getConfigItemAmountRatio(AuctionHouseType houseType) const;
        /** 
         * Gets the config buyer enabled.
         * 
         * @param houseType Type of the house.
         * <returns></returns
         */
        bool getConfigBuyerEnabled(AuctionHouseType houseType) const;
        /** 
         * Gets the config item quality amount.
         * 
         * @param quality The quality.
         * <returns></returns
         */
        uint32 getConfigItemQualityAmount(AuctionQuality quality) const;

        uint32      GetItemPerCycleBoost() const { return m_ItemsPerCycleBoost; }
        uint32      GetItemPerCycleNormal() const { return m_ItemsPerCycleNormal; }
        /** 
         * Reloads the AhBot config.
         * @return true if the config was successfully reloaded, false otherwise
         */
        bool        Reload();
        
        /** 
         * Gets the name of the item class.
         * 
         * @param itemclass The itemclass.
         */
        static char const* GetItemClassName(ItemClass itemclass);
        static char const* GetHouseTypeName(AuctionHouseType houseType);

    private:
        std::string m_configFileName;
        std::string m_AHBotIncludes;
        std::string m_AHBotExcludes;
        Config      m_AhBotCfg;
        uint32      m_ItemsPerCycleBoost;
        uint32      m_ItemsPerCycleNormal;

        uint32 m_configUint32Values[CONFIG_UINT32_AHBOT_UINT32_COUNT];
        bool   m_configBoolValues[CONFIG_UINT32_AHBOT_BOOL_COUNT];

        void SetAHBotIncludes(const std::string& AHBotIncludes) { m_AHBotIncludes = AHBotIncludes; }
        void SetAHBotExcludes(const std::string& AHBotExcludes) { m_AHBotExcludes = AHBotExcludes; }

        /** 
         * Sets the config.
         * 
         * @param index The index.
         * @param fieldname The fieldname.
         * @param defvalue The defvalue.
         */
        void setConfig(AuctionBotConfigUInt32Values index, char const* fieldname, uint32 defvalue);
        /** 
         * Sets the config max.
         * 
         * @param index The index.
         * @param fieldname The fieldname.
         * @param defvalue The defvalue.
         * @param maxvalue The maxvalue.
         */
        void setConfigMax(AuctionBotConfigUInt32Values index, char const* fieldname, uint32 defvalue, uint32 maxvalue);
        /** 
         * Sets the config min max.
         * 
         * @param index The index.
         * @param fieldname The fieldname.
         * @param defvalue The defvalue.
         * @param minvalue The minvalue.
         * @param maxvalue The maxvalue.
         */
        void setConfigMinMax(AuctionBotConfigUInt32Values index, char const* fieldname, uint32 defvalue, uint32 minvalue, uint32 maxvalue);
        /** 
         * Sets the config.
         * 
         * @param index The index.
         * @param fieldname The fieldname.
         * @param defvalue The defvalue.
         */
        void setConfig(AuctionBotConfigBoolValues index, char const* fieldname, bool defvalue);
        /** 
         * Get AuctionHousebot configuration file
         */
        void GetConfigFromFile();
};

#define sAuctionBotConfig MaNGOS::Singleton<AuctionBotConfig>::Instance()

class AuctionBotAgent
{
    public:
        AuctionBotAgent() {}
        virtual ~AuctionBotAgent() {}
    public:
        virtual bool Initialize() = 0;
        virtual bool Update(AuctionHouseType houseType) = 0;
};

struct AuctionHouseBotStatusInfoPerType
{
    uint32 ItemsCount;
    uint32 QualityInfo[MAX_AUCTION_QUALITY];
};

typedef AuctionHouseBotStatusInfoPerType AuctionHouseBotStatusInfo[MAX_AUCTION_HOUSE_TYPE];

// This class handle both Selling and Buying method
// (holder of AuctionBotBuyer and AuctionBotSeller objects)
class AuctionHouseBot
{
    public:
        /** 
         * Initializes a new instance of the \ref AuctionHouseBot class.
         */
        AuctionHouseBot();
        /** 
         * Finalizes an instance of the \ref AuctionHouseBot class.
         */
        ~AuctionHouseBot();

        /** 
         * Updates this instance.
         */
        void Update();
        /** 
         * Initializes this instance.
         */
        void Initialize();

        // Followed method is mainly used by level3.cpp for ingame/console command
        /** 
         * Sets the items ratio.
         * 
         * @param al The alliane house ratio
         * @param ho The horde house ratio
         * @param ne The neutral house ratio
         */
        void SetItemsRatio(uint32 al, uint32 ho, uint32 ne);
        /** 
         * Sets the items ratio for a specific house, like \ref SetItemsRatio but
         * only for one house.
         * 
         * @param house The house
         * @param val The new ratio
         */
        void SetItemsRatioForHouse(AuctionHouseType house, uint32 val);
        /** 
         * Sets the items amount.
         * 
         * @param vals The vals.
         */
        void SetItemsAmount(uint32(&vals) [MAX_AUCTION_QUALITY]);
        /** 
         * Sets the items amount for quality.
         * 
         * @param quality The quality.
         * @param val The val.
         */
        void SetItemsAmountForQuality(AuctionQuality quality, uint32 val);
        /** 
         * Reloads all config.
         */
        bool ReloadAllConfig();
        /** 
         * Rebuilds the specified all.
         * 
         * @param all All.
         */
        void Rebuild(bool all);

        /** 
         * Prepares the status infos.
         * 
         * @param statusInfo The status info.
         */
        void PrepareStatusInfos(AuctionHouseBotStatusInfo& statusInfo);
    private:
        /** 
         * Initilizes the agents.
         */
        void InitilizeAgents();

        AuctionBotAgent* m_Buyer;
        AuctionBotAgent* m_Seller;

        uint32 m_OperationSelector;                         // 0..2*MAX_AUCTION_HOUSE_TYPE-1
};

#define sAuctionBot MaNGOS::Singleton<AuctionHouseBot>::Instance()

#endif
