#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnemyCharacter.generated.h"

// Enemy type classification
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Beast,
	Humanoid,
	Undead,
	Demon,
	Elemental,
	Dragon,
	Giant,
	Aberration,
	Mechanical,
	Critter,
	Dragonkin
};

// Enemy rank/difficulty
UENUM(BlueprintType)
enum class EEnemyRank : uint8
{
	Normal,
	Elite,
	RareElite,
	Boss,
	WorldBoss,
	RaidBoss
};

// Enemy ability definition
USTRUCT(BlueprintType)
struct FEnemyAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	int32 ManaCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float CooldownTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	int32 BaseDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float CastTime = 0.5f;
};

// Loot item definition
USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	int32 ItemId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	float DropChance = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	int32 Quantity = 1;
};

// Enemy template - defines enemy type characteristics
USTRUCT(BlueprintType)
struct FEnemyTemplate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 TemplateId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	EEnemyType Type = EEnemyType::Beast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	EEnemyRank Rank = EEnemyRank::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Mana = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Attack = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Defense = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MagicPower = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<FEnemyAbility> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<FString> Resistances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TArray<FString> Weaknesses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	int32 XPReward = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	int32 GoldReward = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	TArray<FLootItem> LootTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	float DropRate = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FString Description;
};

// Event delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEnemyDamaged, AEnemyCharacter*, Enemy, int32, DamageAmount, FString, DamageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnEnemyDeath, AEnemyCharacter*, DeadEnemy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnEnemyAgro, AEnemyCharacter*, Enemy, AActor*, AggroTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnAbilityCast, AEnemyCharacter*, Enemy, FString, AbilityName);

/**
 * Enemy Character - represents all enemy types in the game
 */
UCLASS()
class RPGPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Initialization
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void InitializeFromTemplate(const FEnemyTemplate& Template);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void InitializeFromId(int32 EnemyTemplateId);

	// Combat
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 TakeDamage(int32 BaseDamage, const FString& DamageType = TEXT("Physical"));

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Heal(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CastAbility(int32 AbilityIndex);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanCastAbility(int32 AbilityIndex) const;

	// Aggro
	UFUNCTION(BlueprintCallable, Category = "AI")
	void Aggro(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void ClearAggro();

	UFUNCTION(BlueprintCallable, Category = "AI")
	bool IsAggroed() const;

	// Loot
	UFUNCTION(BlueprintCallable, Category = "Rewards")
	TArray<FLootItem> GenerateLoot();

	// Buff/Debuff
	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void AddBuff(const FString& BuffName, float Duration);

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void AddDebuff(const FString& DebuffName, float Duration);

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void RemoveBuff(const FString& BuffName);

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void RemoveDebuff(const FString& DebuffName);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	const FEnemyTemplate& GetTemplate() const { return EnemyTemplate; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	FString GetEnemyName() const { return EnemyTemplate.Name; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	int32 GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	int32 GetMaxHealth() const { return EnemyTemplate.Health; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	int32 GetCurrentMana() const { return CurrentMana; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	int32 GetMaxMana() const { return EnemyTemplate.Mana; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool IsAlive() const { return CurrentHealth > 0; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetAttackPower() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetDefensePower() const { return EnemyTemplate.Defense; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 GetMagicPower() const { return EnemyTemplate.MagicPower; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	EEnemyRank GetRank() const { return EnemyTemplate.Rank; }

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	int32 GetLevel() const { return EnemyTemplate.Level; }

	UFUNCTION(BlueprintCallable, Category = "Rewards")
	int32 GetXPReward() const { return EnemyTemplate.XPReward; }

	UFUNCTION(BlueprintCallable, Category = "Rewards")
	int32 GetGoldReward() const { return EnemyTemplate.GoldReward; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool HasWeakness(const FString& DamageType) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool HasResistance(const FString& DamageType) const;

	// Static enemy templates database
	UFUNCTION(BlueprintCallable, Category = "Enemy", meta = (WorldContext = "WorldContextObject"))
	static FEnemyTemplate GetTemplateById(int32 TemplateId);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	static TArray<FEnemyTemplate> GetAllEnemyTemplates();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	static TArray<FEnemyTemplate> GetEnemiesByType(EEnemyType Type);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	static TArray<FEnemyTemplate> GetEnemiesByLevel(int32 MinLevel, int32 MaxLevel);

	// Events
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnEnemyDamaged OnDamaged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnEnemyDeath OnDeath;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnEnemyAgro OnAggro;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnAbilityCast OnAbilityCast;

protected:
	// Enemy template data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	FEnemyTemplate EnemyTemplate;

	// Current health and mana
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 CurrentHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 CurrentMana = 0;

	// Combat state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	AActor* AggroTarget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusEffects")
	TArray<FString> ActiveBuffs;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusEffects")
	TArray<FString> ActiveDebuffs;

	// Ability cooldowns
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TMap<int32, float> AbilityCooldowns;

	// Tick-based resource regeneration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float ManaRegenRate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float ManaRegenTickRate = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	float ManaRegenTimer = 0.0f;

	// Ability state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	int32 CurrentCastingAbility = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	float CurrentCastTime = 0.0f;

private:
	// Internal helper methods
	void RegenerateMana(float DeltaTime);
	void UpdateAbilityCooldowns(float DeltaTime);
	void UpdateCasting(float DeltaTime);
	int32 ApplyDamageTypeModifiers(int32 Damage, const FString& DamageType) const;

	// Static enemy database
	static void InitializeEnemyDatabase();
	static TArray<FEnemyTemplate> EnemyDatabase;
	static bool bEnemyDatabaseInitialized;
};
