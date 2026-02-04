#include "World/WorldDefinition.h"

// ==================== STATIC CONSTANTS ====================
const FString UWorldDefinition::WORLD_NAME = TEXT("Aethermoor");
const FString UWorldDefinition::WORLD_THEME = TEXT("Medieval Fantasy with Magic and Dungeons");

UWorldDefinition::UWorldDefinition()
{
	InitializeWorldDatabase();
}

void UWorldDefinition::InitializeWorldDatabase()
{
	if (bWorldInitialized)
	{
		return;
	}

	// Build all 7 continents
	Continents.Add(BuildValorathContinent());
	Continents.Add(BuildLumeriaContinent());
	Continents.Add(BuildMortalisContinent());
	Continents.Add(BuildKharanosContinent());
	Continents.Add(BuildAethralContinent());
	Continents.Add(BuildDeepmoorContinent());
	Continents.Add(BuildCelestiaContinent());

	bWorldInitialized = true;
}

FString UWorldDefinition::GetWorldName()
{
	return WORLD_NAME;
}

FString UWorldDefinition::GetWorldTheme()
{
	return WORLD_THEME;
}

TArray<FContinent> UWorldDefinition::GetAllContinents()
{
	if (!bWorldInitialized)
	{
		const_cast<UWorldDefinition*>(this)->InitializeWorldDatabase();
	}
	return Continents;
}

FContinent UWorldDefinition::GetContinentById(int32 ContinentId)
{
	if (!bWorldInitialized)
	{
		const_cast<UWorldDefinition*>(this)->InitializeWorldDatabase();
	}

	for (const FContinent& Continent : Continents)
	{
		if (Continent.ContinentId == ContinentId)
		{
			return Continent;
		}
	}

	return FContinent();
}

FContinent UWorldDefinition::GetContinentByName(const FString& ContinentName)
{
	if (!bWorldInitialized)
	{
		const_cast<UWorldDefinition*>(this)->InitializeWorldDatabase();
	}

	for (const FContinent& Continent : Continents)
	{
		if (Continent.Name.Equals(ContinentName, ESearchCase::IgnoreCase))
		{
			return Continent;
		}
	}

	return FContinent();
}

FRegion UWorldDefinition::GetRegionById(int32 RegionId)
{
	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			if (Region.RegionId == RegionId)
			{
				return Region;
			}
		}
	}

	return FRegion();
}

FRegion UWorldDefinition::GetRegionByName(const FString& RegionName)
{
	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			if (Region.Name.Equals(RegionName, ESearchCase::IgnoreCase))
			{
				return Region;
			}
		}
	}

	return FRegion();
}

TArray<FRegion> UWorldDefinition::GetRegionsByBiome(EBiomeType BiomeType)
{
	TArray<FRegion> Result;

	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			if (Region.BiomeType == BiomeType)
			{
				Result.Add(Region);
			}
		}
	}

	return Result;
}

TArray<FRegion> UWorldDefinition::GetRegionsByLevelRange(int32 MinLevel, int32 MaxLevel)
{
	TArray<FRegion> Result;

	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			if (Region.RecommendedLevel >= MinLevel && Region.RecommendedLevel <= MaxLevel)
			{
				Result.Add(Region);
			}
		}
	}

	return Result;
}

FZoneDetail UWorldDefinition::GetZoneById(int32 ZoneId)
{
	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			for (const FZoneDetail& Zone : Region.Zones)
			{
				if (Zone.ZoneId == ZoneId)
				{
					return Zone;
				}
			}
		}
	}

	return FZoneDetail();
}

FZoneDetail UWorldDefinition::GetZoneByName(const FString& ZoneName)
{
	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			for (const FZoneDetail& Zone : Region.Zones)
			{
				if (Zone.Name.Equals(ZoneName, ESearchCase::IgnoreCase))
				{
					return Zone;
				}
			}
		}
	}

	return FZoneDetail();
}

TArray<FZoneDetail> UWorldDefinition::GetZonesByType(EZoneType ZoneType)
{
	TArray<FZoneDetail> Result;

	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			for (const FZoneDetail& Zone : Region.Zones)
			{
				if (Zone.Type == ZoneType)
				{
					Result.Add(Zone);
				}
			}
		}
	}

	return Result;
}

TArray<FZoneDetail> UWorldDefinition::GetZonesByLevel(int32 MinLevel, int32 MaxLevel)
{
	TArray<FZoneDetail> Result;

	for (const FContinent& Continent : GetAllContinents())
	{
		for (const FRegion& Region : Continent.Regions)
		{
			for (const FZoneDetail& Zone : Region.Zones)
			{
				if (Zone.RecommendedLevel >= MinLevel && Zone.RecommendedLevel <= MaxLevel)
				{
					Result.Add(Zone);
				}
			}
		}
	}

	return Result;
}

int32 UWorldDefinition::GetTotalContinents() const
{
	return Continents.Num();
}

int32 UWorldDefinition::GetTotalRegions() const
{
	int32 Total = 0;
	for (const FContinent& Continent : Continents)
	{
		Total += Continent.Regions.Num();
	}
	return Total;
}

int32 UWorldDefinition::GetTotalZones() const
{
	int32 Total = 0;
	for (const FContinent& Continent : Continents)
	{
		for (const FRegion& Region : Continent.Regions)
		{
			Total += Region.Zones.Num();
		}
	}
	return Total;
}

int32 UWorldDefinition::GetTotalPopulation() const
{
	int32 Total = 0;
	for (const FContinent& Continent : Continents)
	{
		Total += Continent.Population;
	}
	return Total;
}

int32 UWorldDefinition::GetTotalArea() const
{
	int32 Total = 0;
	for (const FContinent& Continent : Continents)
	{
		Total += Continent.AreaSquareMiles;
	}
	return Total;
}

FString UWorldDefinition::GetWorldDescription() const
{
	FString Description = FString::Printf(
		TEXT("=== %s ===\n"),
		*WORLD_NAME
	);

	Description += FString::Printf(
		TEXT("Theme: %s\n\n"),
		*WORLD_THEME
	);

	Description += FString::Printf(
		TEXT("World Statistics:\n")
		TEXT("Total Area: %d square miles\n")
		TEXT("Total Population: %d\n")
		TEXT("Total Continents: %d\n")
		TEXT("Total Regions: %d\n")
		TEXT("Total Zones: %d\n"),
		GetTotalArea(),
		GetTotalPopulation(),
		GetTotalContinents(),
		GetTotalRegions(),
		GetTotalZones()
	);

	return Description;
}

void UWorldDefinition::DisplayWorldMap() const
{
	UE_LOG(LogTemp, Warning, TEXT("=== %s ==="), *WORLD_NAME);
	UE_LOG(LogTemp, Warning, TEXT("Theme: %s"), *WORLD_THEME);
	UE_LOG(LogTemp, Warning, TEXT("Total Continents: %d"), GetTotalContinents());

	for (const FContinent& Continent : Continents)
	{
		UE_LOG(LogTemp, Warning, TEXT("\n[CONTINENT %d] %s"), Continent.ContinentId, *Continent.Name);
		UE_LOG(LogTemp, Warning, TEXT("  Description: %s"), *Continent.Description);
		UE_LOG(LogTemp, Warning, TEXT("  Area: %d sq mi | Population: %d"), Continent.AreaSquareMiles, Continent.Population);
		UE_LOG(LogTemp, Warning, TEXT("  Regions: %d"), Continent.Regions.Num());
	}
}

void UWorldDefinition::DisplayContinentInfo(int32 ContinentId) const
{
	FContinent Continent = GetContinentById(ContinentId);

	if (Continent.ContinentId == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Continent not found"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("=== %s ==="), *Continent.Name);
	UE_LOG(LogTemp, Warning, TEXT("Description: %s"), *Continent.Description);
	UE_LOG(LogTemp, Warning, TEXT("Theme: %s"), *Continent.Theme);
	UE_LOG(LogTemp, Warning, TEXT("Area: %d square miles"), Continent.AreaSquareMiles);
	UE_LOG(LogTemp, Warning, TEXT("Population: %d"), Continent.Population);
	UE_LOG(LogTemp, Warning, TEXT("Regions: %d\n"), Continent.Regions.Num());

	for (const FRegion& Region : Continent.Regions)
	{
		UE_LOG(LogTemp, Warning, TEXT("  [%d] %s (Lv %d)"), Region.RegionId, *Region.Name, Region.RecommendedLevel);
		UE_LOG(LogTemp, Warning, TEXT("      %s | Ruler: %s"), *Region.RegionType, *Region.Ruler);
	}
}

void UWorldDefinition::DisplayRegionInfo(int32 RegionId) const
{
	FRegion Region = GetRegionById(RegionId);

	if (Region.RegionId == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Region not found"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("=== %s ==="), *Region.Name);
	UE_LOG(LogTemp, Warning, TEXT("Description: %s"), *Region.Description);
	UE_LOG(LogTemp, Warning, TEXT("Level: %d | Biome: %s"), Region.RecommendedLevel, *BiomeTypeToString(Region.BiomeType));
	UE_LOG(LogTemp, Warning, TEXT("Government: %s | Ruler: %s"), *GovernmentTypeToString(Region.GovernmentType), *Region.Ruler);
	UE_LOG(LogTemp, Warning, TEXT("Capital: %s | Population: %d"), *Region.CapitalCity, Region.Population);
	UE_LOG(LogTemp, Warning, TEXT("Zones: %d\n"), Region.Zones.Num());

	for (const FZoneDetail& Zone : Region.Zones)
	{
		UE_LOG(LogTemp, Warning, TEXT("  [%d] %s (Lv %d)"), Zone.ZoneId, *Zone.Name, Zone.RecommendedLevel);
		UE_LOG(LogTemp, Warning, TEXT("      Type: %s | %s"), *ZoneTypeToString(Zone.Type), *Zone.Description);
	}
}

// ==================== CONTINENT BUILDERS ====================

FContinent UWorldDefinition::BuildValorathContinent()
{
	FContinent Continent;
	Continent.ContinentId = 1;
	Continent.Name = TEXT("Valorath");
	Continent.Description = TEXT("The frozen northern continent of eternal winter and ancient dwarven kingdoms");
	Continent.AreaSquareMiles = 850000;
	Continent.Population = 2500000;
	Continent.Theme = TEXT("Frozen Peaks, Snow Valleys, Dwarven Mines");

	// Region 1: Ironhammer Kingdom
	FRegion IronhammerRegion;
	IronhammerRegion.RegionId = 1;
	IronhammerRegion.Name = TEXT("Ironhammer Kingdom");
	IronhammerRegion.Description = TEXT("The greatest dwarven kingdom with underground cities");
	IronhammerRegion.RecommendedLevel = 1;
	IronhammerRegion.RegionType = TEXT("Underground City / Mountains");
	IronhammerRegion.BiomeType = EBiomeType::Mountain;
	IronhammerRegion.Population = 500000;
	IronhammerRegion.GovernmentType = EGovernmentType::Monarchy;
	IronhammerRegion.Ruler = TEXT("King Thorin Stonebeard");
	IronhammerRegion.CapitalCity = TEXT("Ironforge Citadel");
	IronhammerRegion.Zones = {
		FZoneDetail{ 101, TEXT("Stonekeep Entrance"), 1, EZoneType::Mountain, TEXT("Majestic entrance to the dwarven kingdom") },
		FZoneDetail{ 102, TEXT("Deepdelve Mines"), 5, EZoneType::Underground, TEXT("Ancient mining operations") },
		FZoneDetail{ 103, TEXT("Forgemaster's Cavern"), 8, EZoneType::Dungeon, TEXT("Where legendary weapons are crafted") },
		FZoneDetail{ 104, TEXT("Molten Throne Room"), 12, EZoneType::Castle, TEXT("Seat of dwarven power") }
	};
	Continent.Regions.Add(IronhammerRegion);

	// Region 2: Frostheim Wastes
	FRegion Frostheim;
	Frostheim.RegionId = 2;
	Frostheim.Name = TEXT("Frostheim Wastes");
	Frostheim.Description = TEXT("Endless icy plains home to frost giants and ice dragons");
	Frostheim.RecommendedLevel = 15;
	Frostheim.RegionType = TEXT("Tundra / Glacier");
	Frostheim.BiomeType = EBiomeType::Tundra;
	Frostheim.Population = 100000;
	Frostheim.GovernmentType = EGovernmentType::Tribal;
	Frostheim.Ruler = TEXT("Jarl Skaelgrym");
	Frostheim.CapitalCity = TEXT("Icehammer Hold");
	Frostheim.Zones = {
		FZoneDetail{ 105, TEXT("Eternal Snowfield"), 15, EZoneType::Plains, TEXT("Endless white landscape") },
		FZoneDetail{ 106, TEXT("Glacial Abyss"), 20, EZoneType::Cave, TEXT("Frozen caverns with ancient secrets") },
		FZoneDetail{ 107, TEXT("Frostbite Peak"), 25, EZoneType::Mountain, TEXT("Home of the Ice Dragons") }
	};
	Continent.Regions.Add(Frostheim);

	// Region 3: Drakespine Mountains
	FRegion Drakespine;
	Drakespine.RegionId = 3;
	Drakespine.Name = TEXT("Drakespine Mountains");
	Drakespine.Description = TEXT("Ancient dragon nesting grounds and mountain monasteries");
	Drakespine.RecommendedLevel = 20;
	Drakespine.RegionType = TEXT("Mountain Range");
	Drakespine.BiomeType = EBiomeType::Mountain;
	Drakespine.Population = 250000;
	Drakespine.GovernmentType = EGovernmentType::Theocracy;
	Drakespine.Ruler = TEXT("Grandmaster Elorah");
	Drakespine.CapitalCity = TEXT("Skyward Monastery");
	Drakespine.Zones = {
		FZoneDetail{ 108, TEXT("Eagle's Nest Pass"), 20, EZoneType::Mountain, TEXT("Treacherous mountain passage") },
		FZoneDetail{ 109, TEXT("Dragonborn Sanctum"), 25, EZoneType::Temple, TEXT("Sacred draconic temple") },
		FZoneDetail{ 110, TEXT("Chromatic Spire"), 30, EZoneType::Dungeon, TEXT("Tower of corrupted dragons") }
	};
	Continent.Regions.Add(Drakespine);

	return Continent;
}

FContinent UWorldDefinition::BuildLumeriaContinent()
{
	FContinent Continent;
	Continent.ContinentId = 2;
	Continent.Name = TEXT("Lumeria");
	Continent.Description = TEXT("The mystical eastern continent of ancient elven forests and arcane magic");
	Continent.AreaSquareMiles = 920000;
	Continent.Population = 3000000;
	Continent.Theme = TEXT("Magical Forests, Elven Cities, Arcane Ruins");

	// Region 1: Emerald Vale
	FRegion EmeraldVale;
	EmeraldVale.RegionId = 4;
	EmeraldVale.Name = TEXT("Emerald Vale");
	EmeraldVale.Description = TEXT("The heart of elven civilization with ancient treeship cities");
	EmeraldVale.RecommendedLevel = 8;
	EmeraldVale.RegionType = TEXT("Old Growth Forest");
	EmeraldVale.BiomeType = EBiomeType::TemperateForest;
	EmeraldVale.Population = 800000;
	EmeraldVale.GovernmentType = EGovernmentType::Monarchy;
	EmeraldVale.Ruler = TEXT("Queen Aelindor Moonwhisper");
	EmeraldVale.CapitalCity = TEXT("Silverleaf City");
	EmeraldVale.Zones = {
		FZoneDetail{ 111, TEXT("Whispering Grove"), 8, EZoneType::Forest, TEXT("Ancient elven sanctuary") },
		FZoneDetail{ 112, TEXT("Moonwell Glade"), 12, EZoneType::Forest, TEXT("Sacred magical springs") },
		FZoneDetail{ 113, TEXT("Starfire Tower"), 16, EZoneType::Temple, TEXT("Arcane research center") }
	};
	Continent.Regions.Add(EmeraldVale);

	// Region 2: Shadowpine Jungle
	FRegion ShadowpineJungle;
	ShadowpineJungle.RegionId = 5;
	ShadowpineJungle.Name = TEXT("Shadowpine Jungle");
	ShadowpineJungle.Description = TEXT("Dense rainforest with hidden druids and wild magic");
	ShadowpineJungle.RecommendedLevel = 12;
	ShadowpineJungle.RegionType = TEXT("Tropical Rainforest");
	ShadowpineJungle.BiomeType = EBiomeType::TropicalRainforest;
	ShadowpineJungle.Population = 450000;
	ShadowpineJungle.GovernmentType = EGovernmentType::DruidicCouncil;
	ShadowpineJungle.Ruler = TEXT("Archdruid Sylvanus");
	ShadowpineJungle.CapitalCity = TEXT("Deepwood Grotto");
	ShadowpineJungle.Zones = {
		FZoneDetail{ 114, TEXT("Canopy Pathways"), 12, EZoneType::Forest, TEXT("Bridges through ancient trees") },
		FZoneDetail{ 115, TEXT("Primal Swamp"), 18, EZoneType::Unknown, TEXT("Where nature's power runs wild") },
		FZoneDetail{ 116, TEXT("Bastion of the Wild"), 22, EZoneType::Dungeon, TEXT("Corrupted druid stronghold") }
	};
	Continent.Regions.Add(ShadowpineJungle);

	// Region 3: Arcane Isles
	FRegion ArcaneIsles;
	ArcaneIsles.RegionId = 6;
	ArcaneIsles.Name = TEXT("Arcane Isles");
	ArcaneIsles.Description = TEXT("Magical archipelago of wizard towers and research facilities");
	ArcaneIsles.RecommendedLevel = 18;
	ArcaneIsles.RegionType = TEXT("Island Chain");
	ArcaneIsles.BiomeType = EBiomeType::FloatingIslands;
	ArcaneIsles.Population = 350000;
	ArcaneIsles.GovernmentType = EGovernmentType::MageCouncil;
	ArcaneIsles.Ruler = TEXT("Archmagus Valdris");
	ArcaneIsles.CapitalCity = TEXT("Spellforge Academy");
	ArcaneIsles.Zones = {
		FZoneDetail{ 117, TEXT("Mage Academy Isle"), 18, EZoneType::Town, TEXT("Premier magical university") },
		FZoneDetail{ 118, TEXT("Floating Sanctum"), 22, EZoneType::SkyCity, TEXT("Suspended magical libraries") },
		FZoneDetail{ 119, TEXT("Ley Node Nexus"), 28, EZoneType::Dungeon, TEXT("Heart of magical power") }
	};
	Continent.Regions.Add(ArcaneIsles);

	return Continent;
}

FContinent UWorldDefinition::BuildMortalisContinent()
{
	FContinent Continent;
	Continent.ContinentId = 3;
	Continent.Name = TEXT("Mortalis");
	Continent.Description = TEXT("The western continent of human kingdoms, commerce, and political intrigue");
	Continent.AreaSquareMiles = 880000;
	Continent.Population = 4500000;
	Continent.Theme = TEXT("Human Kingdoms, Trading Routes, Castles");

	// Region 1: Valorian Kingdom
	FRegion Valorian;
	Valorian.RegionId = 7;
	Valorian.Name = TEXT("Valorian Kingdom");
	Valorian.Description = TEXT("The greatest human kingdom with vast territories");
	Valorian.RecommendedLevel = 1;
	Valorian.RegionType = TEXT("Mixed Terrain");
	Valorian.BiomeType = EBiomeType::GrasslandPlains;
	Valorian.Population = 1500000;
	Valorian.GovernmentType = EGovernmentType::Monarchy;
	Valorian.Ruler = TEXT("King Aldarin Stormborn");
	Valorian.CapitalCity = TEXT("Thornhaven");
	Valorian.Zones = {
		FZoneDetail{ 120, TEXT("Thornhaven Plaza"), 1, EZoneType::City, TEXT("Capital city of Valorian") },
		FZoneDetail{ 121, TEXT("Royal Castle Valdemere"), 5, EZoneType::Castle, TEXT("Home of the king") },
		FZoneDetail{ 122, TEXT("Farmland Vales"), 3, EZoneType::Plains, TEXT("Fertile agricultural lands") },
		FZoneDetail{ 123, TEXT("Dark Forest of Mal'thir"), 10, EZoneType::Forest, TEXT("Dangerous woods at kingdom's edge") }
	};
	Continent.Regions.Add(Valorian);

	// Region 2: Merchant's Confluence
	FRegion MerchantConfluence;
	MerchantConfluence.RegionId = 8;
	MerchantConfluence.Name = TEXT("Merchant's Confluence");
	MerchantConfluence.Description = TEXT("Free cities united by commerce and trade");
	MerchantConfluence.RecommendedLevel = 8;
	MerchantConfluence.RegionType = TEXT("Merchant Cities");
	MerchantConfluence.BiomeType = EBiomeType::GrasslandPlains;
	MerchantConfluence.Population = 1200000;
	MerchantConfluence.GovernmentType = EGovernmentType::Republic;
	MerchantConfluence.Ruler = TEXT("High Merchant Lord Cassius");
	MerchantConfluence.CapitalCity = TEXT("Goldport");
	MerchantConfluence.Zones = {
		FZoneDetail{ 124, TEXT("Goldport Harbor"), 8, EZoneType::Port, TEXT("Busiest trading port") },
		FZoneDetail{ 125, TEXT("Silvermarrow Market"), 6, EZoneType::Town, TEXT("Great trading hub") },
		FZoneDetail{ 126, TEXT("Caravan Routes"), 5, EZoneType::Plains, TEXT("Merchant roads crossing continent") }
	};
	Continent.Regions.Add(MerchantConfluence);

	// Region 3: Northmark Frontier
	FRegion Northmark;
	Northmark.RegionId = 9;
	Northmark.Name = TEXT("The Northmark Frontier");
	Northmark.Description = TEXT("Wild frontier lands home to rangers and adventurers");
	Northmark.RecommendedLevel = 15;
	Northmark.RegionType = TEXT("Wilderness");
	Northmark.BiomeType = EBiomeType::Taiga;
	Northmark.Population = 300000;
	Northmark.GovernmentType = EGovernmentType::RangerOrder;
	Northmark.Ruler = TEXT("Ranger Captain Thorne");
	Northmark.CapitalCity = TEXT("Sentinel Keep");
	Northmark.Zones = {
		FZoneDetail{ 127, TEXT("Sentinel Keep Outpost"), 15, EZoneType::Outpost, TEXT("Frontier defense post") },
		FZoneDetail{ 128, TEXT("Wildwood Expanse"), 18, EZoneType::Forest, TEXT("Untamed wilderness") },
		FZoneDetail{ 129, TEXT("Beast Hollows"), 22, EZoneType::Cave, TEXT("Lair of dangerous creatures") }
	};
	Continent.Regions.Add(Northmark);

	return Continent;
}

FContinent UWorldDefinition::BuildKharanosContinent()
{
	FContinent Continent;
	Continent.ContinentId = 4;
	Continent.Name = TEXT("Kharanos");
	Continent.Description = TEXT("The southern desert continent of ancient civilizations and buried treasures");
	Continent.AreaSquareMiles = 950000;
	Continent.Population = 2000000;
	Continent.Theme = TEXT("Deserts, Tombs, Ancient Ruins");

	// Region 1: Scarab Dynasty
	FRegion ScarabDynasty;
	ScarabDynasty.RegionId = 10;
	ScarabDynasty.Name = TEXT("Scarab Dynasty");
	ScarabDynasty.Description = TEXT("Ancient Egyptian-inspired civilization with pyramids and tombs");
	ScarabDynasty.RecommendedLevel = 18;
	ScarabDynasty.RegionType = TEXT("Desert");
	ScarabDynasty.BiomeType = EBiomeType::Desert;
	ScarabDynasty.Population = 800000;
	ScarabDynasty.GovernmentType = EGovernmentType::DivineMonarchy;
	ScarabDynasty.Ruler = TEXT("Pharaoh Amenhotep");
	ScarabDynasty.CapitalCity = TEXT("Amuntep");
	ScarabDynasty.Zones = {
		FZoneDetail{ 130, TEXT("Amuntep City"), 18, EZoneType::City, TEXT("Grand pharaoh capital") },
		FZoneDetail{ 131, TEXT("Valley of Kings"), 22, EZoneType::Ruins, TEXT("Ancient royal tombs") },
		FZoneDetail{ 132, TEXT("The Great Pyramid of Khen"), 26, EZoneType::Dungeon, TEXT("Massive ancient structure") }
	};
	Continent.Regions.Add(ScarabDynasty);

	// Region 2: Endless Dunes
	FRegion EndlessDunes;
	EndlessDunes.RegionId = 11;
	EndlessDunes.Name = TEXT("Endless Dunes");
	EndlessDunes.Description = TEXT("Vast golden deserts with oasis settlements");
	EndlessDunes.RecommendedLevel = 15;
	EndlessDunes.RegionType = TEXT("Desert Wasteland");
	EndlessDunes.BiomeType = EBiomeType::Desert;
	EndlessDunes.Population = 500000;
	EndlessDunes.GovernmentType = EGovernmentType::Tribal;
	EndlessDunes.Ruler = TEXT("Sheikh Abubakar");
	EndlessDunes.CapitalCity = TEXT("Oasis Prime");
	EndlessDunes.Zones = {
		FZoneDetail{ 133, TEXT("Oasis Prime"), 15, EZoneType::Town, TEXT("Largest desert oasis") },
		FZoneDetail{ 134, TEXT("Sunscorch Wastes"), 19, EZoneType::Plains, TEXT("Hottest desert regions") },
		FZoneDetail{ 135, TEXT("Mirage Canyons"), 23, EZoneType::Cavern, TEXT("Hidden canyon systems") }
	};
	Continent.Regions.Add(EndlessDunes);

	// Region 3: Lusatian Jungles
	FRegion LusatianJungles;
	LusatianJungles.RegionId = 12;
	LusatianJungles.Name = TEXT("Lusatian Jungles");
	LusatianJungles.Description = TEXT("Tropical jungles with lost civilizations");
	LusatianJungles.RecommendedLevel = 20;
	LusatianJungles.RegionType = TEXT("Jungle");
	LusatianJungles.BiomeType = EBiomeType::TropicalRainforest;
	LusatianJungles.Population = 400000;
	LusatianJungles.GovernmentType = EGovernmentType::Tribal;
	LusatianJungles.Ruler = TEXT("Shaman Kaida");
	LusatianJungles.CapitalCity = TEXT("Serpent Temple");
	LusatianJungles.Zones = {
		FZoneDetail{ 136, TEXT("Serpent Temple"), 20, EZoneType::Temple, TEXT("Vast ancient temple complex") },
		FZoneDetail{ 137, TEXT("Curse Jungle"), 24, EZoneType::Forest, TEXT("Dangerous overgrown wilderness") },
		FZoneDetail{ 138, TEXT("Lost City of Azurheim"), 28, EZoneType::Ruins, TEXT("Sunken civilization ruins") }
	};
	Continent.Regions.Add(LusatianJungles);

	return Continent;
}

FContinent UWorldDefinition::BuildAethralContinent()
{
	FContinent Continent;
	Continent.ContinentId = 5;
	Continent.Name = TEXT("Aethral");
	Continent.Description = TEXT("The central continent where great powers collide and ancient evils stir");
	Continent.AreaSquareMiles = 1000000;
	Continent.Population = 3500000;
	Continent.Theme = TEXT("Contested Lands, Dark Magic, Battlefields");

	// Region 1: Shadowlands
	FRegion Shadowlands;
	Shadowlands.RegionId = 13;
	Shadowlands.Name = TEXT("The Shadowlands");
	Shadowlands.Description = TEXT("Corrupted lands where darkness reigns supreme");
	Shadowlands.RecommendedLevel = 25;
	Shadowlands.RegionType = TEXT("Dark Badlands");
	Shadowlands.BiomeType = EBiomeType::CorruptedLands;
	Shadowlands.Population = 1000000;
	Shadowlands.GovernmentType = EGovernmentType::NecroticTyranny;
	Shadowlands.Ruler = TEXT("The Lich King Morthos");
	Shadowlands.CapitalCity = TEXT("Blackthorn Citadel");
	Shadowlands.Zones = {
		FZoneDetail{ 139, TEXT("Blackthorn Citadel"), 25, EZoneType::Castle, TEXT("Seat of undeath") },
		FZoneDetail{ 140, TEXT("Plaguelands"), 28, EZoneType::Unknown, TEXT("Disease-ridden wasteland") },
		FZoneDetail{ 141, TEXT("Eternal Darkness"), 32, EZoneType::Dungeon, TEXT("Ultimate evil lair") }
	};
	Continent.Regions.Add(Shadowlands);

	// Region 2: Demonfire Wastes
	FRegion DemonfireWastes;
	DemonfireWastes.RegionId = 14;
	DemonfireWastes.Name = TEXT("Demonfire Wastes");
	DemonfireWastes.Description = TEXT("Hell-touched lands of lava and demonic corruption");
	DemonfireWastes.RecommendedLevel = 22;
	DemonfireWastes.RegionType = TEXT("Volcanic Wasteland");
	DemonfireWastes.BiomeType = EBiomeType::Volcano;
	DemonfireWastes.Population = 250000;
	DemonfireWastes.GovernmentType = EGovernmentType::DemonicHierarchy;
	DemonfireWastes.Ruler = TEXT("Archfiend Baltazar");
	DemonfireWastes.CapitalCity = TEXT("Infernus");
	DemonfireWastes.Zones = {
		FZoneDetail{ 142, TEXT("Infernus City"), 22, EZoneType::City, TEXT("Demon stronghold") },
		FZoneDetail{ 143, TEXT("Brimstone Fields"), 25, EZoneType::Unknown, TEXT("Burning hellscape") },
		FZoneDetail{ 144, TEXT("Abyssal Throne"), 30, EZoneType::Dungeon, TEXT("Demon lord's domain") }
	};
	Continent.Regions.Add(DemonfireWastes);

	// Region 3: Contested Badlands
	FRegion ContestedBadlands;
	ContestedBadlands.RegionId = 15;
	ContestedBadlands.Name = TEXT("Contested Badlands");
	ContestedBadlands.Description = TEXT("Battleground between multiple factions");
	ContestedBadlands.RecommendedLevel = 16;
	ContestedBadlands.RegionType = TEXT("Rocky Badlands");
	ContestedBadlands.BiomeType = EBiomeType::GrasslandPlains;
	ContestedBadlands.Population = 800000;
	ContestedBadlands.GovernmentType = EGovernmentType::MultiFaction;
	ContestedBadlands.Ruler = TEXT("Various Warlords");
	ContestedBadlands.CapitalCity = TEXT("Warforge Keep");
	ContestedBadlands.Zones = {
		FZoneDetail{ 145, TEXT("Warforge Keep"), 16, EZoneType::Fortress, TEXT("Neutral stronghold") },
		FZoneDetail{ 146, TEXT("Blood Fields"), 20, EZoneType::Plains, TEXT("Constant battle zone") },
		FZoneDetail{ 147, TEXT("Warlord's Bastion"), 24, EZoneType::Dungeon, TEXT("Tyrant's stronghold") }
	};
	Continent.Regions.Add(ContestedBadlands);

	return Continent;
}

FContinent UWorldDefinition::BuildDeepmoorContinent()
{
	FContinent Continent;
	Continent.ContinentId = 6;
	Continent.Name = TEXT("Deepmoor");
	Continent.Description = TEXT("The vast underground network of caverns, mines, and subterranean kingdoms");
	Continent.AreaSquareMiles = 650000;
	Continent.Population = 1500000;
	Continent.Theme = TEXT("Underground Cities, Crystal Caverns, Mysterious Depths");

	// Region 1: Khaz-Modan
	FRegion KhazModan;
	KhazModan.RegionId = 16;
	KhazModan.Name = TEXT("Khaz-Modan");
	KhazModan.Description = TEXT("Interconnected dwarven cities beneath the world");
	KhazModan.RecommendedLevel = 10;
	KhazModan.RegionType = TEXT("Underground Network");
	KhazModan.BiomeType = EBiomeType::Mountain;
	KhazModan.Population = 700000;
	KhazModan.GovernmentType = EGovernmentType::DwarvenClans;
	KhazModan.Ruler = TEXT("Grand Council of Clans");
	KhazModan.CapitalCity = TEXT("Ironforge Underground");
	KhazModan.Zones = {
		FZoneDetail{ 148, TEXT("Main Trade Tunnels"), 10, EZoneType::Underground, TEXT("Major dwarven highways") },
		FZoneDetail{ 149, TEXT("Crystal Caverns"), 14, EZoneType::Cavern, TEXT("Gem mining operations") },
		FZoneDetail{ 150, TEXT("Deepforge Sanctuary"), 18, EZoneType::Temple, TEXT("Ancient dwarven temple") }
	};
	Continent.Regions.Add(KhazModan);

	// Region 2: Underdark Abyss
	FRegion UnderdarkAbyss;
	UnderdarkAbyss.RegionId = 17;
	UnderdarkAbyss.Name = TEXT("Underdark Abyss");
	UnderdarkAbyss.Description = TEXT("Darkest depths where the Drow rule supreme");
	UnderdarkAbyss.RecommendedLevel = 20;
	UnderdarkAbyss.RegionType = TEXT("Deep Underground");
	UnderdarkAbyss.BiomeType = EBiomeType::Underground;
	UnderdarkAbyss.Population = 450000;
	UnderdarkAbyss.GovernmentType = EGovernmentType::MatriarchalTheocracy;
	UnderdarkAbyss.Ruler = TEXT("Matriarch Lolth's Chosen");
	UnderdarkAbyss.CapitalCity = TEXT("Menzoberranzan");
	UnderdarkAbyss.Zones = {
		FZoneDetail{ 151, TEXT("Menzoberranzan"), 20, EZoneType::City, TEXT("Dark elven metropolis") },
		FZoneDetail{ 152, TEXT("Spider Warrens"), 23, EZoneType::Cavern, TEXT("Drow breeding grounds") },
		FZoneDetail{ 153, TEXT("Yochlol's Lair"), 28, EZoneType::Dungeon, TEXT("Demon queen's throne") }
	};
	Continent.Regions.Add(UnderdarkAbyss);

	// Region 3: Fungal Depths
	FRegion FungalDepths;
	FungalDepths.RegionId = 18;
	FungalDepths.Name = TEXT("Fungal Depths");
	FungalDepths.Description = TEXT("Bioluminescent caverns filled with otherworldly lifeforms");
	FungalDepths.RecommendedLevel = 15;
	FungalDepths.RegionType = TEXT("Biological Caverns");
	FungalDepths.BiomeType = EBiomeType::Underground;
	FungalDepths.Population = 350000;
	FungalDepths.GovernmentType = EGovernmentType::HiveMind;
	FungalDepths.Ruler = TEXT("The Collective");
	FungalDepths.CapitalCity = TEXT("Spore Collective");
	FungalDepths.Zones = {
		FZoneDetail{ 154, TEXT("Spore Collective"), 15, EZoneType::Cavern, TEXT("Fungal intelligence hub") },
		FZoneDetail{ 155, TEXT("Biolume Gardens"), 19, EZoneType::Cavern, TEXT("Glowing organism farms") },
		FZoneDetail{ 156, TEXT("The Myconid Throne"), 24, EZoneType::Dungeon, TEXT("Ancient fungal structure") }
	};
	Continent.Regions.Add(FungalDepths);

	return Continent;
}

FContinent UWorldDefinition::BuildCelestiaContinent()
{
	FContinent Continent;
	Continent.ContinentId = 7;
	Continent.Name = TEXT("Celestia");
	Continent.Description = TEXT("The floating sky islands and cloud cities suspended above the world");
	Continent.AreaSquareMiles = 450000;
	Continent.Population = 1000000;
	Continent.Theme = TEXT("Floating Islands, Sky Cities, Celestial Magic");

	// Region 1: Aethermere Sky
	FRegion Aethermeresky;
	Aethermeresky.RegionId = 19;
	Aethermeresky.Name = TEXT("Aethermere Sky");
	Aethermeresky.Description = TEXT("Ancient sky kingdoms of angels and celestials");
	Aethermeresky.RecommendedLevel = 24;
	Aethermeresky.RegionType = TEXT("Floating Islands");
	Aethermeresky.BiomeType = EBiomeType::FloatingIslands;
	Aethermeresky.Population = 500000;
	Aethermeresky.GovernmentType = EGovernmentType::DivineMonarchy;
	Aethermeresky.Ruler = TEXT("Archangel Uriel");
	Aethermeresky.CapitalCity = TEXT("Heavenspire");
	Aethermeresky.Zones = {
		FZoneDetail{ 157, TEXT("Heavenspire City"), 24, EZoneType::SkyCity, TEXT("Divine city of angels") },
		FZoneDetail{ 158, TEXT("Cloud Sanctuaries"), 27, EZoneType::SkyCity, TEXT("Holy sanctuaries above clouds") },
		FZoneDetail{ 159, TEXT("The Golden Thrones"), 31, EZoneType::Dungeon, TEXT("Celestial divine seat") }
	};
	Continent.Regions.Add(Aethermeresky);

	// Region 2: Storm Islands
	FRegion StormIslands;
	StormIslands.RegionId = 20;
	StormIslands.Name = TEXT("Storm Islands");
	StormIslands.Description = TEXT("Tempestuous islands ruled by storm giants and air elementals");
	StormIslands.RecommendedLevel = 20;
	StormIslands.RegionType = TEXT("Storm Islands");
	StormIslands.BiomeType = EBiomeType::FloatingIslands;
	StormIslands.Population = 300000;
	StormIslands.GovernmentType = EGovernmentType::ElementalHierarchy;
	StormIslands.Ruler = TEXT("Storm Lord Tempestus");
	StormIslands.CapitalCity = TEXT("Stormhaven");
	StormIslands.Zones = {
		FZoneDetail{ 160, TEXT("Stormhaven"), 20, EZoneType::SkyCity, TEXT("Storm giant capital") },
		FZoneDetail{ 161, TEXT("Lightning Peaks"), 23, EZoneType::Mountain, TEXT("Electric storm mountains") },
		FZoneDetail{ 162, TEXT("The Eye of the Maelstrom"), 28, EZoneType::Dungeon, TEXT("Eternal storm core") }
	};
	Continent.Regions.Add(StormIslands);

	return Continent;
}

// ==================== HELPER FUNCTIONS ====================

FString UWorldDefinition::BiomeTypeToString(EBiomeType BiomeType) const
{
	switch (BiomeType)
	{
	case EBiomeType::GrasslandPlains: return TEXT("Grassland Plains");
	case EBiomeType::TemperateForest: return TEXT("Temperate Forest");
	case EBiomeType::Mountain: return TEXT("Mountain");
	case EBiomeType::Tundra: return TEXT("Tundra");
	case EBiomeType::Desert: return TEXT("Desert");
	case EBiomeType::TropicalRainforest: return TEXT("Tropical Rainforest");
	case EBiomeType::Volcano: return TEXT("Volcano");
	case EBiomeType::Underground: return TEXT("Underground");
	case EBiomeType::FloatingIslands: return TEXT("Floating Islands");
	case EBiomeType::Taiga: return TEXT("Taiga");
	case EBiomeType::CorruptedLands: return TEXT("Corrupted Lands");
	default: return TEXT("Unknown");
	}
}

FString UWorldDefinition::ZoneTypeToString(EZoneType ZoneType) const
{
	switch (ZoneType)
	{
	case EZoneType::City: return TEXT("City");
	case EZoneType::Town: return TEXT("Town");
	case EZoneType::Village: return TEXT("Village");
	case EZoneType::Castle: return TEXT("Castle");
	case EZoneType::Fortress: return TEXT("Fortress");
	case EZoneType::Dungeon: return TEXT("Dungeon");
	case EZoneType::Cave: return TEXT("Cave");
	case EZoneType::Forest: return TEXT("Forest");
	case EZoneType::Plains: return TEXT("Plains");
	case EZoneType::Desert: return TEXT("Desert");
	case EZoneType::Mountain: return TEXT("Mountain");
	case EZoneType::Underground: return TEXT("Underground");
	case EZoneType::Ruins: return TEXT("Ruins");
	case EZoneType::Cavern: return TEXT("Cavern");
	case EZoneType::Temple: return TEXT("Temple");
	case EZoneType::SkyCity: return TEXT("Sky City");
	case EZoneType::Port: return TEXT("Port");
	case EZoneType::Outpost: return TEXT("Outpost");
	default: return TEXT("Unknown");
	}
}

FString UWorldDefinition::GovernmentTypeToString(EGovernmentType GovernmentType) const
{
	switch (GovernmentType)
	{
	case EGovernmentType::Monarchy: return TEXT("Monarchy");
	case EGovernmentType::Theocracy: return TEXT("Theocracy");
	case EGovernmentType::Tribal: return TEXT("Tribal");
	case EGovernmentType::Republic: return TEXT("Republic");
	case EGovernmentType::MageCouncil: return TEXT("Mage Council");
	case EGovernmentType::RangerOrder: return TEXT("Ranger Order");
	case EGovernmentType::DwarvenClans: return TEXT("Dwarven Clans");
	case EGovernmentType::NecroticTyranny: return TEXT("Necrotic Tyranny");
	case EGovernmentType::DemonicHierarchy: return TEXT("Demonic Hierarchy");
	case EGovernmentType::MultiFaction: return TEXT("Multi-Faction");
	case EGovernmentType::DruidicCouncil: return TEXT("Druidic Council");
	case EGovernmentType::MatriarchalTheocracy: return TEXT("Matriarchal Theocracy");
	case EGovernmentType::ElementalHierarchy: return TEXT("Elemental Hierarchy");
	case EGovernmentType::DivineMonarchy: return TEXT("Divine Monarchy");
	case EGovernmentType::HiveMind: return TEXT("Hive Mind");
	default: return TEXT("Unknown");
	}
}
