#include "Dungeon/DungeonSystem.h"

UDungeonSystem::UDungeonSystem()
{
	// Initialize
	CurrentRun.bIsActive = false;
}

void UDungeonSystem::InitializeDungeonDatabase()
{
	if (DungeonDatabase.Num() > 0)
	{
		return; // Already initialized
	}

	PopulateDungeonDatabase();
}

FDungeonTemplate UDungeonSystem::GetDungeonById(int32 DungeonId)
{
	if (DungeonDatabase.Num() == 0)
	{
		InitializeDungeonDatabase();
	}

	for (const FDungeonTemplate& Dungeon : DungeonDatabase)
	{
		if (Dungeon.DungeonId == DungeonId)
		{
			return Dungeon;
		}
	}

	return FDungeonTemplate();
}

TArray<FDungeonTemplate> UDungeonSystem::GetAllDungeons()
{
	if (DungeonDatabase.Num() == 0)
	{
		InitializeDungeonDatabase();
	}

	return DungeonDatabase;
}

TArray<FDungeonTemplate> UDungeonSystem::GetDungeonsByType(EDungeonType Type)
{
	TArray<FDungeonTemplate> Result;

	for (const FDungeonTemplate& Dungeon : GetAllDungeons())
	{
		if (Dungeon.Type == Type)
		{
			Result.Add(Dungeon);
		}
	}

	return Result;
}

TArray<FDungeonTemplate> UDungeonSystem::GetDungeonsByLevelRange(int32 MinLevel, int32 MaxLevel)
{
	TArray<FDungeonTemplate> Result;

	for (const FDungeonTemplate& Dungeon : GetAllDungeons())
	{
		if (Dungeon.MinLevel <= MaxLevel && Dungeon.MaxLevel >= MinLevel)
		{
			Result.Add(Dungeon);
		}
	}

	return Result;
}

bool UDungeonSystem::EnterDungeon(int32 DungeonId, EDungeonDifficulty Difficulty)
{
	if (CurrentRun.bIsActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already in a dungeon!"));
		return false;
	}

	FDungeonTemplate Template = GetDungeonById(DungeonId);
	if (Template.DungeonId == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dungeon with ID %d not found"), DungeonId);
		return false;
	}

	// Check if difficulty is available
	if (!Template.AvailableDifficulties.Contains(Difficulty))
	{
		UE_LOG(LogTemp, Warning, TEXT("Difficulty not available for this dungeon"));
		return false;
	}

	// Initialize the dungeon run
	CurrentRun.DungeonTemplate = Template;
	CurrentRun.Difficulty = Difficulty;
	CurrentRun.CurrentBossIndex = 0;
	CurrentRun.DeathCount = 0;
	CurrentRun.bIsCompleted = false;
	CurrentRun.bIsActive = true;
	CurrentRun.StartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	UE_LOG(LogTemp, Warning, TEXT("Entered dungeon: %s (Difficulty: %d)"), *Template.Name, (int32)Difficulty);

	return true;
}

void UDungeonSystem::ExitDungeon()
{
	if (CurrentRun.bIsActive)
	{
		CurrentRun.bIsActive = false;
		UE_LOG(LogTemp, Warning, TEXT("Exited dungeon"));
	}
}

bool UDungeonSystem::IsInDungeon() const
{
	return CurrentRun.bIsActive;
}

void UDungeonSystem::DefeatCurrentBoss(int32 RewardXP)
{
	if (!CurrentRun.bIsActive)
	{
		return;
	}

	if (CurrentRun.CurrentBossIndex >= CurrentRun.DungeonTemplate.Bosses.Num())
	{
		return;
	}

	FDungeonBoss CurrentBoss = CurrentRun.DungeonTemplate.Bosses[CurrentRun.CurrentBossIndex];

	OnBossDefeated.Broadcast(CurrentBoss.Name, RewardXP);

	CurrentRun.CurrentBossIndex++;

	if (CurrentRun.CurrentBossIndex >= CurrentRun.DungeonTemplate.Bosses.Num())
	{
		CompleteDungeon();
	}
}

void UDungeonSystem::OnPartyMemberDeath()
{
	if (!CurrentRun.bIsActive)
	{
		return;
	}

	CurrentRun.DeathCount++;
	OnPartyMemberDied.Broadcast(nullptr, CurrentRun.DeathCount);

	// Auto-fail if too many deaths
	if (CurrentRun.DeathCount >= 5)
	{
		FailDungeon(TEXT("Too many deaths"));
	}
}

void UDungeonSystem::CompleteDungeon()
{
	if (!CurrentRun.bIsActive)
	{
		return;
	}

	CurrentRun.bIsCompleted = true;
	CurrentRun.bIsActive = false;

	float ElapsedTime = GetElapsedTime();
	int32 TotalRewards = CurrentRun.DungeonTemplate.Bosses.Num() * 100; // Base reward

	CompletedDungeonCount++;
	CompletionTimes.Add(ElapsedTime);

	OnDungeonCompleted.Broadcast(CurrentRun.DungeonTemplate.Name, ElapsedTime, TotalRewards);

	UE_LOG(LogTemp, Warning, TEXT("Dungeon Completed: %s in %.1f seconds"), *CurrentRun.DungeonTemplate.Name, ElapsedTime);
}

void UDungeonSystem::FailDungeon(const FString& Reason)
{
	if (!CurrentRun.bIsActive)
	{
		return;
	}

	CurrentRun.bIsActive = false;
	FailedDungeonCount++;

	OnDungeonFailed.Broadcast(Reason);

	UE_LOG(LogTemp, Warning, TEXT("Dungeon Failed: %s - Reason: %s"), *CurrentRun.DungeonTemplate.Name, *Reason);
}

FDungeonBoss UDungeonSystem::GetCurrentBoss() const
{
	if (!CurrentRun.bIsActive || CurrentRun.CurrentBossIndex >= CurrentRun.DungeonTemplate.Bosses.Num())
	{
		return FDungeonBoss();
	}

	return CurrentRun.DungeonTemplate.Bosses[CurrentRun.CurrentBossIndex];
}

float UDungeonSystem::GetElapsedTime() const
{
	if (!CurrentRun.bIsActive)
	{
		return 0.0f;
	}

	return GetWorld() ? GetWorld()->GetTimeSeconds() - CurrentRun.StartTime : 0.0f;
}

int32 UDungeonSystem::GetRemainingBosses() const
{
	if (!CurrentRun.bIsActive)
	{
		return 0;
	}

	return CurrentRun.DungeonTemplate.Bosses.Num() - CurrentRun.CurrentBossIndex;
}

FString UDungeonSystem::GetDifficultyModifier(EDungeonDifficulty Difficulty) const
{
	switch (Difficulty)
	{
	case EDungeonDifficulty::Normal:
		return TEXT("1.0x");
	case EDungeonDifficulty::Heroic:
		return TEXT("2.0x");
	case EDungeonDifficulty::Mythic:
		return TEXT("4.0x");
	case EDungeonDifficulty::MythicPlus:
		return TEXT("6.0x+");
	default:
		return TEXT("Unknown");
	}
}

FString UDungeonSystem::GetDungeonDescription() const
{
	if (!CurrentRun.bIsActive)
	{
		return TEXT("Not in a dungeon");
	}

	FString Desc = FString::Printf(
		TEXT("=== %s ===\n"),
		*CurrentRun.DungeonTemplate.Name
	);

	Desc += FString::Printf(
		TEXT("Type: %d | Location: %s\n"),
		(int32)CurrentRun.DungeonTemplate.Type,
		*CurrentRun.DungeonTemplate.Location
	);

	Desc += FString::Printf(
		TEXT("Bosses: %d/%d | Deaths: %d\n"),
		CurrentRun.CurrentBossIndex,
		CurrentRun.DungeonTemplate.Bosses.Num(),
		CurrentRun.DeathCount
	);

	Desc += FString::Printf(
		TEXT("Elapsed Time: %.1f seconds\n"),
		GetElapsedTime()
	);

	return Desc;
}

float UDungeonSystem::GetAverageCompletionTime() const
{
	if (CompletionTimes.Num() == 0)
	{
		return 0.0f;
	}

	float Total = 0.0f;
	for (float Time : CompletionTimes)
	{
		Total += Time;
	}

	return Total / static_cast<float>(CompletionTimes.Num());
}

bool UDungeonSystem::CanEnterDungeon(int32 PlayerLevel, int32 PartySize) const
{
	if (CurrentRun.bIsActive)
	{
		return false; // Already in a dungeon
	}

	// Check level and party size against current dungeon (if there was one selected)
	// This would typically be called before EnterDungeon() to validate

	return true;
}

void UDungeonSystem::DisplayDungeonInfo(int32 DungeonId) const
{
	FDungeonTemplate Dungeon = GetDungeonById(DungeonId);

	if (Dungeon.DungeonId == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dungeon not found"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("=== %s ==="), *Dungeon.Name);
	UE_LOG(LogTemp, Warning, TEXT("Type: %d"), (int32)Dungeon.Type);
	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Dungeon.Location);
	UE_LOG(LogTemp, Warning, TEXT("Description: %s"), *Dungeon.Description);
	UE_LOG(LogTemp, Warning, TEXT("Level Range: %d - %d"), Dungeon.MinLevel, Dungeon.MaxLevel);
	UE_LOG(LogTemp, Warning, TEXT("Party Size: %d - %d"), Dungeon.MinPlayers, Dungeon.MaxPlayers);
	UE_LOG(LogTemp, Warning, TEXT("Estimated Time: %d minutes"), Dungeon.EstimatedTimeMinutes);
	UE_LOG(LogTemp, Warning, TEXT("Bosses: %d"), Dungeon.Bosses.Num());

	for (int32 i = 0; i < Dungeon.Bosses.Num(); ++i)
	{
		const FDungeonBoss& Boss = Dungeon.Bosses[i];
		FString RaidBossStr = Boss.bIsRaidBoss ? TEXT(" (RAID BOSS)") : TEXT("");
		UE_LOG(LogTemp, Warning, TEXT("  [%d] %s - Lvl %d%s"), i, *Boss.Name, Boss.Level, *RaidBossStr);
	}
}

void UDungeonSystem::PopulateDungeonDatabase()
{
	// The Deadmines
	FDungeonTemplate DeadminesTemplate;
	DeadminesTemplate.DungeonId = 1;
	DeadminesTemplate.Name = TEXT("The Deadmines");
	DeadminesTemplate.Type = EDungeonType::StandardDungeon;
	DeadminesTemplate.Description = TEXT("An abandoned mine taken over by the Defias Brotherhood");
	DeadminesTemplate.MinLevel = 15;
	DeadminesTemplate.MaxLevel = 21;
	DeadminesTemplate.MinPlayers = 5;
	DeadminesTemplate.MaxPlayers = 5;
	DeadminesTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal, EDungeonDifficulty::Heroic };
	DeadminesTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("Rhahk'Zor"), .Level = 17 },
		FDungeonBoss{ .Name = TEXT("Sneed"), .Level = 18 },
		FDungeonBoss{ .Name = TEXT("Gilnid"), .Level = 19 },
		FDungeonBoss{ .Name = TEXT("Mr. Smite"), .Level = 20 },
		FDungeonBoss{ .Name = TEXT("Edwin VanCleef"), .Level = 21, .bIsRaidBoss = true }
	};
	DeadminesTemplate.Rewards = { TEXT("Rare Weapons"), TEXT("Armor"), TEXT("Gold") };
	DeadminesTemplate.EstimatedTimeMinutes = 30;
	DeadminesTemplate.Location = TEXT("Westfall");
	DungeonDatabase.Add(DeadminesTemplate);

	// Wailing Caverns
	FDungeonTemplate WailingCavernsTemplate;
	WailingCavernsTemplate.DungeonId = 2;
	WailingCavernsTemplate.Name = TEXT("Wailing Caverns");
	WailingCavernsTemplate.Type = EDungeonType::StandardDungeon;
	WailingCavernsTemplate.Description = TEXT("A corrupted underground cavern");
	WailingCavernsTemplate.MinLevel = 15;
	WailingCavernsTemplate.MaxLevel = 25;
	WailingCavernsTemplate.MinPlayers = 5;
	WailingCavernsTemplate.MaxPlayers = 5;
	WailingCavernsTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal, EDungeonDifficulty::Heroic };
	WailingCavernsTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("Lady Anacondra"), .Level = 18 },
		FDungeonBoss{ .Name = TEXT("Lord Pythas"), .Level = 19 },
		FDungeonBoss{ .Name = TEXT("Lord Cobrahn"), .Level = 20 },
		FDungeonBoss{ .Name = TEXT("Mutanus the Devourer"), .Level = 22, .bIsRaidBoss = true }
	};
	WailingCavernsTemplate.Rewards = { TEXT("Druid Gear"), TEXT("Leather Armor") };
	WailingCavernsTemplate.EstimatedTimeMinutes = 45;
	WailingCavernsTemplate.Location = TEXT("The Barrens");
	DungeonDatabase.Add(WailingCavernsTemplate);

	// Scarlet Monastery
	FDungeonTemplate ScarletMonasteryTemplate;
	ScarletMonasteryTemplate.DungeonId = 3;
	ScarletMonasteryTemplate.Name = TEXT("Scarlet Monastery");
	ScarletMonasteryTemplate.Type = EDungeonType::StandardDungeon;
	ScarletMonasteryTemplate.Description = TEXT("A cathedral overtaken by zealous crusaders");
	ScarletMonasteryTemplate.MinLevel = 30;
	ScarletMonasteryTemplate.MaxLevel = 45;
	ScarletMonasteryTemplate.MinPlayers = 5;
	ScarletMonasteryTemplate.MaxPlayers = 5;
	ScarletMonasteryTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal, EDungeonDifficulty::Heroic };
	ScarletMonasteryTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("Interrogator Vishas"), .Level = 32 },
		FDungeonBoss{ .Name = TEXT("High Inquisitor Whitemane"), .Level = 34 },
		FDungeonBoss{ .Name = TEXT("Scarlet Commander Mograine"), .Level = 34 },
		FDungeonBoss{ .Name = TEXT("Herod"), .Level = 36, .bIsRaidBoss = true }
	};
	ScarletMonasteryTemplate.Rewards = { TEXT("Plate Armor"), TEXT("Rare Weapons"), TEXT("Tabards") };
	ScarletMonasteryTemplate.EstimatedTimeMinutes = 40;
	ScarletMonasteryTemplate.Location = TEXT("Tirisfal Glades");
	DungeonDatabase.Add(ScarletMonasteryTemplate);

	// Stratholme
	FDungeonTemplate StratholmeTemplate;
	StratholmeTemplate.DungeonId = 4;
	StratholmeTemplate.Name = TEXT("Stratholme");
	StratholmeTemplate.Type = EDungeonType::StandardDungeon;
	StratholmeTemplate.Description = TEXT("A city plagued by the undead scourge");
	StratholmeTemplate.MinLevel = 55;
	StratholmeTemplate.MaxLevel = 60;
	StratholmeTemplate.MinPlayers = 5;
	StratholmeTemplate.MaxPlayers = 5;
	StratholmeTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal, EDungeonDifficulty::Heroic };
	StratholmeTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("The Unforgiven"), .Level = 57 },
		FDungeonBoss{ .Name = TEXT("Baroness Anastari"), .Level = 58 },
		FDungeonBoss{ .Name = TEXT("Maleki the Pallid"), .Level = 58 },
		FDungeonBoss{ .Name = TEXT("Baron Rivendare"), .Level = 60, .bIsRaidBoss = true }
	};
	StratholmeTemplate.Rewards = { TEXT("Epic Mounts"), TEXT("Tier 0.5 Gear"), TEXT("Runecloth") };
	StratholmeTemplate.EstimatedTimeMinutes = 60;
	StratholmeTemplate.Location = TEXT("Eastern Plaguelands");
	DungeonDatabase.Add(StratholmeTemplate);

	// Molten Core (Raid)
	FDungeonTemplate MoltenCoreTemplate;
	MoltenCoreTemplate.DungeonId = 5;
	MoltenCoreTemplate.Name = TEXT("Molten Core");
	MoltenCoreTemplate.Type = EDungeonType::Raid;
	MoltenCoreTemplate.Description = TEXT("A volcanic lair beneath Blackrock Mountain");
	MoltenCoreTemplate.MinLevel = 60;
	MoltenCoreTemplate.MaxLevel = 60;
	MoltenCoreTemplate.MinPlayers = 20;
	MoltenCoreTemplate.MaxPlayers = 40;
	MoltenCoreTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal };
	MoltenCoreTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("Lucifron"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Magmadar"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Gehennas"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Garr"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Baron Geddon"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Shazzrah"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Sulfuron Harbinger"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Golemagg the Incinerator"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Majordomo Executus"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Ragnaros the Firelord"), .Level = 60, .bIsRaidBoss = true }
	};
	MoltenCoreTemplate.Rewards = { TEXT("Tier 1 Armor"), TEXT("Legendary Weapons"), TEXT("Sulfuras") };
	MoltenCoreTemplate.EstimatedTimeMinutes = 180;
	MoltenCoreTemplate.Location = TEXT("Blackrock Mountain");
	DungeonDatabase.Add(MoltenCoreTemplate);

	// Blackwing Lair
	FDungeonTemplate BlackwingLairTemplate;
	BlackwingLairTemplate.DungeonId = 6;
	BlackwingLairTemplate.Name = TEXT("Blackwing Lair");
	BlackwingLairTemplate.Type = EDungeonType::Raid;
	BlackwingLairTemplate.Description = TEXT("The lair of the black dragon Nefarian");
	BlackwingLairTemplate.MinLevel = 60;
	BlackwingLairTemplate.MaxLevel = 60;
	BlackwingLairTemplate.MinPlayers = 40;
	BlackwingLairTemplate.MaxPlayers = 40;
	BlackwingLairTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal };
	BlackwingLairTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("Razorgore the Untamed"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Vaelastrasz the Corrupt"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Broodlord Lashlayer"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Firemaw"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Ebonroc"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Flamegor"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Chromaggus"), .Level = 60 },
		FDungeonBoss{ .Name = TEXT("Nefarian"), .Level = 60, .bIsRaidBoss = true }
	};
	BlackwingLairTemplate.Rewards = { TEXT("Tier 2 Armor"), TEXT("Dragon Weapons"), TEXT("Legendary Materials") };
	BlackwingLairTemplate.EstimatedTimeMinutes = 240;
	BlackwingLairTemplate.Location = TEXT("Blackrock Mountain");
	DungeonDatabase.Add(BlackwingLairTemplate);

	// Trial of the Crusader
	FDungeonTemplate TrialTemplate;
	TrialTemplate.DungeonId = 7;
	TrialTemplate.Name = TEXT("Trial of the Crusader");
	TrialTemplate.Type = EDungeonType::Trial;
	TrialTemplate.Description = TEXT("Prove yourself in the Argent Tournament");
	TrialTemplate.MinLevel = 80;
	TrialTemplate.MaxLevel = 80;
	TrialTemplate.MinPlayers = 10;
	TrialTemplate.MaxPlayers = 25;
	TrialTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal, EDungeonDifficulty::Heroic };
	TrialTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("The Beasts of Northrend"), .Level = 80 },
		FDungeonBoss{ .Name = TEXT("Lord Jaraxxus"), .Level = 80 },
		FDungeonBoss{ .Name = TEXT("Faction Champions"), .Level = 80 },
		FDungeonBoss{ .Name = TEXT("The Twin Val'kyr"), .Level = 80 },
		FDungeonBoss{ .Name = TEXT("Anub'arak"), .Level = 80, .bIsRaidBoss = true }
	};
	TrialTemplate.Rewards = { TEXT("Tier 9 Armor"), TEXT("Tribute Chest Items") };
	TrialTemplate.EstimatedTimeMinutes = 90;
	TrialTemplate.Location = TEXT("Icecrown");
	DungeonDatabase.Add(TrialTemplate);

	// The Maw of Souls
	FDungeonTemplate MawTemplate;
	MawTemplate.DungeonId = 8;
	MawTemplate.Name = TEXT("The Maw of Souls");
	MawTemplate.Type = EDungeonType::Challenge;
	MawTemplate.Description = TEXT("Navigate the cursed ship through the afterlife");
	MawTemplate.MinLevel = 110;
	MawTemplate.MaxLevel = 110;
	MawTemplate.MinPlayers = 5;
	MawTemplate.MaxPlayers = 5;
	MawTemplate.AvailableDifficulties = { EDungeonDifficulty::Normal, EDungeonDifficulty::Heroic, EDungeonDifficulty::Mythic, EDungeonDifficulty::MythicPlus };
	MawTemplate.Bosses = {
		FDungeonBoss{ .Name = TEXT("Ymiron the Fallen King"), .Level = 110 },
		FDungeonBoss{ .Name = TEXT("Harbaron"), .Level = 110 },
		FDungeonBoss{ .Name = TEXT("Helya"), .Level = 110, .bIsRaidBoss = true }
	};
	MawTemplate.Rewards = { TEXT("Mythic+ Gear"), TEXT("Artifact Power") };
	MawTemplate.EstimatedTimeMinutes = 25;
	MawTemplate.Location = TEXT("Helheim");
	DungeonDatabase.Add(MawTemplate);
}
