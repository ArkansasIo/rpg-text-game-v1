#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "World/WorldDefinition.h"
#include "AethermoorWorldSystem.generated.h"

// Forward declarations
class UWorldDefinition;
class UFactionSystem;
class UWorldCharacters;

// World statistics structure
USTRUCT(BlueprintType)
struct FWorldStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalContinents = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalRegions = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalZones = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalPopulation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalFactions = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalCharacters = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalArtifacts = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalLegendaryBeasts = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	float AverageCharacterLevel = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 HighestLevelCharacter = 0;
};

// Lore type enumeration
UENUM(BlueprintType)
enum class ELoreType : uint8
{
	Creation,
	Prophecy,
	LichKing,
	DemonIncursion,
	Unknown
};

/**
 * Master World System - Central hub for all world information
 * 
 * Integrates:
 * - 7 Continents with 20 regions and 57 zones
 * - Multiple factions with alliances/rivalries
 * - 50+ major NPC characters
 * - Legendary artifacts and treasures
 * - Legendary boss enemies
 * - World lore and history
 * 
 * This is the primary access point for all world data
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API UAethermoorWorldSystem : public UObject
{
	GENERATED_BODY()

public:
	UAethermoorWorldSystem();

	// Initialization
	UFUNCTION(BlueprintCallable, Category = "World")
	void InitializeWorld();

	// ==================== CONTINENT ACCESS ====================

	UFUNCTION(BlueprintCallable, Category = "World|Continents")
	TArray<FContinent> GetAllContinents() const;

	UFUNCTION(BlueprintCallable, Category = "World|Continents")
	FContinent GetContinentById(int32 ContinentId) const;

	UFUNCTION(BlueprintCallable, Category = "World|Continents")
	FContinent GetContinentByName(const FString& ContinentName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Continents")
	TArray<FRegion> GetRegionsByContinentId(int32 ContinentId) const;

	UFUNCTION(BlueprintCallable, Category = "World|Continents")
	TArray<FZoneDetail> GetZonesByRegionId(int32 ContinentId, int32 RegionId) const;

	// ==================== FACTION ACCESS ====================

	UFUNCTION(BlueprintCallable, Category = "World|Factions")
	int32 GetTotalFactions() const;

	UFUNCTION(BlueprintCallable, Category = "World|Factions")
	TArray<FString> GetAllFactionNames() const;

	UFUNCTION(BlueprintCallable, Category = "World|Factions")
	FString GetFactionDescription(const FString& FactionName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Factions")
	TArray<FString> GetEnemyFactions(const FString& FactionName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Factions")
	TArray<FString> GetAlliedFactions(const FString& FactionName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Factions")
	TArray<FString> GetFactionsByAlignment(const FString& Alignment) const;

	// ==================== CHARACTER ACCESS ====================

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	int32 GetTotalCharacters() const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	TArray<FString> GetAllCharacterNames() const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	TArray<FString> GetCharactersByFaction(const FString& FactionName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	TArray<FString> GetCharactersByLocation(const FString& Location) const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	TArray<FString> GetCharactersByClass(const FString& ClassName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	TArray<FString> GetCharactersByRace(const FString& RaceName) const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	TArray<FString> GetLeadersByRank() const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	int32 GetAverageCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "World|Characters")
	int32 GetHighestLevelCharacter() const;

	// ==================== ARTIFACT ACCESS ====================

	UFUNCTION(BlueprintCallable, Category = "World|Artifacts")
	int32 GetTotalArtifacts() const;

	UFUNCTION(BlueprintCallable, Category = "World|Artifacts")
	TArray<FString> GetAllArtifactNames() const;

	UFUNCTION(BlueprintCallable, Category = "World|Artifacts")
	TArray<FString> GetArtifactsByLocation(const FString& Location) const;

	UFUNCTION(BlueprintCallable, Category = "World|Artifacts")
	TArray<FString> GetArtifactsByLevel(int32 MinLevel) const;

	// ==================== LEGENDARY BEAST ACCESS ====================

	UFUNCTION(BlueprintCallable, Category = "World|Beasts")
	int32 GetTotalLegendaryBeasts() const;

	UFUNCTION(BlueprintCallable, Category = "World|Beasts")
	TArray<FString> GetAllBeastNames() const;

	UFUNCTION(BlueprintCallable, Category = "World|Beasts")
	TArray<FString> GetBeastsByLevel(int32 MinLevel) const;

	UFUNCTION(BlueprintCallable, Category = "World|Beasts")
	TArray<FString> GetDefeatedBeasts() const;

	UFUNCTION(BlueprintCallable, Category = "World|Beasts")
	int32 GetTotalDefeatedBeasts() const;

	// ==================== WORLD STATISTICS ====================

	UFUNCTION(BlueprintCallable, Category = "World|Statistics")
	FWorldStatistics GetWorldStatistics() const;

	UFUNCTION(BlueprintCallable, Category = "World|Statistics")
	FString GetWorldStatisticsString() const;

	// ==================== WORLD INFORMATION ====================

	UFUNCTION(BlueprintCallable, Category = "World|Information")
	FString GetWorldName() const;

	UFUNCTION(BlueprintCallable, Category = "World|Information")
	FString GetWorldTheme() const;

	UFUNCTION(BlueprintCallable, Category = "World|Information")
	FString GetWorldDescription() const;

	UFUNCTION(BlueprintCallable, Category = "World|Information")
	FString GetWorldLore(ELoreType LoreType) const;

	// ==================== TRAVEL & NAVIGATION ====================

	UFUNCTION(BlueprintCallable, Category = "World|Navigation")
	bool CanTravelBetweenZones(int32 FromZoneId, int32 ToZoneId) const;

	UFUNCTION(BlueprintCallable, Category = "World|Navigation")
	TArray<FString> GetRecommendedPath(int32 PlayerLevel) const;

	// ==================== WORLD DISPLAY ====================

	UFUNCTION(BlueprintCallable, Category = "World|Display")
	void DisplayWorldMap() const;

	UFUNCTION(BlueprintCallable, Category = "World|Display")
	void DisplayContinentInfo(int32 ContinentId) const;

	UFUNCTION(BlueprintCallable, Category = "World|Display")
	void DisplayRegionInfo(int32 RegionId) const;

	UFUNCTION(BlueprintCallable, Category = "World|Display")
	void DisplayWorldStatistics() const;

protected:
	// World components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
	UWorldDefinition* WorldDef;

	// Cached data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
	int32 CachedTotalFactions = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
	int32 CachedTotalCharacters = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
	int32 CachedTotalArtifacts = 20;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
	int32 CachedTotalBeasts = 15;

	bool bWorldInitialized = false;

private:
	// Lore strings
	FString GetCreationMythLore() const;
	FString GetAncientProphecyLore() const;
	FString GetLichKingCurseLore() const;
	FString GetDemonIncursionLore() const;
};
