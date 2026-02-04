#include "RPGGameSystemsManager.h"
#include "CharacterProgressionSystem.h"
#include "CombatSystem.h"
#include "InventorySystem.h"
#include "QuestSystem.h"
#include "StatusEffectSystem.h"

ARPGGameSystemsManager::ARPGGameSystemsManager()
{
	PrimaryActorTick.TickInterval = 0.016f; // ~60 FPS
	PrimaryActorTick.bCanEverTick = true;
}

void ARPGGameSystemsManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeAllSystems();
}

void ARPGGameSystemsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSystemsInitialized)
	{
		// Update systems every frame
		if (StatusEffectSystem)
		{
			StatusEffectSystem->UpdateEffects(DeltaTime);
		}

		if (CombatSystem)
		{
			CombatSystem->RegenerateResources(DeltaTime);
		}
	}
}

void ARPGGameSystemsManager::InitializeAllSystems()
{
	InitializeProgressionSystem();
	InitializeCombatSystem();
	InitializeInventorySystem();
	InitializeQuestSystem();
	InitializeStatusEffectSystem();

	bSystemsInitialized = true;

	UE_LOG(LogTemp, Warning, TEXT("All RPG Systems initialized successfully!"));
}

void ARPGGameSystemsManager::InitializeProgressionSystem()
{
	if (!ProgressionSystem)
	{
		ProgressionSystem = NewObject<UCharacterProgressionSystem>(this);
		ProgressionSystem->CurrentLevel = 1;
		ProgressionSystem->AvailableSkillPoints = 0;
		ProgressionSystem->MaxLevel = 100;

		UE_LOG(LogTemp, Warning, TEXT("Progression System initialized"));
	}
}

void ARPGGameSystemsManager::InitializeCombatSystem()
{
	if (!CombatSystem)
	{
		CombatSystem = NewObject<UCombatSystem>(this);
		CombatSystem->CurrentHealth = 100.0f;
		CombatSystem->CurrentMana = 50.0f;
		CombatSystem->CurrentStamina = 100.0f;

		UE_LOG(LogTemp, Warning, TEXT("Combat System initialized"));
	}
}

void ARPGGameSystemsManager::InitializeInventorySystem()
{
	if (!InventorySystem)
	{
		InventorySystem = NewObject<UInventorySystem>(this);
		InventorySystem->MaxInventoryWeight = 50.0f;
		InventorySystem->InventoryCapacity = 20;
		InventorySystem->Gold = 0;

		UE_LOG(LogTemp, Warning, TEXT("Inventory System initialized"));
	}
}

void ARPGGameSystemsManager::InitializeQuestSystem()
{
	if (!QuestSystem)
	{
		QuestSystem = NewObject<UQuestSystem>(this);
		QuestSystem->TotalQuestsCompleted = 0;

		UE_LOG(LogTemp, Warning, TEXT("Quest System initialized"));
	}
}

void ARPGGameSystemsManager::InitializeStatusEffectSystem()
{
	if (!StatusEffectSystem)
	{
		StatusEffectSystem = NewObject<UStatusEffectSystem>(this);

		UE_LOG(LogTemp, Warning, TEXT("Status Effect System initialized"));
	}
}

UCharacterProgressionSystem* ARPGGameSystemsManager::GetProgressionSystem() const
{
	return ProgressionSystem;
}

UCombatSystem* ARPGGameSystemsManager::GetCombatSystem() const
{
	return CombatSystem;
}

UInventorySystem* ARPGGameSystemsManager::GetInventorySystem() const
{
	return InventorySystem;
}

UQuestSystem* ARPGGameSystemsManager::GetQuestSystem() const
{
	return QuestSystem;
}

UStatusEffectSystem* ARPGGameSystemsManager::GetStatusEffectSystem() const
{
	return StatusEffectSystem;
}

void ARPGGameSystemsManager::SaveGameProgress()
{
	// TODO: Implement save system
	UE_LOG(LogTemp, Warning, TEXT("Game progress saved"));
}

void ARPGGameSystemsManager::LoadGameProgress()
{
	// TODO: Implement load system
	UE_LOG(LogTemp, Warning, TEXT("Game progress loaded"));
}

void ARPGGameSystemsManager::ResetAllSystems()
{
	if (ProgressionSystem)
	{
		ProgressionSystem->CurrentLevel = 1;
		ProgressionSystem->CurrentExperience = 0;
		ProgressionSystem->AvailableSkillPoints = 0;
	}

	if (CombatSystem)
	{
		CombatSystem->EndCombat();
		CombatSystem->CurrentHealth = 100.0f;
		CombatSystem->CurrentMana = 50.0f;
		CombatSystem->CurrentStamina = 100.0f;
	}

	if (InventorySystem)
	{
		InventorySystem->ClearInventory();
		InventorySystem->Gold = 0;
	}

	if (QuestSystem)
	{
		QuestSystem->ActiveQuests.Clear();
		QuestSystem->CompletedQuests.Clear();
	}

	if (StatusEffectSystem)
	{
		StatusEffectSystem->ClearAllEffects();
	}

	UE_LOG(LogTemp, Warning, TEXT("All RPG Systems have been reset"));
}
