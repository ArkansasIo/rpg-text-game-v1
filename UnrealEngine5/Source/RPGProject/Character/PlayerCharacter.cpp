#include "PlayerCharacter.h"
#include "../Systems/CharacterProgressionSystem.h"
#include "../Systems/CombatSystem.h"
#include "../Systems/InventorySystem.h"
#include "../Systems/QuestSystem.h"
#include "../Systems/StatusEffectSystem.h"
#include "../Systems/RPGGameSystemsManager.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	// Prevent rotation with camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxAcceleration = 2400.0f;

	// Don't rotate character with camera
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!ProgressionSystem)
	{
		InitializeSystems();
	}

	// Initial setup
	if (CombatSystem)
	{
		CombatSystem->CurrentHealth = Health;
	}

	OnCharacterCreated.Broadcast(CharacterName);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update resource regeneration
	if (StatusEffectSystem)
	{
		StatusEffectSystem->UpdateEffects(DeltaTime);
	}

	if (CombatSystem)
	{
		CombatSystem->RegenerateResources(DeltaTime);
	}

	// Sync health with combat system
	if (CombatSystem && CombatSystem->CurrentHealth != Health)
	{
		Health = CombatSystem->CurrentHealth;
		NotifyHealthChanged();
	}

	UpdateResourceBars();
	CheckDeath();
}

void APlayerCharacter::InitializeCharacter(const FString& InName, const FString& InRace, const FString& InClass)
{
	CharacterName = InName;
	Race = InRace;
	Class = InClass;

	// Set class-specific stats
	if (Class == TEXT("Warrior"))
	{
		Strength = 15;
		Vitality = 14;
		BaseAttack = 15.0f;
		BaseDefense = 10.0f;
		MaxHealth = 120.0f;
	}
	else if (Class == TEXT("Mage"))
	{
		Intelligence = 16;
		Endurance = 12;
		BaseMagicPower = 15.0f;
		MaxMana = 100.0f;
	}
	else if (Class == TEXT("Rogue"))
	{
		Agility = 16;
		Intelligence = 12;
		BaseAttack = 12.0f;
		CriticalChance = 25.0f;
	}
	else if (Class == TEXT("Paladin"))
	{
		Strength = 13;
		Vitality = 13;
		Intelligence = 12;
		BaseAttack = 12.0f;
		BaseDefense = 12.0f;
	}

	Health = MaxHealth;
	Mana = MaxMana;
	Stamina = MaxStamina;

	InitializeSystems();
	OnCharacterCreated.Broadcast(CharacterName);

	UE_LOG(LogTemp, Warning, TEXT("Character Created: %s - %s %s"), *CharacterName, *Race, *Class);
}

void APlayerCharacter::InitializeSystems()
{
	// Get game systems manager
	ARPGGameSystemsManager* GameSystems = Cast<ARPGGameSystemsManager>(GetWorld()->GetGameState());
	if (!GameSystems)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get RPG Game Systems Manager!"));
		return;
	}

	// Get all systems
	ProgressionSystem = GameSystems->GetProgressionSystem();
	CombatSystem = GameSystems->GetCombatSystem();
	InventorySystem = GameSystems->GetInventorySystem();
	QuestSystem = GameSystems->GetQuestSystem();
	StatusEffectSystem = GameSystems->GetStatusEffectSystem();

	// Initialize combat system with player stats
	if (CombatSystem)
	{
		CombatSystem->CurrentHealth = Health;
		CombatSystem->CurrentMana = Mana;
		CombatSystem->CurrentStamina = Stamina;
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Systems Initialized"));
}

void APlayerCharacter::TakeDamage(float DamageAmount)
{
	if (!IsAlive())
	{
		return;
	}

	Health -= DamageAmount;
	if (Health < 0.0f)
	{
		Health = 0.0f;
	}

	NotifyHealthChanged();
	CheckDeath();

	UE_LOG(LogTemp, Warning, TEXT("%s takes %.0f damage! Health: %.0f/%.0f"), 
		*CharacterName, DamageAmount, Health, MaxHealth);
}

void APlayerCharacter::Heal(float HealAmount)
{
	Health += HealAmount;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}

	NotifyHealthChanged();
}

void APlayerCharacter::RestoreHealth(float Amount)
{
	Heal(Amount);
}

float APlayerCharacter::GetHealthPercentage() const
{
	if (MaxHealth <= 0.0f)
	{
		return 0.0f;
	}
	return (Health / MaxHealth) * 100.0f;
}

void APlayerCharacter::ConsumeMana(float ManaAmount)
{
	Mana -= ManaAmount;
	if (Mana < 0.0f)
	{
		Mana = 0.0f;
	}

	NotifyManaChanged();
}

void APlayerCharacter::RestoreMana(float Amount)
{
	Mana += Amount;
	if (Mana > MaxMana)
	{
		Mana = MaxMana;
	}

	NotifyManaChanged();
}

float APlayerCharacter::GetManaPercentage() const
{
	if (MaxMana <= 0.0f)
	{
		return 0.0f;
	}
	return (Mana / MaxMana) * 100.0f;
}

void APlayerCharacter::ConsumeStamina(float StaminaAmount)
{
	Stamina -= StaminaAmount;
	if (Stamina < 0.0f)
	{
		Stamina = 0.0f;
	}
}

void APlayerCharacter::RestoreStamina(float Amount)
{
	Stamina += Amount;
	if (Stamina > MaxStamina)
	{
		Stamina = MaxStamina;
	}
}

float APlayerCharacter::GetStaminaPercentage() const
{
	if (MaxStamina <= 0.0f)
	{
		return 0.0f;
	}
	return (Stamina / MaxStamina) * 100.0f;
}

void APlayerCharacter::GainExperience(int32 ExperienceAmount)
{
	if (ProgressionSystem)
	{
		ProgressionSystem->GainExperience(ExperienceAmount);
		CharacterLevel = ProgressionSystem->CurrentLevel;
		Experience = ProgressionSystem->CurrentExperience;
		ExperienceToNextLevel = ProgressionSystem->ExperienceToNextLevel;

		OnExperienceGained.Broadcast(ExperienceAmount);
	}
}

void APlayerCharacter::LevelUp()
{
	if (ProgressionSystem)
	{
		ProgressionSystem->LevelUp();
		CharacterLevel = ProgressionSystem->CurrentLevel;
		SkillPoints = ProgressionSystem->AvailableSkillPoints;

		// Increase stats on level up
		MaxHealth += 20.0f;
		MaxMana += 10.0f;
		MaxStamina += 10.0f;
		Health = MaxHealth;
		Mana = MaxMana;
		Stamina = MaxStamina;

		OnLevelUp.Broadcast(CharacterLevel);

		UE_LOG(LogTemp, Warning, TEXT("%s leveled up to %d!"), *CharacterName, CharacterLevel);
	}
}

float APlayerCharacter::GetExperiencePercentage() const
{
	if (ExperienceToNextLevel <= 0)
	{
		return 1.0f;
	}

	return static_cast<float>(Experience) / static_cast<float>(ExperienceToNextLevel);
}

void APlayerCharacter::IncreaseAttribute(ECharacterStatType AttributeType, int32 Amount)
{
	switch (AttributeType)
	{
		case ECharacterStatType::Strength:
			Strength += Amount;
			BaseAttack += (Amount * 0.5f);
			break;
		case ECharacterStatType::Intelligence:
			Intelligence += Amount;
			BaseMagicPower += (Amount * 0.5f);
			break;
		case ECharacterStatType::Vitality:
			Vitality += Amount;
			MaxHealth += (Amount * 10.0f);
			Health = MaxHealth;
			break;
		case ECharacterStatType::Endurance:
			Endurance += Amount;
			MaxStamina += (Amount * 5.0f);
			Stamina = MaxStamina;
			break;
		case ECharacterStatType::Defense:
			BaseDefense += (Amount * 0.5f);
			break;
		case ECharacterStatType::Dexterity:
			Agility += Amount;
			AttackSpeed += (Amount * 0.05f);
			break;
		default:
			break;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s increased attribute by %d"), *CharacterName, Amount);
}

int32 APlayerCharacter::GetTotalAttack() const
{
	return BaseAttack + (Strength / 2);
}

int32 APlayerCharacter::GetTotalDefense() const
{
	return BaseDefense + (Vitality / 2);
}

int32 APlayerCharacter::GetTotalMagicPower() const
{
	return BaseMagicPower + (Intelligence / 2);
}

void APlayerCharacter::EnterCombat()
{
	bIsInCombat = true;
	if (CombatSystem)
	{
		CombatSystem->StartCombat();
	}
}

void APlayerCharacter::ExitCombat()
{
	bIsInCombat = false;
	if (CombatSystem)
	{
		CombatSystem->EndCombat();
	}
}

void APlayerCharacter::DisplayStats()
{
	FString StatsInfo = FString::Printf(
		TEXT("=== %s ===\n")
		TEXT("Race: %s | Class: %s\n")
		TEXT("Level: %d | XP: %d/%d\n")
		TEXT("HP: %.0f/%.0f | MP: %.0f/%.0f | Stamina: %.0f/%.0f\n")
		TEXT("STR: %d | AGI: %d | INT: %d | VIT: %d | END: %d\n")
		TEXT("ATK: %.0f | DEF: %.0f | MAGIC: %.0f | CRIT: %.0f%%\n")
		TEXT("Gold: %d | Skill Points: %d"),
		*CharacterName, *Race, *Class,
		CharacterLevel, Experience, ExperienceToNextLevel,
		Health, MaxHealth, Mana, MaxMana, Stamina, MaxStamina,
		Strength, Agility, Intelligence, Vitality, Endurance,
		GetTotalAttack(), GetTotalDefense(), GetTotalMagicPower(), CriticalChance,
		Gold, SkillPoints
	);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *StatsInfo);
}

FString APlayerCharacter::GetFullDescription() const
{
	return FString::Printf(TEXT("%s the %s %s"), *CharacterName, *Race, *Class);
}

void APlayerCharacter::ResetCharacter()
{
	Health = MaxHealth;
	Mana = MaxMana;
	Stamina = MaxStamina;
	CharacterLevel = 1;
	Experience = 0;
	SkillPoints = 0;
	bIsInCombat = false;

	UE_LOG(LogTemp, Warning, TEXT("%s has been reset"), *CharacterName);
}

void APlayerCharacter::UpdateResourceBars()
{
	// Update combat system if exists
	if (CombatSystem)
	{
		CombatSystem->CurrentHealth = Health;
		CombatSystem->CurrentMana = Mana;
		CombatSystem->CurrentStamina = Stamina;
	}
}

void APlayerCharacter::CheckDeath()
{
	if (!bIsAlive && IsAlive())
	{
		bIsAlive = true;
	}
	else if (bIsAlive && !IsAlive())
	{
		bIsAlive = false;
		ExitCombat();
		UE_LOG(LogTemp, Error, TEXT("%s has been defeated!"), *CharacterName);
	}
}

void APlayerCharacter::NotifyHealthChanged()
{
	OnHealthChanged.Broadcast(Health, MaxHealth);
}

void APlayerCharacter::NotifyManaChanged()
{
	OnManaChanged.Broadcast(Mana, MaxMana);
}
