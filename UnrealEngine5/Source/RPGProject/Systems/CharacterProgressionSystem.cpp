#include "CharacterProgressionSystem.h"
#include "Math/UnrealMathUtility.h"

UCharacterProgressionSystem::UCharacterProgressionSystem()
{
	CurrentLevel = 1;
	CurrentExperience = 0;
	MaxLevel = 100;
	AvailableSkillPoints = 0;
	CalculateExperienceRequirement();
}

void UCharacterProgressionSystem::GainExperience(int32 ExperienceAmount)
{
	if (CurrentLevel >= MaxLevel)
	{
		return;
	}

	CurrentExperience += ExperienceAmount;
	OnExperienceGained.Broadcast(ExperienceAmount, CurrentExperience);

	// Check for level up
	while (CurrentExperience >= ExperienceToNextLevel && CurrentLevel < MaxLevel)
	{
		CurrentExperience -= ExperienceToNextLevel;
		LevelUp();
	}
}

void UCharacterProgressionSystem::LevelUp()
{
	if (CurrentLevel >= MaxLevel)
	{
		return;
	}

	CurrentLevel++;
	AvailableSkillPoints += 5;

	// Increase base stats
	BaseStats.Health += 10.0f;
	BaseStats.Mana += 5.0f;
	BaseStats.Stamina += 10.0f;
	BaseStats.PhysicalDamage += 2.0f;
	BaseStats.MagicalDamage += 1.5f;
	BaseStats.Defense += 1.0f;
	BaseStats.MagicalResistance += 0.5f;

	CalculateExperienceRequirement();
	OnLevelUp.Broadcast(CurrentLevel, 5);
}

void UCharacterProgressionSystem::IncreaseStatByPoints(ECharacterStatType StatType, int32 Points)
{
	if (AvailableSkillPoints < Points)
	{
		return;
	}

	AvailableSkillPoints -= Points;

	switch (StatType)
	{
		case ECharacterStatType::Strength:
			BonusStats.PhysicalDamage += Points * 0.5f;
			break;
		case ECharacterStatType::Intelligence:
			BonusStats.MagicalDamage += Points * 0.5f;
			break;
		case ECharacterStatType::Vitality:
			BonusStats.Health += Points * 10.0f;
			break;
		case ECharacterStatType::Endurance:
			BonusStats.Stamina += Points * 5.0f;
			break;
		case ECharacterStatType::Defense:
			BonusStats.Defense += Points * 0.5f;
			break;
		case ECharacterStatType::Dexterity:
			BonusStats.AttackSpeed += Points * 0.05f;
			break;
		default:
			break;
	}

	OnStatIncrease.Broadcast(GetTotalStats());
}

void UCharacterProgressionSystem::LearnSkill(const FSkillData& NewSkill)
{
	// Check if skill already learned
	if (FindSkill(NewSkill.SkillName))
	{
		return;
	}

	LearnedSkills.Add(NewSkill);
}

void UCharacterProgressionSystem::UpgradeSkill(const FString& SkillName)
{
	FSkillData* Skill = FindSkill(SkillName);
	if (!Skill)
	{
		return;
	}

	if (Skill->SkillLevel < Skill->MaxSkillLevel)
	{
		Skill->SkillLevel++;
		Skill->ManaCost *= 0.95f; // Slightly cheaper as you level
		Skill->Cooldown *= 0.9f;  // Slightly faster cooldown
	}
}

FCharacterStats UCharacterProgressionSystem::GetTotalStats() const
{
	FCharacterStats TotalStats = BaseStats;
	TotalStats.Health += BonusStats.Health;
	TotalStats.Mana += BonusStats.Mana;
	TotalStats.Stamina += BonusStats.Stamina;
	TotalStats.PhysicalDamage += BonusStats.PhysicalDamage;
	TotalStats.MagicalDamage += BonusStats.MagicalDamage;
	TotalStats.Defense += BonusStats.Defense;
	TotalStats.MagicalResistance += BonusStats.MagicalResistance;
	TotalStats.AttackSpeed += BonusStats.AttackSpeed;
	return TotalStats;
}

float UCharacterProgressionSystem::GetExperiencePercentage() const
{
	if (ExperienceToNextLevel <= 0)
	{
		return 1.0f;
	}

	return static_cast<float>(CurrentExperience) / static_cast<float>(ExperienceToNextLevel);
}

FSkillData* UCharacterProgressionSystem::FindSkill(const FString& SkillName)
{
	for (FSkillData& Skill : LearnedSkills)
	{
		if (Skill.SkillName == SkillName)
		{
			return &Skill;
		}
	}
	return nullptr;
}

void UCharacterProgressionSystem::CalculateExperienceRequirement()
{
	// Exponential experience curve
	ExperienceToNextLevel = FMath::FloorToInt(1000.0f * FMath::Pow(1.1f, CurrentLevel));
}
