#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldDefinition.generated.h"

// ==================== ENUMERATIONS ====================

// Biome classification
UENUM(BlueprintType)
enum class EBiomeType : uint8
{
	GrasslandPlains,
	TemperateForest,
	Mountain,
	Tundra,
	Desert,
	TropicalRainforest,
	Volcano,
	Underground,
	FloatingIslands,
	Taiga,
	CorruptedLands,
	Unknown
};

// Zone types
UENUM(BlueprintType)
enum class EZoneType : uint8
{
	City,
	Town,
	Village,
	Castle,
	Fortress,
	Dungeon,
	Cave,
	Forest,
	Plains,
	Desert,
	Mountain,
	Underground,
	Ruins,
	Cavern,
	Temple,
	SkyCity,
	Port,
	Outpost,
	Unknown
};

// Government types
UENUM(BlueprintType)
enum class EGovernmentType : uint8
{
	Monarchy,
	Theocracy,
	Tribal,
	Republic,
	MageCouncil,
	RangerOrder,
	DwarvenClans,
	NecroticTyranny,
	DemonicHierarchy,
	MultiFaction,
	DruidicCouncil,
	MatriarchalTheocracy,
	ElementalHierarchy,
	DivineMonarchy,
	HiveMind,
	Unknown
};

// ==================== STRUCTURES ====================

// Zone detail - represents a specific zone within a region
USTRUCT(BlueprintType)
struct FZoneDetail
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	int32 ZoneId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	int32 RecommendedLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	EZoneType Type = EZoneType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	FString Description;
};

// Region - represents a major region within a continent
USTRUCT(BlueprintType)
struct FRegion
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	int32 RegionId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	int32 RecommendedLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FString RegionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	EBiomeType BiomeType = EBiomeType::GrasslandPlains;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	int32 Population = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	EGovernmentType GovernmentType = EGovernmentType::Monarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FString Ruler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	FString CapitalCity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Region")
	TArray<FZoneDetail> Zones;
};

// Continent - represents a major landmass in the world
USTRUCT(BlueprintType)
struct FContinent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	int32 ContinentId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	int32 AreaSquareMiles = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	int32 Population = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	FString Theme;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Continent")
	TArray<FRegion> Regions;
};

// ==================== WORLD DEFINITION CLASS ====================

/**
 * Aethermoor World Definition - Defines the entire fantasy world structure
 * 
 * The world "Aethermoor" spans 7 major continents with ~5.3 million square miles
 * Total population: ~50 million across all civilizations
 * 
 * Continents:
 * 1. Valorath (North) - Frozen peaks and dwarven kingdoms
 * 2. Lumeria (East) - Mystical forests and arcane magic
 * 3. Mortalis (West) - Human kingdoms and commerce
 * 4. Kharanos (South) - Desert civilizations and tombs
 * 5. Aethral (Central) - Contested lands and dark magic
 * 6. Deepmoor (Underground) - Subterranean kingdoms
 * 7. Celestia (Sky Realms) - Floating islands and celestials
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API UWorldDefinition : public UObject
{
	GENERATED_BODY()

public:
	UWorldDefinition();

	// Constants
	static const FString WORLD_NAME;
	static const FString WORLD_THEME;

	// World retrieval
	UFUNCTION(BlueprintCallable, Category = "World")
	static FString GetWorldName();

	UFUNCTION(BlueprintCallable, Category = "World")
	static FString GetWorldTheme();

	UFUNCTION(BlueprintCallable, Category = "World")
	TArray<FContinent> GetAllContinents();

	UFUNCTION(BlueprintCallable, Category = "World")
	FContinent GetContinentById(int32 ContinentId);

	UFUNCTION(BlueprintCallable, Category = "World")
	FContinent GetContinentByName(const FString& ContinentName);

	// Region access
	UFUNCTION(BlueprintCallable, Category = "World")
	FRegion GetRegionById(int32 RegionId);

	UFUNCTION(BlueprintCallable, Category = "World")
	FRegion GetRegionByName(const FString& RegionName);

	UFUNCTION(BlueprintCallable, Category = "World")
	TArray<FRegion> GetRegionsByBiome(EBiomeType BiomeType);

	UFUNCTION(BlueprintCallable, Category = "World")
	TArray<FRegion> GetRegionsByLevelRange(int32 MinLevel, int32 MaxLevel);

	// Zone access
	UFUNCTION(BlueprintCallable, Category = "World")
	FZoneDetail GetZoneById(int32 ZoneId);

	UFUNCTION(BlueprintCallable, Category = "World")
	FZoneDetail GetZoneByName(const FString& ZoneName);

	UFUNCTION(BlueprintCallable, Category = "World")
	TArray<FZoneDetail> GetZonesByType(EZoneType ZoneType);

	UFUNCTION(BlueprintCallable, Category = "World")
	TArray<FZoneDetail> GetZonesByLevel(int32 MinLevel, int32 MaxLevel);

	// Statistics
	UFUNCTION(BlueprintCallable, Category = "World")
	int32 GetTotalContinents() const;

	UFUNCTION(BlueprintCallable, Category = "World")
	int32 GetTotalRegions() const;

	UFUNCTION(BlueprintCallable, Category = "World")
	int32 GetTotalZones() const;

	UFUNCTION(BlueprintCallable, Category = "World")
	int32 GetTotalPopulation() const;

	UFUNCTION(BlueprintCallable, Category = "World")
	int32 GetTotalArea() const;

	// World information
	UFUNCTION(BlueprintCallable, Category = "World")
	FString GetWorldDescription() const;

	UFUNCTION(BlueprintCallable, Category = "World")
	void DisplayWorldMap() const;

	UFUNCTION(BlueprintCallable, Category = "World")
	void DisplayContinentInfo(int32 ContinentId) const;

	UFUNCTION(BlueprintCallable, Category = "World")
	void DisplayRegionInfo(int32 RegionId) const;

protected:
	// World data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
	TArray<FContinent> Continents;

	// Database initialization
	UFUNCTION()
	void InitializeWorldDatabase();

private:
	// Continent builders
	FContinent BuildValorathContinent();
	FContinent BuildLumeriaContinent();
	FContinent BuildMortalisContinent();
	FContinent BuildKharanosContinent();
	FContinent BuildAethralContinent();
	FContinent BuildDeepmoorContinent();
	FContinent BuildCelestiaContinent();

	// Helper functions
	FString BiomeTypeToString(EBiomeType BiomeType) const;
	FString ZoneTypeToString(EZoneType ZoneType) const;
	FString GovernmentTypeToString(EGovernmentType GovernmentType) const;

	bool bWorldInitialized = false;
};
