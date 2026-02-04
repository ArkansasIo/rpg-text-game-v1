#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/PlayerCharacter.h"
#include "Character/EnemyCharacter.h"
#include "DungeonSystem.generated.h"

// Dungeon difficulty levels
UENUM(BlueprintType)
enum class EDungeonDifficulty : uint8
{
	Normal,
	Heroic,
	Mythic,
	MythicPlus
};

// Dungeon type
UENUM(BlueprintType)
enum class EDungeonType : uint8
{
	StandardDungeon,
	Raid,
	Trial,
	Challenge,
	Scenario,
	WorldBoss
};

// Dungeon boss definition
USTRUCT(BlueprintType)
struct FDungeonBoss
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	int32 Health = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	bool bIsRaidBoss = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss")
	TArray<FString> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	TArray<FString> LootTable;
};

// Dungeon definition
USTRUCT(BlueprintType)
struct FDungeonTemplate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 DungeonId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	EDungeonType Type = EDungeonType::StandardDungeon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	int32 MinLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	int32 MaxLevel = 120;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	int32 MinPlayers = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")
	int32 MaxPlayers = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	TArray<EDungeonDifficulty> AvailableDifficulties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	TArray<FDungeonBoss> Bosses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	TArray<FString> Rewards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	int32 EstimatedTimeMinutes = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
	FString Location;
};

// Dungeon instance run
USTRUCT(BlueprintType)
struct FDungeonRun
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	FDungeonTemplate DungeonTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	EDungeonDifficulty Difficulty = EDungeonDifficulty::Normal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	int32 CurrentBossIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	float StartTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	int32 DeathCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	bool bIsCompleted = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	bool bIsActive = false;
};

// Event delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnBossDefeated, FString, BossName, int32, RewardXP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Three(FOnDungeonCompleted, FString, DungeonName, float, CompletionTime, int32, TotalRewards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnDungeonFailed, FString, FailureReason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnPartyMemberDied, ACharacter*, DeadCharacter, int32, DeathCount);

/**
 * Dungeon System - manages all dungeon instances and difficulty
 */
UCLASS(Blueprintable, BlueprintType)
class RPGPROJECT_API UDungeonSystem : public UObject
{
	GENERATED_BODY()

public:
	UDungeonSystem();

	// Dungeon initialization and access
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void InitializeDungeonDatabase();

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FDungeonTemplate GetDungeonById(int32 DungeonId);

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	TArray<FDungeonTemplate> GetAllDungeons();

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	TArray<FDungeonTemplate> GetDungeonsByType(EDungeonType Type);

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	TArray<FDungeonTemplate> GetDungeonsByLevelRange(int32 MinLevel, int32 MaxLevel);

	// Dungeon instance management
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	bool EnterDungeon(int32 DungeonId, EDungeonDifficulty Difficulty);

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void ExitDungeon();

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	bool IsInDungeon() const;

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void DefeatCurrentBoss(int32 RewardXP);

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void OnPartyMemberDeath();

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void CompleteDungeon();

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void FailDungeon(const FString& Reason = TEXT("Wipe"));

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	const FDungeonRun& GetCurrentDungeonRun() const { return CurrentRun; }

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FDungeonBoss GetCurrentBoss() const;

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	float GetElapsedTime() const;

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	int32 GetRemainingBosses() const;

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FString GetDifficultyModifier(EDungeonDifficulty Difficulty) const;

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	FString GetDungeonDescription() const;

	// Statistics
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	int32 GetTotalDungeonsCompleted() const { return CompletedDungeonCount; }

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	int32 GetTotalDungeonsFailed() const { return FailedDungeonCount; }

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	float GetAverageCompletionTime() const;

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	bool CanEnterDungeon(int32 PlayerLevel, int32 PartySize) const;

	UFUNCTION(BlueprintCallable, Category = "Dungeon")
	void DisplayDungeonInfo(int32 DungeonId) const;

	// Events
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnBossDefeated OnBossDefeated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnDungeonCompleted OnDungeonCompleted;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnDungeonFailed OnDungeonFailed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnPartyMemberDied OnPartyMemberDied;

protected:
	// Current dungeon run
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instance")
	FDungeonRun CurrentRun;

	// Dungeon database
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	TArray<FDungeonTemplate> DungeonDatabase;

	// Statistics
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 CompletedDungeonCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 FailedDungeonCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	TArray<float> CompletionTimes;

	// Initialize helper
private:
	void PopulateDungeonDatabase();
};
