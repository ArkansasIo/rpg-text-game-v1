#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../RPGTypes.h"
#include "CharacterProgressionSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnLevelUpDelegate, int32, NewLevel, int32, SkillPointsGained);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnExperienceGainedDelegate, int32, ExperienceAmount, int32, CurrentExperience);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnStatIncreaseDelegate, const FCharacterStats&, NewStats);

USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxSkillLevel = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaCost = 0.0f;
};

/**
 * Character Progression & Leveling System
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UCharacterProgressionSystem : public UObject
{
	GENERATED_BODY()

public:
	UCharacterProgressionSystem();

	// Level & Experience
	UPROPERTY(BlueprintReadWrite, Category = "Progression")
	int32 CurrentLevel = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Progression")
	int32 CurrentExperience = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Progression")
	int32 ExperienceToNextLevel = 1000;

	UPROPERTY(BlueprintReadWrite, Category = "Progression")
	int32 AvailableSkillPoints = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Progression")
	int32 MaxLevel = 100;

	// Base Stats
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	FCharacterStats BaseStats;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	FCharacterStats BonusStats;

	// Skills & Abilities
	UPROPERTY(BlueprintReadWrite, Category = "Skills")
	TArray<FSkillData> LearnedSkills;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnExperienceGainedDelegate OnExperienceGained;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStatIncreaseDelegate OnStatIncrease;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Progression")
	void GainExperience(int32 ExperienceAmount);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void IncreaseStatByPoints(ECharacterStatType StatType, int32 Points);

	UFUNCTION(BlueprintCallable, Category = "Skills")
	void LearnSkill(const FSkillData& NewSkill);

	UFUNCTION(BlueprintCallable, Category = "Skills")
	void UpgradeSkill(const FString& SkillName);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	FCharacterStats GetTotalStats() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	float GetExperiencePercentage() const;

	UFUNCTION(BlueprintPure, Category = "Skills")
	FSkillData* FindSkill(const FString& SkillName);

private:
	void CalculateExperienceRequirement();
};
