#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../RPGTypes.h"
#include "PlayerCharacter.generated.h"

class UCharacterProgressionSystem;
class UCombatSystem;
class UInventorySystem;
class UQuestSystem;
class UStatusEffectSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnHealthChanged, float, NewHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnManaChanged, float, NewMana, float, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnLevelUpDelegate, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnExperienceGainedDelegate, int32, ExperienceAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnCharacterCreatedDelegate, const FString&, CharacterName);

/**
 * Player Character - Main playable character with all RPG systems
 */
UCLASS(BlueprintType, Blueprintable)
class RPGPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ==================== Character Identity ====================
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString CharacterName = TEXT("Hero");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Race = TEXT("Human");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Class = TEXT("Warrior");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString Specialization = TEXT("Sword Master");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int32 CharacterLevel = 1;

	// ==================== Core Statistics ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Mana = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxMana = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxStamina = 100.0f;

	// ==================== Character Attributes ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 Strength = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 Agility = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 Intelligence = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 Vitality = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int32 Endurance = 10;

	// ==================== Combat Stats ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BaseAttack = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BaseDefense = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float BaseMagicPower = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float CriticalChance = 15.0f;

	// ==================== Progression ====================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 Experience = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 ExperienceToNextLevel = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 SkillPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 Gold = 100;

	// ==================== Status Flags ====================

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	bool bIsAlive = true;

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	bool bIsInCombat = false;

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	bool bIsMovementDisabled = false;

	// ==================== Systems References ====================

	UPROPERTY(BlueprintReadWrite, Category = "Systems")
	class UCharacterProgressionSystem* ProgressionSystem;

	UPROPERTY(BlueprintReadWrite, Category = "Systems")
	class UCombatSystem* CombatSystem;

	UPROPERTY(BlueprintReadWrite, Category = "Systems")
	class UInventorySystem* InventorySystem;

	UPROPERTY(BlueprintReadWrite, Category = "Systems")
	class UQuestSystem* QuestSystem;

	UPROPERTY(BlueprintReadWrite, Category = "Systems")
	class UStatusEffectSystem* StatusEffectSystem;

	// ==================== Events ====================

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnManaChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnExperienceGainedDelegate OnExperienceGained;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterCreatedDelegate OnCharacterCreated;

	// ==================== Initialization ====================

	UFUNCTION(BlueprintCallable, Category = "Character")
	void InitializeCharacter(const FString& InName, const FString& InRace, const FString& InClass);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void InitializeSystems();

	// ==================== Health Management ====================

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void RestoreHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsAlive() const { return Health > 0.0f; }

	// ==================== Mana Management ====================

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void ConsumeMana(float ManaAmount);

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void RestoreMana(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Mana")
	float GetManaPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Mana")
	bool HasEnoughMana(float Required) const { return Mana >= Required; }

	// ==================== Stamina Management ====================

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void ConsumeStamina(float StaminaAmount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void RestoreStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	float GetStaminaPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool HasEnoughStamina(float Required) const { return Stamina >= Required; }

	// ==================== Experience & Leveling ====================

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void GainExperience(int32 ExperienceAmount);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "Progression")
	float GetExperiencePercentage() const;

	// ==================== Attribute Management ====================

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void IncreaseAttribute(ECharacterStatType AttributeType, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetTotalAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetTotalDefense() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetTotalMagicPower() const;

	// ==================== Combat ====================

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EnterCombat();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ExitCombat();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool CanAct() const { return !bIsMovementDisabled && IsAlive(); }

	// ==================== Utility ====================

	UFUNCTION(BlueprintCallable, Category = "Character")
	void DisplayStats();

	UFUNCTION(BlueprintCallable, Category = "Character")
	FString GetFullDescription() const;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void ResetCharacter();

private:
	void UpdateResourceBars();
	void CheckDeath();
	void NotifyHealthChanged();
	void NotifyManaChanged();
};
