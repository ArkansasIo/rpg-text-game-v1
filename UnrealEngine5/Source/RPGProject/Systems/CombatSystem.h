#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../RPGTypes.h"
#include "CombatSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnDamageDealtDelegate, float, DamageAmount, ECharacterStatType, DamageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnCriticalHitDelegate, float, CriticalDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnDefendDelegate, float, DamageBlocked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatEndDelegate);

USTRUCT(BlueprintType)
struct FCombatStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AccuracyPercentage = 85.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalChance = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlockChance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DodgeChance = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSteal = 0.0f; // Percentage of damage dealt as healing
};

/**
 * Combat System for handling damage, abilities, and combat mechanics
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UCombatSystem : public UObject
{
	GENERATED_BODY()

public:
	UCombatSystem();

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FCharacterStats AttackerStats;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FCharacterStats DefenderStats;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FCombatStats CombatStats;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool bIsInCombat = false;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	float CurrentHealth = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	float CurrentMana = 50.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	float CurrentStamina = 100.0f;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Combat Events")
	FOnDamageDealtDelegate OnDamageDealt;

	UPROPERTY(BlueprintAssignable, Category = "Combat Events")
	FOnCriticalHitDelegate OnCriticalHit;

	UPROPERTY(BlueprintAssignable, Category = "Combat Events")
	FOnDefendDelegate OnDefend;

	UPROPERTY(BlueprintAssignable, Category = "Combat Events")
	FOnCombatStartDelegate OnCombatStart;

	UPROPERTY(BlueprintAssignable, Category = "Combat Events")
	FOnCombatEndDelegate OnCombatEnd;

	// Combat Functions
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartCombat();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndCombat();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float CalculateDamage(ECharacterStatType DamageType);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float ApplyDefense(float IncomingDamage, ECharacterStatType DamageType);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool AttemptAbility(const FString& AbilityName, float ManaCost);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool AttemptDodge();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool AttemptBlock();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegenerateResources(float DeltaTime);

private:
	bool bCriticalHit = false;
	float RegenerationTimer = 0.0f;
};
