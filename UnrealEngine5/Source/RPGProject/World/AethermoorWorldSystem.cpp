#include "World/AethermoorWorldSystem.h"
#include "World/WorldDefinition.h"

UAethermoorWorldSystem::UAethermoorWorldSystem()
{
	WorldDef = NewObject<UWorldDefinition>();
}

void UAethermoorWorldSystem::InitializeWorld()
{
	if (bWorldInitialized)
	{
		return;
	}

	if (!WorldDef)
	{
		WorldDef = NewObject<UWorldDefinition>();
	}

	bWorldInitialized = true;

	UE_LOG(LogTemp, Warning, TEXT("Aethermoor World System initialized successfully"));
	UE_LOG(LogTemp, Warning, TEXT("Continents: %d | Regions: %d | Zones: %d"), 
		GetWorldStatistics().TotalContinents,
		GetWorldStatistics().TotalRegions,
		GetWorldStatistics().TotalZones);
}

// ==================== CONTINENT ACCESS ====================

TArray<FContinent> UAethermoorWorldSystem::GetAllContinents() const
{
	if (WorldDef)
	{
		return WorldDef->GetAllContinents();
	}
	return TArray<FContinent>();
}

FContinent UAethermoorWorldSystem::GetContinentById(int32 ContinentId) const
{
	if (WorldDef)
	{
		return WorldDef->GetContinentById(ContinentId);
	}
	return FContinent();
}

FContinent UAethermoorWorldSystem::GetContinentByName(const FString& ContinentName) const
{
	if (WorldDef)
	{
		return WorldDef->GetContinentByName(ContinentName);
	}
	return FContinent();
}

TArray<FRegion> UAethermoorWorldSystem::GetRegionsByContinentId(int32 ContinentId) const
{
	if (WorldDef)
	{
		FContinent Continent = WorldDef->GetContinentById(ContinentId);
		return Continent.Regions;
	}
	return TArray<FRegion>();
}

TArray<FZoneDetail> UAethermoorWorldSystem::GetZonesByRegionId(int32 ContinentId, int32 RegionId) const
{
	if (WorldDef)
	{
		FContinent Continent = WorldDef->GetContinentById(ContinentId);
		for (const FRegion& Region : Continent.Regions)
		{
			if (Region.RegionId == RegionId)
			{
				return Region.Zones;
			}
		}
	}
	return TArray<FZoneDetail>();
}

// ==================== FACTION ACCESS ====================

int32 UAethermoorWorldSystem::GetTotalFactions() const
{
	return CachedTotalFactions;
}

TArray<FString> UAethermoorWorldSystem::GetAllFactionNames() const
{
	// Return array of all faction names in Aethermoor
	TArray<FString> Factions = {
		TEXT("The Divine Light"),
		TEXT("Shadow Council"),
		TEXT("Dwarven Clans"),
		TEXT("Elven Kingdoms"),
		TEXT("Arcane Mages"),
		TEXT("Demon Lords"),
		TEXT("The Lich King's Undead"),
		TEXT("Druidic Circle"),
		TEXT("Ranger's Brotherhood"),
		TEXT("Dragon Cult"),
		TEXT("Human Kingdoms"),
		TEXT("Merchant's Guild"),
		TEXT("Assassin's Brotherhood"),
		TEXT("Sky Guard"),
		TEXT("Nature Spirits")
	};
	return Factions;
}

FString UAethermoorWorldSystem::GetFactionDescription(const FString& FactionName) const
{
	if (FactionName.Equals(TEXT("The Divine Light"), ESearchCase::IgnoreCase))
	{
		return TEXT("Forces of good and righteousness, led by celestial powers");
	}
	else if (FactionName.Equals(TEXT("Shadow Council"), ESearchCase::IgnoreCase))
	{
		return TEXT("Secretive organization working from the shadows");
	}
	else if (FactionName.Equals(TEXT("Dwarven Clans"), ESearchCase::IgnoreCase))
	{
		return TEXT("Underground dwarf kingdoms focused on mining and crafting");
	}
	else if (FactionName.Equals(TEXT("Elven Kingdoms"), ESearchCase::IgnoreCase))
	{
		return TEXT("Ancient elven civilizations protecting the forests");
	}
	else if (FactionName.Equals(TEXT("Arcane Mages"), ESearchCase::IgnoreCase))
	{
		return TEXT("Powerful magic users studying arcane mysteries");
	}
	else if (FactionName.Equals(TEXT("Demon Lords"), ESearchCase::IgnoreCase))
	{
		return TEXT("Evil demonic forces from the abyss");
	}
	else if (FactionName.Equals(TEXT("The Lich King's Undead"), ESearchCase::IgnoreCase))
	{
		return TEXT("Undead army serving the immortal Lich King");
	}
	else if (FactionName.Equals(TEXT("Druidic Circle"), ESearchCase::IgnoreCase))
	{
		return TEXT("Nature-aligned druids protecting the balance");
	}
	else if (FactionName.Equals(TEXT("Ranger's Brotherhood"), ESearchCase::IgnoreCase))
	{
		return TEXT("Skilled hunters and scouts of the wilderness");
	}
	else if (FactionName.Equals(TEXT("Dragon Cult"), ESearchCase::IgnoreCase))
	{
		return TEXT("Worshippers of ancient dragons");
	}
	else if (FactionName.Equals(TEXT("Human Kingdoms"), ESearchCase::IgnoreCase))
	{
		return TEXT("Diverse human realms with varying governments");
	}
	else if (FactionName.Equals(TEXT("Merchant's Guild"), ESearchCase::IgnoreCase))
	{
		return TEXT("Traders and merchants controlling commerce");
	}
	else if (FactionName.Equals(TEXT("Assassin's Brotherhood"), ESearchCase::IgnoreCase))
	{
		return TEXT("Shadowy guild of skilled assassins");
	}
	else if (FactionName.Equals(TEXT("Sky Guard"), ESearchCase::IgnoreCase))
	{
		return TEXT("Celestial guardians of the sky realms");
	}
	
	return TEXT("Unknown faction");
}

TArray<FString> UAethermoorWorldSystem::GetEnemyFactions(const FString& FactionName) const
{
	TArray<FString> Enemies;

	if (FactionName.Equals(TEXT("The Divine Light"), ESearchCase::IgnoreCase))
	{
		Enemies = { TEXT("Demon Lords"), TEXT("The Lich King's Undead"), TEXT("Shadow Council") };
	}
	else if (FactionName.Equals(TEXT("Demon Lords"), ESearchCase::IgnoreCase))
	{
		Enemies = { TEXT("The Divine Light"), TEXT("Druidic Circle"), TEXT("Ranger's Brotherhood") };
	}
	else if (FactionName.Equals(TEXT("The Lich King's Undead"), ESearchCase::IgnoreCase))
	{
		Enemies = { TEXT("The Divine Light"), TEXT("Dwarven Clans"), TEXT("Human Kingdoms") };
	}

	return Enemies;
}

TArray<FString> UAethermoorWorldSystem::GetAlliedFactions(const FString& FactionName) const
{
	TArray<FString> Allies;

	if (FactionName.Equals(TEXT("The Divine Light"), ESearchCase::IgnoreCase))
	{
		Allies = { TEXT("Dwarven Clans"), TEXT("Elven Kingdoms"), TEXT("Human Kingdoms") };
	}
	else if (FactionName.Equals(TEXT("Dwarven Clans"), ESearchCase::IgnoreCase))
	{
		Allies = { TEXT("The Divine Light"), TEXT("Human Kingdoms"), TEXT("Ranger's Brotherhood") };
	}
	else if (FactionName.Equals(TEXT("Druidic Circle"), ESearchCase::IgnoreCase))
	{
		Allies = { TEXT("Ranger's Brotherhood"), TEXT("Elven Kingdoms"), TEXT("Nature Spirits") };
	}

	return Allies;
}

TArray<FString> UAethermoorWorldSystem::GetFactionsByAlignment(const FString& Alignment) const
{
	TArray<FString> Result;
	TArray<FString> AllFactions = GetAllFactionNames();

	if (Alignment.Equals(TEXT("Good"), ESearchCase::IgnoreCase))
	{
		Result = { TEXT("The Divine Light"), TEXT("Dwarven Clans"), TEXT("Elven Kingdoms"), 
				   TEXT("Druidic Circle"), TEXT("Ranger's Brotherhood"), TEXT("Sky Guard") };
	}
	else if (Alignment.Equals(TEXT("Evil"), ESearchCase::IgnoreCase))
	{
		Result = { TEXT("Demon Lords"), TEXT("The Lich King's Undead"), TEXT("Shadow Council"), 
				   TEXT("Dragon Cult"), TEXT("Assassin's Brotherhood") };
	}
	else if (Alignment.Equals(TEXT("Neutral"), ESearchCase::IgnoreCase))
	{
		Result = { TEXT("Human Kingdoms"), TEXT("Merchant's Guild"), TEXT("Arcane Mages") };
	}

	return Result;
}

// ==================== CHARACTER ACCESS ====================

int32 UAethermoorWorldSystem::GetTotalCharacters() const
{
	return CachedTotalCharacters;
}

TArray<FString> UAethermoorWorldSystem::GetAllCharacterNames() const
{
	TArray<FString> Characters = {
		TEXT("King Aldarin Stormborn"),
		TEXT("Queen Aelindor Moonwhisper"),
		TEXT("Grandmaster Elorah"),
		TEXT("Pharaoh Amenhotep"),
		TEXT("The Lich King Morthos"),
		TEXT("Archfiend Baltazar"),
		TEXT("Archmagus Valdris"),
		TEXT("Archangel Uriel"),
		TEXT("Storm Lord Tempestus"),
		TEXT("Ranger Captain Thorne"),
		TEXT("Archdruid Sylvanus"),
		TEXT("King Thorin Stonebeard"),
		TEXT("Jarl Skaelgrym"),
		TEXT("Sheikh Abubakar"),
		TEXT("High Merchant Lord Cassius"),
		TEXT("Shaman Kaida"),
		TEXT("Matriarch Lolth's Chosen"),
		TEXT("Inquisitor Cassandra"),
		TEXT("Shadowmaster Vex"),
		TEXT("Battlemaster Kragnar")
	};
	return Characters;
}

TArray<FString> UAethermoorWorldSystem::GetCharactersByFaction(const FString& FactionName) const
{
	TArray<FString> Characters;

	if (FactionName.Equals(TEXT("Human Kingdoms"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("King Aldarin Stormborn"), TEXT("High Merchant Lord Cassius"), TEXT("Ranger Captain Thorne") };
	}
	else if (FactionName.Equals(TEXT("Elven Kingdoms"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("Queen Aelindor Moonwhisper"), TEXT("Archdruid Sylvanus") };
	}
	else if (FactionName.Equals(TEXT("Dwarven Clans"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("King Thorin Stonebeard"), TEXT("Jarl Skaelgrym") };
	}
	else if (FactionName.Equals(TEXT("The Divine Light"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("Archangel Uriel"), TEXT("Grandmaster Elorah"), TEXT("Inquisitor Cassandra") };
	}
	else if (FactionName.Equals(TEXT("Arcane Mages"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("Archmagus Valdris"), TEXT("Shadowmaster Vex") };
	}

	return Characters;
}

TArray<FString> UAethermoorWorldSystem::GetCharactersByLocation(const FString& Location) const
{
	TArray<FString> Characters;

	if (Location.Contains(TEXT("Thornhaven")))
	{
		Characters.Add(TEXT("King Aldarin Stormborn"));
	}
	if (Location.Contains(TEXT("Ironforge")))
	{
		Characters.Add(TEXT("King Thorin Stonebeard"));
	}
	if (Location.Contains(TEXT("Silverleaf")))
	{
		Characters.Add(TEXT("Queen Aelindor Moonwhisper"));
	}

	return Characters;
}

TArray<FString> UAethermoorWorldSystem::GetCharactersByClass(const FString& ClassName) const
{
	TArray<FString> Characters;

	if (ClassName.Contains(TEXT("Warrior")))
	{
		Characters = { TEXT("King Aldarin Stormborn"), TEXT("King Thorin Stonebeard"), TEXT("Battlemaster Kragnar") };
	}
	else if (ClassName.Contains(TEXT("Mage")))
	{
		Characters = { TEXT("Archmagus Valdris"), TEXT("Shadowmaster Vex") };
	}
	else if (ClassName.Contains(TEXT("Ranger")))
	{
		Characters = { TEXT("Ranger Captain Thorne") };
	}

	return Characters;
}

TArray<FString> UAethermoorWorldSystem::GetCharactersByRace(const FString& RaceName) const
{
	TArray<FString> Characters;

	if (RaceName.Equals(TEXT("Human"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("King Aldarin Stormborn"), TEXT("Inquisitor Cassandra") };
	}
	else if (RaceName.Equals(TEXT("Elf"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("Queen Aelindor Moonwhisper"), TEXT("Archdruid Sylvanus") };
	}
	else if (RaceName.Equals(TEXT("Dwarf"), ESearchCase::IgnoreCase))
	{
		Characters = { TEXT("King Thorin Stonebeard"), TEXT("Jarl Skaelgrym") };
	}

	return Characters;
}

TArray<FString> UAethermoorWorldSystem::GetLeadersByRank() const
{
	TArray<FString> Leaders = {
		TEXT("King Aldarin Stormborn"),
		TEXT("Queen Aelindor Moonwhisper"),
		TEXT("King Thorin Stonebeard"),
		TEXT("Archangel Uriel"),
		TEXT("Pharaoh Amenhotep"),
		TEXT("The Lich King Morthos"),
		TEXT("Archmagus Valdris"),
		TEXT("Storm Lord Tempestus")
	};
	return Leaders;
}

int32 UAethermoorWorldSystem::GetAverageCharacterLevel() const
{
	return 35;
}

int32 UAethermoorWorldSystem::GetHighestLevelCharacter() const
{
	return 70;
}

// ==================== ARTIFACT ACCESS ====================

int32 UAethermoorWorldSystem::GetTotalArtifacts() const
{
	return CachedTotalArtifacts;
}

TArray<FString> UAethermoorWorldSystem::GetAllArtifactNames() const
{
	TArray<FString> Artifacts = {
		TEXT("Sulfuras, the Hand of Ragnaros"),
		TEXT("Excalibur"),
		TEXT("The Helm of Eternal Wisdom"),
		TEXT("Crown of the Dragon King"),
		TEXT("Mystical Amulet of Teleportation"),
		TEXT("Sword of Divine Justice"),
		TEXT("Shield of the Ancient Dwarves"),
		TEXT("Staff of Arcane Power"),
		TEXT("Ring of Invisibility"),
		TEXT("Boots of Speed"),
		TEXT("Cloak of Shadows"),
		TEXT("Gauntlets of Giant Strength"),
		TEXT("Necklace of Life Protection"),
		TEXT("Rune of Eternal Flame"),
		TEXT("Orb of Dark Prophecy"),
		TEXT("Scepter of the Pharaohs"),
		TEXT("Dragon Scale Armor"),
		TEXT("Holy Grail of Healing"),
		TEXT("Book of Ancient Spells"),
		TEXT("Codex of Forbidden Knowledge")
	};
	return Artifacts;
}

TArray<FString> UAethermoorWorldSystem::GetArtifactsByLocation(const FString& Location) const
{
	TArray<FString> Artifacts;

	if (Location.Contains(TEXT("Molten Core")))
	{
		Artifacts = { TEXT("Sulfuras, the Hand of Ragnaros") };
	}
	else if (Location.Contains(TEXT("Valley of Kings")))
	{
		Artifacts = { TEXT("Scepter of the Pharaohs") };
	}
	else if (Location.Contains(TEXT("Blackthorn Citadel")))
	{
		Artifacts = { TEXT("Orb of Dark Prophecy") };
	}

	return Artifacts;
}

TArray<FString> UAethermoorWorldSystem::GetArtifactsByLevel(int32 MinLevel) const
{
	TArray<FString> AllArtifacts = GetAllArtifactNames();
	TArray<FString> Result;

	// Simulate level requirements (artifacts 0-20 level range)
	int32 ArtifactLevel = 40;
	if (ArtifactLevel >= MinLevel)
	{
		Result = AllArtifacts;
	}

	return Result;
}

// ==================== LEGENDARY BEAST ACCESS ====================

int32 UAethermoorWorldSystem::GetTotalLegendaryBeasts() const
{
	return CachedTotalBeasts;
}

TArray<FString> UAethermoorWorldSystem::GetAllBeastNames() const
{
	TArray<FString> Beasts = {
		TEXT("Ragnaros the Firelord"),
		TEXT("Nefarian"),
		TEXT("Onyxia"),
		TEXT("Lich King Morthos"),
		TEXT("Demon Lord Kazzak"),
		TEXT("Ancient Dragon"),
		TEXT("The Tarrasque"),
		TEXT("Leviathan of the Deep"),
		TEXT("Chimera"),
		TEXT("Cerberus"),
		TEXT("Phoenix of Rebirth"),
		TEXT("Shadow Beast"),
		TEXT("Frost Wyrm"),
		TEXT("Storm Giant"),
		TEXT("Abyssal Horror")
	};
	return Beasts;
}

TArray<FString> UAethermoorWorldSystem::GetBeastsByLevel(int32 MinLevel) const
{
	TArray<FString> Beasts = GetAllBeastNames();
	TArray<FString> Result = Beasts;
	return Result;
}

TArray<FString> UAethermoorWorldSystem::GetDefeatedBeasts() const
{
	TArray<FString> Defeated = {
		TEXT("Nefarian"),
		TEXT("Onyxia")
	};
	return Defeated;
}

int32 UAethermoorWorldSystem::GetTotalDefeatedBeasts() const
{
	return GetDefeatedBeasts().Num();
}

// ==================== WORLD STATISTICS ====================

FWorldStatistics UAethermoorWorldSystem::GetWorldStatistics() const
{
	FWorldStatistics Stats;

	if (WorldDef)
	{
		TArray<FContinent> Continents = WorldDef->GetAllContinents();
		Stats.TotalContinents = Continents.Num();

		int32 RegionCount = 0;
		int32 ZoneCount = 0;
		int32 PopulationCount = 0;

		for (const FContinent& Continent : Continents)
		{
			RegionCount += Continent.Regions.Num();
			PopulationCount += Continent.Population;

			for (const FRegion& Region : Continent.Regions)
			{
				ZoneCount += Region.Zones.Num();
			}
		}

		Stats.TotalRegions = RegionCount;
		Stats.TotalZones = ZoneCount;
		Stats.TotalPopulation = PopulationCount;
	}

	Stats.TotalFactions = CachedTotalFactions;
	Stats.TotalCharacters = CachedTotalCharacters;
	Stats.TotalArtifacts = CachedTotalArtifacts;
	Stats.TotalLegendaryBeasts = CachedTotalBeasts;
	Stats.AverageCharacterLevel = GetAverageCharacterLevel();
	Stats.HighestLevelCharacter = GetHighestLevelCharacter();

	return Stats;
}

FString UAethermoorWorldSystem::GetWorldStatisticsString() const
{
	FWorldStatistics Stats = GetWorldStatistics();

	return FString::Printf(
		TEXT("========== AETHERMOOR WORLD STATISTICS ==========\n")
		TEXT("Continents: %d\n")
		TEXT("Regions: %d\n")
		TEXT("Zones: %d\n")
		TEXT("Total Population: %d\n")
		TEXT("Factions: %d\n")
		TEXT("Major Characters: %d\n")
		TEXT("Legendary Artifacts: %d\n")
		TEXT("Legendary Bosses: %d\n")
		TEXT("Average Character Level: %.1f\n")
		TEXT("Highest Level Character: %d\n")
		TEXT("================================================\n"),
		Stats.TotalContinents,
		Stats.TotalRegions,
		Stats.TotalZones,
		Stats.TotalPopulation,
		Stats.TotalFactions,
		Stats.TotalCharacters,
		Stats.TotalArtifacts,
		Stats.TotalLegendaryBeasts,
		Stats.AverageCharacterLevel,
		Stats.HighestLevelCharacter
	);
}

// ==================== WORLD INFORMATION ====================

FString UAethermoorWorldSystem::GetWorldName() const
{
	return TEXT("Aethermoor");
}

FString UAethermoorWorldSystem::GetWorldTheme() const
{
	return TEXT("Medieval Fantasy with Magic and Dungeons");
}

FString UAethermoorWorldSystem::GetWorldDescription() const
{
	FWorldStatistics Stats = GetWorldStatistics();

	return FString::Printf(
		TEXT("Welcome to Aethermoor\n\n")
		TEXT("A vast medieval fantasy world spanning %d major continents with %d regions and hundreds of distinct zones. ")
		TEXT("This Earth-sized world rivals World of Warcraft in scope and is filled with kingdoms, factions, powerful artifacts, ")
		TEXT("and legendary beasts awaiting brave adventurers.\n\n")
		TEXT("Total Population: %d\n")
		TEXT("Total Factions: %d\n")
		TEXT("Major Characters: %d\n")
		TEXT("Legendary Artifacts: %d\n")
		TEXT("Legendary Bosses: %d\n"),
		Stats.TotalContinents,
		Stats.TotalRegions,
		Stats.TotalPopulation,
		Stats.TotalFactions,
		Stats.TotalCharacters,
		Stats.TotalArtifacts,
		Stats.TotalLegendaryBeasts
	);
}

FString UAethermoorWorldSystem::GetWorldLore(ELoreType LoreType) const
{
	switch (LoreType)
	{
	case ELoreType::Creation:
		return GetCreationMythLore();
	case ELoreType::Prophecy:
		return GetAncientProphecyLore();
	case ELoreType::LichKing:
		return GetLichKingCurseLore();
	case ELoreType::DemonIncursion:
		return GetDemonIncursionLore();
	default:
		return TEXT("Unknown lore type");
	}
}

// ==================== TRAVEL & NAVIGATION ====================

bool UAethermoorWorldSystem::CanTravelBetweenZones(int32 FromZoneId, int32 ToZoneId) const
{
	if (WorldDef)
	{
		TArray<FContinent> Continents = WorldDef->GetAllContinents();

		for (const FContinent& Continent : Continents)
		{
			for (const FRegion& Region : Continent.Regions)
			{
				bool bFromFound = false;
				bool bToFound = false;

				for (const FZoneDetail& Zone : Region.Zones)
				{
					if (Zone.ZoneId == FromZoneId) bFromFound = true;
					if (Zone.ZoneId == ToZoneId) bToFound = true;
				}

				if (bFromFound && bToFound)
				{
					return true;
				}
			}
		}
	}

	return false;
}

TArray<FString> UAethermoorWorldSystem::GetRecommendedPath(int32 PlayerLevel) const
{
	TArray<FString> RecommendedZones;

	if (WorldDef)
	{
		TArray<FContinent> Continents = WorldDef->GetAllContinents();

		for (const FContinent& Continent : Continents)
		{
			for (const FRegion& Region : Continent.Regions)
			{
				for (const FZoneDetail& Zone : Region.Zones)
				{
					if (Zone.RecommendedLevel <= PlayerLevel && Zone.RecommendedLevel >= PlayerLevel - 5)
					{
						RecommendedZones.Add(FString::Printf(TEXT("%s (Level %d)"), *Zone.Name, Zone.RecommendedLevel));
					}
				}
			}
		}
	}

	// Return top 10 recommended zones
	if (RecommendedZones.Num() > 10)
	{
		TArray<FString> TopZones;
		for (int32 i = 0; i < 10; ++i)
		{
			TopZones.Add(RecommendedZones[i]);
		}
		return TopZones;
	}

	return RecommendedZones;
}

// ==================== WORLD DISPLAY ====================

void UAethermoorWorldSystem::DisplayWorldMap() const
{
	if (WorldDef)
	{
		WorldDef->DisplayWorldMap();
	}
}

void UAethermoorWorldSystem::DisplayContinentInfo(int32 ContinentId) const
{
	if (WorldDef)
	{
		WorldDef->DisplayContinentInfo(ContinentId);
	}
}

void UAethermoorWorldSystem::DisplayRegionInfo(int32 RegionId) const
{
	if (WorldDef)
	{
		WorldDef->DisplayRegionInfo(RegionId);
	}
}

void UAethermoorWorldSystem::DisplayWorldStatistics() const
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetWorldStatisticsString());
}

// ==================== LORE FUNCTIONS ====================

FString UAethermoorWorldSystem::GetCreationMythLore() const
{
	return TEXT(
		"In the beginning, the world was formless and void. The Great Creator wove reality from raw elemental chaos, "
		"shaping seven continents from the primordial waters. The divine light filled the sky, creating day and night, "
		"and blessed the lands with life - forests, mountains, deserts, and underground caverns teeming with wonders."
	);
}

FString UAethermoorWorldSystem::GetAncientProphecyLore() const
{
	return TEXT(
		"An ancient prophecy speaks of a great darkness that will rise to challenge all life in Aethermoor. "
		"A chosen one will emerge from unlikely circumstances to face this darkness, wielding artifacts of immense power. "
		"The fate of the world hangs in balance between light and shadow."
	);
}

FString UAethermoorWorldSystem::GetLichKingCurseLore() const
{
	return TEXT(
		"Centuries ago, a great wizard sought immortality through forbidden rituals. Binding his soul to undeath, "
		"he became the Lich King Morthos, cursing the lands around him with necrotic energy. His power grows each passing age, "
		"and his undead legions march across the Shadowlands, threatening all mortal kingdoms."
	);
}

FString UAethermoorWorldSystem::GetDemonIncursionLore() const
{
	return TEXT(
		"From the abyss below, demonic forces breach the barriers between worlds. Led by powerful archfiends, "
		"the demons seek to corrupt and dominate Aethermoor. Their corruption spreads across the Demonfire Wastes, "
		"threatening to engulf all of civilization in hellfire and chaos."
	);
}
