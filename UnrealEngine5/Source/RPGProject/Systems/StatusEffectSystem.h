#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusEffectSystem.generated.h"

UENUM(BlueprintType)
enum class EStatusEffectType : uint8
{
	Poison UMETA(DisplayName = "Poison"),
	Burn UMETA(DisplayName = "Burn"),
	Freeze UMETA(DisplayName = "Freeze"),
	Stun UMETA(DisplayName = "Stun"),
	Bleed UMETA(DisplayName = "Bleed"),
	Curse UMETA(DisplayName = "Curse"),
	Buff UMETA(DisplayName = "Buff"),
	Debuff UMETA(DisplayName = "Debuff"),
	Regeneration UMETA(DisplayName = "Regeneration"),
	Shield UMETA(DisplayName = "Shield")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnStatusEffectAppliedDelegate, EStatusEffectType, EffectType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnStatusEffectRemovedDelegate, EStatusEffectType, EffectType);

USTRUCT(BlueprintType)
struct FStatusEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EffectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatusEffectType EffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EffectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EffectDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemainingTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickInterval = 1.0f; // Damage/heal every second

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickDamage = 5.0f; // Damage per tick

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StatModifier = 0.0f; // % stat change

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stacks = 1; // Can stack effects

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStacks = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanStack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPermanent = false;
};

/**
 * Status Effect & Buff/Debuff System
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UStatusEffectSystem : public UObject
{
	GENERATED_BODY()

public:
	UStatusEffectSystem();

	UPROPERTY(BlueprintReadWrite, Category = "Status Effects")
	TArray<FStatusEffect> ActiveEffects;

	UPROPERTY(BlueprintReadWrite, Category = "Status Effects")
	float TickTimer = 0.0f;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Status Events")
	FOnStatusEffectAppliedDelegate OnStatusEffectApplied;

	UPROPERTY(BlueprintAssignable, Category = "Status Events")
	FOnStatusEffectRemovedDelegate OnStatusEffectRemoved;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void ApplyEffect(const FStatusEffect& NewEffect);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void RemoveEffect(const FString& EffectID);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void RemoveEffectByType(EStatusEffectType EffectType);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void UpdateEffects(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	FStatusEffect* GetEffect(const FString& EffectID);

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	bool HasEffect(EStatusEffectType EffectType) const;

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void ClearAllEffects();

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	void CleansPoison();

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	float GetTotalStatModifier(EStatusEffectType EffectType) const;

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	int32 GetActiveEffectCount() const;

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	bool IsImmobilized() const; // Stun/freeze check

	UFUNCTION(BlueprintCallable, Category = "Status Effects")
	bool IsSlowed() const;

private:
	void ProcessEffectTick(FStatusEffect& Effect, float DeltaTime);
};
