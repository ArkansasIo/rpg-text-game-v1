#include "CombatSystem.h"
#include "Math/UnrealMathUtility.h"

UCombatSystem::UCombatSystem()
{
	bIsInCombat = false;
	CurrentHealth = 100.0f;
	CurrentMana = 50.0f;
	CurrentStamina = 100.0f;
}

void UCombatSystem::StartCombat()
{
	bIsInCombat = true;
	OnCombatStart.Broadcast();
}

void UCombatSystem::EndCombat()
{
	bIsInCombat = false;
	OnCombatEnd.Broadcast();
}

float UCombatSystem::CalculateDamage(ECharacterStatType DamageType)
{
	float BaseDamage = 0.0f;

	switch (DamageType)
	{
		case ECharacterStatType::Strength:
			BaseDamage = AttackerStats.PhysicalDamage;
			break;
		case ECharacterStatType::Intelligence:
			BaseDamage = AttackerStats.MagicalDamage;
			break;
		default:
			BaseDamage = AttackerStats.PhysicalDamage;
			break;
	}

	// Check for critical hit
	bCriticalHit = FMath::FRand() * 100.0f < CombatStats.CriticalChance;
	if (bCriticalHit)
	{
		BaseDamage *= CombatStats.CriticalMultiplier;
		OnCriticalHit.Broadcast(BaseDamage);
	}

	// Add variance (±10%)
	float Variance = FMath::FRand() * 0.2f - 0.1f; // -10% to +10%
	BaseDamage *= (1.0f + Variance);

	return FMath::Max(0.1f, BaseDamage); // Minimum 0.1 damage
}

float UCombatSystem::ApplyDefense(float IncomingDamage, ECharacterStatType DamageType)
{
	float FinalDamage = IncomingDamage;

	// Apply armor/defense
	float DefenseReduction = DefenderStats.Defense * 0.5f; // Each defense point blocks 0.5% damage
	FinalDamage *= (1.0f - (DefenseReduction / 100.0f));

	// Apply resistances
	if (DamageType == ECharacterStatType::Intelligence)
	{
		float MagicResistance = DefenderStats.MagicalResistance * 0.3f;
		FinalDamage *= (1.0f - (MagicResistance / 100.0f));
	}

	// Check for block
	if (AttemptBlock())
	{
		float BlockAmount = FinalDamage * 0.5f; // Block 50% of damage
		FinalDamage -= BlockAmount;
		OnDefend.Broadcast(BlockAmount);
	}

	return FMath::Max(0.1f, FinalDamage);
}

void UCombatSystem::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth < 0.0f)
	{
		CurrentHealth = 0.0f;
	}
}

void UCombatSystem::Heal(float HealAmount)
{
	CurrentHealth += HealAmount;
	if (CurrentHealth > AttackerStats.Health)
	{
		CurrentHealth = AttackerStats.Health;
	}
}

bool UCombatSystem::AttemptAbility(const FString& AbilityName, float ManaCost)
{
	if (CurrentMana >= ManaCost)
	{
		CurrentMana -= ManaCost;
		return true;
	}
	return false;
}

bool UCombatSystem::AttemptDodge()
{
	return FMath::FRand() * 100.0f < CombatStats.DodgeChance;
}

bool UCombatSystem::AttemptBlock()
{
	return FMath::FRand() * 100.0f < CombatStats.BlockChance;
}

bool UCombatSystem::IsAlive() const
{
	return CurrentHealth > 0.0f;
}

void UCombatSystem::RegenerateResources(float DeltaTime)
{
	// Health regeneration (slow)
	CurrentHealth += 1.0f * DeltaTime;
	if (CurrentHealth > AttackerStats.Health)
	{
		CurrentHealth = AttackerStats.Health;
	}

	// Mana regeneration (medium)
	CurrentMana += 3.0f * DeltaTime;
	if (CurrentMana > AttackerStats.Mana)
	{
		CurrentMana = AttackerStats.Mana;
	}

	// Stamina regeneration (fast)
	CurrentStamina += 5.0f * DeltaTime;
	if (CurrentStamina > AttackerStats.Stamina)
	{
		CurrentStamina = AttackerStats.Stamina;
	}
}
