#include "Character/EnemyCharacter.h"

// Static member initialization
TArray<FEnemyTemplate> AEnemyCharacter::EnemyDatabase;
bool AEnemyCharacter::bEnemyDatabaseInitialized = false;

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate with camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxAcceleration = 2048.0f;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Initialize enemy database on first use
	if (!bEnemyDatabaseInitialized)
	{
		InitializeEnemyDatabase();
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsAlive())
	{
		return;
	}

	RegenerateMana(DeltaTime);
	UpdateAbilityCooldowns(DeltaTime);
	UpdateCasting(DeltaTime);
}

void AEnemyCharacter::InitializeFromTemplate(const FEnemyTemplate& Template)
{
	EnemyTemplate = Template;
	CurrentHealth = EnemyTemplate.Health;
	CurrentMana = EnemyTemplate.Mana;

	// Set character name
	SetActorLabel(EnemyTemplate.Name);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f + (EnemyTemplate.Level * 10.0f);
}

void AEnemyCharacter::InitializeFromId(int32 EnemyTemplateId)
{
	FEnemyTemplate Template = GetTemplateById(EnemyTemplateId);
	if (Template.TemplateId > 0)
	{
		InitializeFromTemplate(Template);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy template with ID %d not found"), EnemyTemplateId);
	}
}

int32 AEnemyCharacter::TakeDamage(int32 BaseDamage, const FString& DamageType)
{
	if (!IsAlive())
	{
		return 0;
	}

	// Apply resistance and weakness modifiers
	int32 AdjustedDamage = ApplyDamageTypeModifiers(BaseDamage, DamageType);

	// Apply defense reduction (defense reduces damage by a percentage)
	float DefenseReduction = (EnemyTemplate.Defense / 100.0f) * 0.5f;
	DefenseReduction = FMath::Clamp(DefenseReduction, 0.0f, 0.8f); // Cap at 80% damage reduction
	int32 FinalDamage = FMath::Max(1, FMath::RoundToInt(AdjustedDamage * (1.0f - DefenseReduction)));

	CurrentHealth -= FinalDamage;
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}

	OnDamaged.Broadcast(this, FinalDamage, DamageType);

	if (!IsAlive())
	{
		OnDeath.Broadcast(this);
	}

	return FinalDamage;
}

void AEnemyCharacter::Heal(int32 Amount)
{
	CurrentHealth = FMath::Min(EnemyTemplate.Health, CurrentHealth + Amount);
}

void AEnemyCharacter::CastAbility(int32 AbilityIndex)
{
	if (!CanCastAbility(AbilityIndex))
	{
		return;
	}

	if (AbilityIndex < 0 || AbilityIndex >= EnemyTemplate.Abilities.Num())
	{
		return;
	}

	const FEnemyAbility& Ability = EnemyTemplate.Abilities[AbilityIndex];

	// Start casting
	CurrentCastingAbility = AbilityIndex;
	CurrentCastTime = Ability.CastTime;

	OnAbilityCast.Broadcast(this, Ability.Name);
}

bool AEnemyCharacter::CanCastAbility(int32 AbilityIndex) const
{
	if (!IsAlive() || CurrentCastingAbility != -1)
	{
		return false;
	}

	if (AbilityIndex < 0 || AbilityIndex >= EnemyTemplate.Abilities.Num())
	{
		return false;
	}

	const FEnemyAbility& Ability = EnemyTemplate.Abilities[AbilityIndex];

	// Check mana
	if (CurrentMana < Ability.ManaCost)
	{
		return false;
	}

	// Check cooldown
	if (AbilityCooldowns.Contains(AbilityIndex))
	{
		float RemainingCooldown = AbilityCooldowns[AbilityIndex];
		if (RemainingCooldown > 0.0f)
		{
			return false;
		}
	}

	return true;
}

void AEnemyCharacter::Aggro(AActor* Target)
{
	if (!IsAlive())
	{
		return;
	}

	AggroTarget = Target;
	OnAggro.Broadcast(this, Target);
}

void AEnemyCharacter::ClearAggro()
{
	AggroTarget = nullptr;
}

bool AEnemyCharacter::IsAggroed() const
{
	return AggroTarget != nullptr;
}

TArray<FLootItem> AEnemyCharacter::GenerateLoot()
{
	TArray<FLootItem> GeneratedLoot;

	if (EnemyTemplate.LootTable.Num() == 0)
	{
		return GeneratedLoot;
	}

	float Roll = FMath::FRand();
	if (Roll < EnemyTemplate.DropRate)
	{
		for (const FLootItem& LootItem : EnemyTemplate.LootTable)
		{
			float ItemRoll = FMath::FRand();
			if (ItemRoll < LootItem.DropChance)
			{
				GeneratedLoot.Add(LootItem);
			}
		}
	}

	return GeneratedLoot;
}

void AEnemyCharacter::AddBuff(const FString& BuffName, float Duration)
{
	if (!ActiveBuffs.Contains(BuffName))
	{
		ActiveBuffs.Add(BuffName);
	}
}

void AEnemyCharacter::AddDebuff(const FString& DebuffName, float Duration)
{
	if (!ActiveDebuffs.Contains(DebuffName))
	{
		ActiveDebuffs.Add(DebuffName);
	}
}

void AEnemyCharacter::RemoveBuff(const FString& BuffName)
{
	ActiveBuffs.Remove(BuffName);
}

void AEnemyCharacter::RemoveDebuff(const FString& DebuffName)
{
	ActiveDebuffs.Remove(DebuffName);
}

float AEnemyCharacter::GetHealthPercentage() const
{
	if (EnemyTemplate.Health <= 0)
	{
		return 0.0f;
	}
	return static_cast<float>(CurrentHealth) / static_cast<float>(EnemyTemplate.Health);
}

int32 AEnemyCharacter::GetAttackPower() const
{
	return EnemyTemplate.Attack;
}

bool AEnemyCharacter::HasWeakness(const FString& DamageType) const
{
	return EnemyTemplate.Weaknesses.Contains(DamageType);
}

bool AEnemyCharacter::HasResistance(const FString& DamageType) const
{
	return EnemyTemplate.Resistances.Contains(DamageType);
}

FEnemyTemplate AEnemyCharacter::GetTemplateById(int32 TemplateId)
{
	if (!bEnemyDatabaseInitialized)
	{
		const_cast<AEnemyCharacter*>(GetDefault<AEnemyCharacter>())->InitializeEnemyDatabase();
	}

	for (const FEnemyTemplate& Template : EnemyDatabase)
	{
		if (Template.TemplateId == TemplateId)
		{
			return Template;
		}
	}

	return FEnemyTemplate(); // Return empty template if not found
}

TArray<FEnemyTemplate> AEnemyCharacter::GetAllEnemyTemplates()
{
	if (!bEnemyDatabaseInitialized)
	{
		const_cast<AEnemyCharacter*>(GetDefault<AEnemyCharacter>())->InitializeEnemyDatabase();
	}

	return EnemyDatabase;
}

TArray<FEnemyTemplate> AEnemyCharacter::GetEnemiesByType(EEnemyType Type)
{
	TArray<FEnemyTemplate> Result;

	for (const FEnemyTemplate& Template : GetAllEnemyTemplates())
	{
		if (Template.Type == Type)
		{
			Result.Add(Template);
		}
	}

	return Result;
}

TArray<FEnemyTemplate> AEnemyCharacter::GetEnemiesByLevel(int32 MinLevel, int32 MaxLevel)
{
	TArray<FEnemyTemplate> Result;

	for (const FEnemyTemplate& Template : GetAllEnemyTemplates())
	{
		if (Template.Level >= MinLevel && Template.Level <= MaxLevel)
		{
			Result.Add(Template);
		}
	}

	return Result;
}

void AEnemyCharacter::RegenerateMana(float DeltaTime)
{
	if (!IsAlive() || EnemyTemplate.Mana <= 0)
	{
		return;
	}

	ManaRegenTimer += DeltaTime;

	if (ManaRegenTimer >= ManaRegenTickRate)
	{
		CurrentMana = FMath::Min(EnemyTemplate.Mana, CurrentMana + FMath::RoundToInt(ManaRegenRate));
		ManaRegenTimer = 0.0f;
	}
}

void AEnemyCharacter::UpdateAbilityCooldowns(float DeltaTime)
{
	for (auto& CooldownPair : AbilityCooldowns)
	{
		CooldownPair.Value -= DeltaTime;
	}
}

void AEnemyCharacter::UpdateCasting(float DeltaTime)
{
	if (CurrentCastingAbility == -1)
	{
		return;
	}

	CurrentCastTime -= DeltaTime;

	if (CurrentCastTime <= 0.0f)
	{
		const FEnemyAbility& Ability = EnemyTemplate.Abilities[CurrentCastingAbility];

		// Consume mana
		CurrentMana -= Ability.ManaCost;

		// Set cooldown
		AbilityCooldowns.Add(CurrentCastingAbility, Ability.CooldownTime);

		// Clear casting state
		CurrentCastingAbility = -1;
		CurrentCastTime = 0.0f;
	}
}

int32 AEnemyCharacter::ApplyDamageTypeModifiers(int32 Damage, const FString& DamageType) const
{
	int32 FinalDamage = Damage;

	// Apply resistance (reduces damage)
	if (HasResistance(DamageType))
	{
		FinalDamage = FMath::RoundToInt(Damage * 0.5f);
	}

	// Apply weakness (increases damage)
	if (HasWeakness(DamageType))
	{
		FinalDamage = FMath::RoundToInt(Damage * 1.5f);
	}

	return FinalDamage;
}

void AEnemyCharacter::InitializeEnemyDatabase()
{
	if (bEnemyDatabaseInitialized)
	{
		return;
	}

	// Beasts
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 1, .Name = TEXT("Wolf"), .Type = EEnemyType::Beast, .Rank = EEnemyRank::Normal,
		.Level = 5, .Health = 100, .Attack = 12, .Defense = 3, .XPReward = 50, .GoldReward = 5,
		.Abilities = { FEnemyAbility{.Name = TEXT("Bite"), .BaseDamage = 15}, FEnemyAbility{.Name = TEXT("Howl")} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 2, .Name = TEXT("Bear"), .Type = EEnemyType::Beast, .Rank = EEnemyRank::Normal,
		.Level = 8, .Health = 200, .Attack = 18, .Defense = 5, .XPReward = 80, .GoldReward = 10,
		.Abilities = { FEnemyAbility{.Name = TEXT("Maul"), .BaseDamage = 25}, FEnemyAbility{.Name = TEXT("Swipe"), .BaseDamage = 20} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 3, .Name = TEXT("Raptor"), .Type = EEnemyType::Beast, .Rank = EEnemyRank::Normal,
		.Level = 15, .Health = 250, .Attack = 25, .Defense = 7, .XPReward = 120, .GoldReward = 15,
		.Abilities = { FEnemyAbility{.Name = TEXT("Rend"), .BaseDamage = 30}, FEnemyAbility{.Name = TEXT("Pounce"), .BaseDamage = 28} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 4, .Name = TEXT("Elder Bear"), .Type = EEnemyType::Beast, .Rank = EEnemyRank::Elite,
		.Level = 20, .Health = 800, .Attack = 40, .Defense = 15, .XPReward = 500, .GoldReward = 50,
		.Abilities = { FEnemyAbility{.Name = TEXT("Crushing Blow"), .BaseDamage = 60}, FEnemyAbility{.Name = TEXT("Roar")}, FEnemyAbility{.Name = TEXT("Enrage")} }
	});

	// Humanoids
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 5, .Name = TEXT("Bandit"), .Type = EEnemyType::Humanoid, .Rank = EEnemyRank::Normal,
		.Level = 10, .Health = 180, .Attack = 20, .Defense = 5, .XPReward = 100, .GoldReward = 25,
		.Abilities = { FEnemyAbility{.Name = TEXT("Backstab"), .BaseDamage = 35}, FEnemyAbility{.Name = TEXT("Throw Dagger"), .BaseDamage = 15} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 6, .Name = TEXT("Orc Warrior"), .Type = EEnemyType::Humanoid, .Rank = EEnemyRank::Normal,
		.Level = 25, .Health = 500, .Attack = 45, .Defense = 20, .XPReward = 250, .GoldReward = 40,
		.Abilities = { FEnemyAbility{.Name = TEXT("Cleave"), .BaseDamage = 55}, FEnemyAbility{.Name = TEXT("Shield Bash"), .BaseDamage = 30} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 7, .Name = TEXT("Dark Mage"), .Type = EEnemyType::Humanoid, .Rank = EEnemyRank::Elite,
		.Level = 35, .Health = 800, .Mana = 1000, .Attack = 30, .MagicPower = 60, .Defense = 15, .XPReward = 600, .GoldReward = 75,
		.Abilities = { FEnemyAbility{.Name = TEXT("Fireball"), .BaseDamage = 50, .ManaCost = 100}, FEnemyAbility{.Name = TEXT("Frost Nova"), .BaseDamage = 40, .ManaCost = 80}, FEnemyAbility{.Name = TEXT("Blink")} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 8, .Name = TEXT("Bandit Lord"), .Type = EEnemyType::Humanoid, .Rank = EEnemyRank::RareElite,
		.Level = 40, .Health = 2000, .Attack = 80, .Defense = 30, .XPReward = 1500, .GoldReward = 200,
		.Abilities = { FEnemyAbility{.Name = TEXT("Dual Strike"), .BaseDamage = 85}, FEnemyAbility{.Name = TEXT("Poison Blade"), .BaseDamage = 45}, FEnemyAbility{.Name = TEXT("Shadow Step")} }
	});

	// Undead
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 9, .Name = TEXT("Zombie"), .Type = EEnemyType::Undead, .Rank = EEnemyRank::Normal,
		.Level = 12, .Health = 200, .Attack = 15, .Defense = 3, .XPReward = 90, .GoldReward = 8,
		.Abilities = { FEnemyAbility{.Name = TEXT("Infectious Bite"), .BaseDamage = 18} },
		.Weaknesses = { TEXT("Holy") }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 10, .Name = TEXT("Skeleton Warrior"), .Type = EEnemyType::Undead, .Rank = EEnemyRank::Normal,
		.Level = 18, .Health = 300, .Attack = 28, .Defense = 10, .XPReward = 150, .GoldReward = 20,
		.Abilities = { FEnemyAbility{.Name = TEXT("Bone Strike"), .BaseDamage = 32}, FEnemyAbility{.Name = TEXT("Shield Wall")} },
		.Weaknesses = { TEXT("Holy"), TEXT("Blunt") }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 11, .Name = TEXT("Lich"), .Type = EEnemyType::Undead, .Rank = EEnemyRank::Elite,
		.Level = 50, .Health = 3000, .Mana = 2000, .MagicPower = 90, .Defense = 25, .XPReward = 2000, .GoldReward = 300,
		.Abilities = { FEnemyAbility{.Name = TEXT("Death Coil"), .BaseDamage = 70, .ManaCost = 150}, FEnemyAbility{.Name = TEXT("Frost Nova"), .BaseDamage = 60, .ManaCost = 120}, FEnemyAbility{.Name = TEXT("Raise Dead"), .ManaCost = 200}, FEnemyAbility{.Name = TEXT("Phylactery")} },
		.Weaknesses = { TEXT("Holy") }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 12, .Name = TEXT("Vampire Lord"), .Type = EEnemyType::Undead, .Rank = EEnemyRank::Boss,
		.Level = 60, .Health = 10000, .Attack = 150, .Defense = 50, .XPReward = 5000, .GoldReward = 1000,
		.Abilities = { FEnemyAbility{.Name = TEXT("Life Drain"), .BaseDamage = 80}, FEnemyAbility{.Name = TEXT("Blood Frenzy"), .BaseDamage = 100}, FEnemyAbility{.Name = TEXT("Bat Form")}, FEnemyAbility{.Name = TEXT("Hypnotize")} },
		.Weaknesses = { TEXT("Holy"), TEXT("Fire") }
	});

	// Demons
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 13, .Name = TEXT("Imp"), .Type = EEnemyType::Demon, .Rank = EEnemyRank::Normal,
		.Level = 20, .Health = 250, .Mana = 300, .MagicPower = 35, .Defense = 5, .XPReward = 180, .GoldReward = 30,
		.Abilities = { FEnemyAbility{.Name = TEXT("Firebolt"), .BaseDamage = 25, .ManaCost = 50}, FEnemyAbility{.Name = TEXT("Phase Shift")} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 14, .Name = TEXT("Felguard"), .Type = EEnemyType::Demon, .Rank = EEnemyRank::Elite,
		.Level = 45, .Health = 2500, .Attack = 85, .Defense = 35, .XPReward = 1800, .GoldReward = 250,
		.Abilities = { FEnemyAbility{.Name = TEXT("Fel Cleave"), .BaseDamage = 95}, FEnemyAbility{.Name = TEXT("Demonic Charge"), .BaseDamage = 80}, FEnemyAbility{.Name = TEXT("Intimidate")} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 15, .Name = TEXT("Pit Lord"), .Type = EEnemyType::Demon, .Rank = EEnemyRank::RareElite,
		.Level = 55, .Health = 8000, .Attack = 120, .Defense = 40, .XPReward = 4000, .GoldReward = 800,
		.Abilities = { FEnemyAbility{.Name = TEXT("Doom"), .BaseDamage = 150}, FEnemyAbility{.Name = TEXT("Rain of Fire"), .BaseDamage = 120}, FEnemyAbility{.Name = TEXT("Howl of Terror")} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 16, .Name = TEXT("Demon Lord Kazzak"), .Type = EEnemyType::Demon, .Rank = EEnemyRank::WorldBoss,
		.Level = 70, .Health = 50000, .Attack = 250, .MagicPower = 150, .Defense = 100, .XPReward = 20000, .GoldReward = 5000,
		.Abilities = { FEnemyAbility{.Name = TEXT("Shadow Bolt Volley"), .BaseDamage = 200}, FEnemyAbility{.Name = TEXT("Mark of Kazzak"), .BaseDamage = 100}, FEnemyAbility{.Name = TEXT("Twisted Reflection"), .BaseDamage = 150}, FEnemyAbility{.Name = TEXT("Capture Soul")} },
		.Description = TEXT("The most powerful demon lord")
	});

	// Elementals
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 17, .Name = TEXT("Fire Elemental"), .Type = EEnemyType::Elemental, .Rank = EEnemyRank::Normal,
		.Level = 30, .Health = 600, .MagicPower = 50, .Defense = 10, .XPReward = 350, .GoldReward = 45,
		.Abilities = { FEnemyAbility{.Name = TEXT("Flame Burst"), .BaseDamage = 55}, FEnemyAbility{.Name = TEXT("Immolate"), .BaseDamage = 45} },
		.Resistances = { TEXT("Fire") }, .Weaknesses = { TEXT("Water"), TEXT("Frost") }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 18, .Name = TEXT("Water Elemental"), .Type = EEnemyType::Elemental, .Rank = EEnemyRank::Normal,
		.Level = 30, .Health = 600, .MagicPower = 50, .Defense = 10, .XPReward = 350, .GoldReward = 45,
		.Abilities = { FEnemyAbility{.Name = TEXT("Water Bolt"), .BaseDamage = 50}, FEnemyAbility{.Name = TEXT("Freeze"), .BaseDamage = 48} },
		.Resistances = { TEXT("Frost"), TEXT("Water") }, .Weaknesses = { TEXT("Lightning") }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 19, .Name = TEXT("Storm Elemental"), .Type = EEnemyType::Elemental, .Rank = EEnemyRank::Elite,
		.Level = 50, .Health = 3500, .MagicPower = 100, .Defense = 30, .XPReward = 2200, .GoldReward = 350,
		.Abilities = { FEnemyAbility{.Name = TEXT("Chain Lightning"), .BaseDamage = 90}, FEnemyAbility{.Name = TEXT("Thunderstorm"), .BaseDamage = 110}, FEnemyAbility{.Name = TEXT("Static Charge"), .BaseDamage = 70} },
		.Resistances = { TEXT("Lightning") }
	});

	// Dragons
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 20, .Name = TEXT("Whelp"), .Type = EEnemyType::Dragonkin, .Rank = EEnemyRank::Normal,
		.Level = 35, .Health = 800, .Attack = 55, .Defense = 20, .XPReward = 500, .GoldReward = 60,
		.Abilities = { FEnemyAbility{.Name = TEXT("Flame Breath"), .BaseDamage = 70}, FEnemyAbility{.Name = TEXT("Wing Buffet"), .BaseDamage = 50} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 21, .Name = TEXT("Drake"), .Type = EEnemyType::Dragonkin, .Rank = EEnemyRank::Elite,
		.Level = 50, .Health = 4000, .Attack = 100, .MagicPower = 70, .Defense = 50, .XPReward = 2500, .GoldReward = 400,
		.Abilities = { FEnemyAbility{.Name = TEXT("Dragon Breath"), .BaseDamage = 120}, FEnemyAbility{.Name = TEXT("Tail Swipe"), .BaseDamage = 90}, FEnemyAbility{.Name = TEXT("Fly")} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 22, .Name = TEXT("Ancient Dragon"), .Type = EEnemyType::Dragonkin, .Rank = EEnemyRank::Boss,
		.Level = 65, .Health = 15000, .Attack = 180, .MagicPower = 120, .Defense = 80, .XPReward = 8000, .GoldReward = 2000,
		.Abilities = { FEnemyAbility{.Name = TEXT("Inferno Breath"), .BaseDamage = 180}, FEnemyAbility{.Name = TEXT("Wing Storm"), .BaseDamage = 140}, FEnemyAbility{.Name = TEXT("Dragon Fear")}, FEnemyAbility{.Name = TEXT("Ancient Fury"), .BaseDamage = 200} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 23, .Name = TEXT("Onyxia"), .Type = EEnemyType::Dragonkin, .Rank = EEnemyRank::RaidBoss,
		.Level = 60, .Health = 100000, .Attack = 200, .MagicPower = 150, .Defense = 100, .XPReward = 50000, .GoldReward = 10000,
		.Abilities = { FEnemyAbility{.Name = TEXT("Deep Breath"), .BaseDamage = 250}, FEnemyAbility{.Name = TEXT("Tail Sweep"), .BaseDamage = 180}, FEnemyAbility{.Name = TEXT("Fear")}, FEnemyAbility{.Name = TEXT("Fireball"), .BaseDamage = 150}, FEnemyAbility{.Name = TEXT("Phase Shift")} },
		.Description = TEXT("A massive black dragon")
	});

	// Giants
	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 24, .Name = TEXT("Hill Giant"), .Type = EEnemyType::Giant, .Rank = EEnemyRank::Elite,
		.Level = 40, .Health = 3000, .Attack = 90, .Defense = 25, .XPReward = 1500, .GoldReward = 200,
		.Abilities = { FEnemyAbility{.Name = TEXT("Boulder Throw"), .BaseDamage = 100}, FEnemyAbility{.Name = TEXT("Ground Slam"), .BaseDamage = 110} }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 25, .Name = TEXT("Frost Giant"), .Type = EEnemyType::Giant, .Rank = EEnemyRank::Elite,
		.Level = 55, .Health = 6000, .Attack = 120, .Defense = 40, .XPReward = 3500, .GoldReward = 600,
		.Abilities = { FEnemyAbility{.Name = TEXT("Ice Boulder"), .BaseDamage = 130}, FEnemyAbility{.Name = TEXT("Frost Aura")}, FEnemyAbility{.Name = TEXT("Stomp"), .BaseDamage = 140} },
		.Resistances = { TEXT("Frost") }
	});

	EnemyDatabase.Add(FEnemyTemplate{
		.TemplateId = 26, .Name = TEXT("Fire Giant King"), .Type = EEnemyType::Giant, .Rank = EEnemyRank::Boss,
		.Level = 65, .Health = 20000, .Attack = 180, .Defense = 60, .XPReward = 10000, .GoldReward = 3000,
		.Abilities = { FEnemyAbility{.Name = TEXT("Molten Strike"), .BaseDamage = 190}, FEnemyAbility{.Name = TEXT("Inferno"), .BaseDamage = 170}, FEnemyAbility{.Name = TEXT("Volcanic Eruption"), .BaseDamage = 220}, FEnemyAbility{.Name = TEXT("Flame Shield")} },
		.Resistances = { TEXT("Fire") }
	});

	bEnemyDatabaseInitialized = true;
}
