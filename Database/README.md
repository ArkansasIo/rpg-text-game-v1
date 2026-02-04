# RPG/MMORPG Database Schema Documentation

## Overview
This is a comprehensive database schema for a full-featured RPG/MMORPG game system. The schema supports both single-player RPG and massively multiplayer online functionality.

## Database Structure

### ?? Total Tables: 80+

## Core Systems

### 1. **Accounts & Characters** (2 tables)
- `Accounts` - Player account management
- `Characters` - Character data with stats, location, progression

### 2. **Items & Equipment** (8 tables)
- `Items` - All game items (weapons, armor, consumables, etc.)
- `ItemStats` - Item stat bonuses
- `Weapons` - Weapon-specific data (damage, speed, DPS)
- `Armor` - Armor-specific data (armor value, type)
- `CharacterInventory` - Player inventory (grid-based)
- `CharacterEquipment` - Equipped items (19 slots)
- `CharacterBank` - Bank storage with tabs

### 3. **World & Zones** (3 tables)
- `Zones` - All game zones (72 zones)
- `ZoneConnections` - How zones connect
- `CharacterZoneDiscovery` - Player exploration tracking

### 4. **NPCs** (1 table)
- `NPCs` - Non-player characters (vendors, quest givers, trainers)

### 5. **Enemies & Combat** (3 tables)
- `Enemies` - Enemy templates (26+ types)
- `EnemyLootTable` - Drop tables
- `EnemySpawns` - Spawn locations

### 6. **Dungeons & Raids** (4 tables)
- `Dungeons` - Dungeon/raid instances
- `DungeonDifficulties` - Normal, Heroic, Mythic, Mythic+
- `DungeonBosses` - Boss encounters
- `CharacterDungeonProgress` - Player completion tracking

### 7. **Quests** (4 tables)
- `Quests` - Quest data
- `QuestObjectives` - Quest goals
- `CharacterQuests` - Player quest progress
- `QuestRewardItems` - Quest rewards

### 8. **Guilds** (4 tables)
- `Guilds` - Guild organizations
- `GuildRanks` - Rank permissions
- `GuildBank` - Guild storage
- `GuildPerks` - Guild bonuses

### 9. **Crafting & Professions** (5 tables)
- `Professions` - 14 professions
- `CharacterProfessions` - Player profession skills
- `Recipes` - Crafting recipes
- `RecipeMaterials` - Recipe ingredients
- `CharacterRecipes` - Known recipes

### 10. **Economy & Trading** (3 tables)
- `AuctionListings` - Auction house
- `AuctionBidHistory` - Bid tracking
- `Mail` - In-game mail system

### 11. **Talents & Skills** (3 tables)
- `TalentTrees` - Skill trees
- `TalentNodes` - Individual talents (51 points)
- `CharacterTalents` - Player talent allocation

### 12. **Achievements** (2 tables)
- `Achievements` - Achievement definitions
- `CharacterAchievements` - Player achievement progress

### 13. **Reputation & Factions** (2 tables)
- `Factions` - Game factions
- `CharacterReputation` - Standing with factions (7 levels)

### 14. **Mounts & Pets** (4 tables)
- `Mounts` - Mount collection
- `CharacterMounts` - Owned mounts
- `Pets` - Pet collection
- `CharacterPets` - Owned pets

### 15. **Player Housing** (2 tables)
- `Houses` - Player homes
- `HouseDecorations` - Furniture placement

### 16. **PvP Systems** (3 tables)
- `PvPStats` - Honor, rating, kills/deaths
- `PvPMatches` - Match history
- `PvPMatchParticipants` - Player participation

### 17. **Status Effects** (2 tables)
- `StatusEffects` - Buff/debuff definitions
- `CharacterStatusEffects` - Active effects on players

### 18. **World Events** (2 tables)
- `WorldEvents` - Scheduled/random events
- `CharacterEventParticipation` - Event contributions

### 19. **Resource Nodes** (2 tables)
- `ResourceNodes` - Gathering locations
- `ResourceNodeDrops` - Harvestable items

### 20. **Companions** (4 tables)
- `Companions` - NPC companions
- `CompanionAbilities` - Companion skills
- `CharacterCompanions` - Recruited companions
- `CompanionEquipment` - Companion gear

### 21. **Dialogue System** (3 tables)
- `DialogueTrees` - Conversation structures
- `DialogueNodes` - Individual dialogue
- `DialogueChoices` - Player choices

### 22. **Transmog/Appearance** (3 tables)
- `TransmogAppearances` - Cosmetic appearances
- `CharacterTransmog` - Applied transmogs
- `CharacterUnlockedAppearances` - Unlocked cosmetics

### 23. **Social Systems** (3 tables)
- `FriendsList` - Friend management
- `IgnoreList` - Blocked players
- `ChatMessages` - Chat history

### 24. **Analytics** (3 tables)
- `PlayerSessions` - Login tracking
- `PlayerActions` - Telemetry
- `EconomyTransactions` - Economic data

### 25. **Moderation** (2 tables)
- `PlayerReports` - Player reports
- `Bans` - Ban management

### 26. **Leaderboards** (2 tables)
- `Leaderboards` - Ranking categories
- `LeaderboardEntries` - Player rankings

---

## Key Features

### ?? **Character Progression**
- 12 Races
- 12 Classes
- 40+ Specializations
- 51-point talent trees
- Level 1-70+
- Experience & skill systems

### ?? **Combat Systems**
- 26+ enemy types
- 6 enemy ranks (Normal ? World Boss)
- Status effects (buffs, debuffs, DOT, HOT, CC)
- Threat/aggro system
- Combo system

### ??? **World**
- 72 unique zones
- 20 biome types
- 15 underground zone types
- Dynamic weather
- Day/night cycle
- World events

### ?? **Items & Loot**
- 8 item quality tiers
- 19 equipment slots
- Socket & gem system
- Enchantments
- Transmog system
- Grid-based inventory

### ?? **Dungeons & Raids**
- 8+ dungeons
- 4 difficulty levels
- 40-player raids
- Mythic+ system
- Boss mechanics

### ?? **Economy**
- Auction house
- Mail system with attachments
- Player trading
- Multi-currency support
- 14 professions
- Crafting system

### ?? **Progression Systems**
- Achievements
- Reputation (7 levels)
- PvP ranking
- Guild progression
- Mounts & pets collection

### ?? **Housing**
- 6 house types
- Decoration system
- Storage
- Guild halls

### ?? **Social**
- Guild system
- Party (5 players)
- Raid (40 players)
- Friends list
- Mail system
- Chat channels

---

## Installation

### Option 1: SQL Server
```sql
-- Run in order:
1. Schema_Part1_Core.sql
2. Schema_Part2_Social.sql
3. Schema_Part3_Advanced.sql
4. SeedData.sql (optional - sample data)
```

### Option 2: Entity Framework
```bash
# Update connection string in appsettings.json
# Run migrations
dotnet ef database update
```

---

## Data Relationships

### Character ? Equipment
- One-to-many: Characters have multiple inventory items
- One-to-many: Characters have equipment in 19 slots
- One-to-many: Characters have bank storage

### Character ? Quests
- Many-to-many: Characters can have multiple active quests
- Tracks progress per objective

### Character ? Guild
- Many-to-one: Characters belong to one guild
- Guilds have ranks with permissions

### Items ? Stats
- One-to-many: Items have multiple stat bonuses
- Supports sockets, gems, enchantments

### Zones ? Enemies
- One-to-many: Zones have enemy spawns
- Dynamic respawn system

### Dungeons ? Bosses
- One-to-many: Dungeons have multiple bosses
- Supports multiple difficulties

---

## Indexes & Performance

The schema includes strategic indexes on:
- Primary foreign key relationships
- Common query patterns (level, type, status)
- Composite indexes for multi-column searches
- Unique constraints for data integrity

---

## Scalability Considerations

### Horizontal Scaling
- Character data can be sharded by AccountId
- Auction house can be regionalized
- Analytics tables can be partitioned by date

### Vertical Optimization
- Computed columns for performance
- JSON columns for flexible data
- Indexed views for complex queries

---

## Security Features

- Password hashing with salt
- Account ban system
- Player reporting
- Moderation tools
- IP tracking for analytics

---

## Analytics & Telemetry

### Player Behavior
- Session tracking
- Action logging
- Economy monitoring
- Matchmaking data

### Game Balance
- Drop rate tracking
- Economy inflation monitoring
- PvP balance metrics
- Dungeon completion rates

---

## Extension Points

The schema is designed to be extensible:

1. **Custom Events** - JSON fields in WorldEvents
2. **Dynamic Stats** - JSON in Items for new stat types
3. **New Content** - Easily add zones, enemies, items
4. **Seasonal Content** - Event and leaderboard systems
5. **Modding Support** - Flexible data structures

---

## Sample Queries

### Get Character Full Equipment
```sql
SELECT c.CharacterName, ce.SlotType, i.ItemName, i.Quality
FROM Characters c
INNER JOIN CharacterEquipment ce ON c.CharacterId = ce.CharacterId
INNER JOIN Items i ON ce.ItemId = i.ItemId
WHERE c.CharacterId = @CharacterId;
```

### Top 10 Richest Players
```sql
SELECT TOP 10 CharacterName, Gold, Level
FROM Characters
WHERE IsDeleted = 0
ORDER BY Gold DESC;
```

### Guild Member Count
```sql
SELECT g.GuildName, COUNT(c.CharacterId) as MemberCount
FROM Guilds g
LEFT JOIN Characters c ON g.GuildId = c.GuildId
GROUP BY g.GuildId, g.GuildName
ORDER BY MemberCount DESC;
```

### Most Valuable Auction Items
```sql
SELECT i.ItemName, al.BuyoutPrice, al.CurrentBid
FROM AuctionListings al
INNER JOIN Items i ON al.ItemId = i.ItemId
WHERE al.Status = 0 -- Active
ORDER BY al.BuyoutPrice DESC;
```

---

## Database Size Estimates

For 10,000 active players:

| Table | Estimated Rows | Size |
|-------|---------------|------|
| Characters | 50,000 | ~50 MB |
| CharacterInventory | 500,000 | ~200 MB |
| Items | 5,000 | ~5 MB |
| Enemies | 100 | ~1 MB |
| Quests | 1,000 | ~10 MB |
| ChatMessages | 10,000,000 | ~5 GB |
| PlayerActions | 100,000,000 | ~50 GB |

**Total Estimated: ~60-100 GB** for established server

---

## Backup Strategy

1. **Full Backup**: Daily
2. **Incremental**: Every 4 hours
3. **Transaction Log**: Every 15 minutes
4. **Archive**: Keep 30 days

---

## Maintenance Tasks

### Daily
- Rebuild fragmented indexes
- Update statistics
- Clean expired auctions
- Process old mail

### Weekly
- Archive old chat logs
- Analyze slow queries
- Review ban reports

### Monthly
- Partition old analytics data
- Archive inactive accounts
- Database integrity check

---

## Version History

- **v1.0** - Initial release
- All core RPG/MMORPG systems
- 80+ tables
- Full relationships
- Seed data included

---

## License

This database schema is provided as-is for educational and development purposes.

---

## Support

For issues or questions about the schema:
1. Check table relationships
2. Review index usage
3. Consult documentation
4. Test with seed data

---

**Built for: Enterprise-level RPG/MMORPG Development**
**Compatible with: SQL Server 2016+, Azure SQL Database**
