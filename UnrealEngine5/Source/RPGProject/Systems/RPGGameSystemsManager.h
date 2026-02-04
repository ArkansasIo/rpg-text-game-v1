#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CharacterProgressionSystem.h"
#include "CombatSystem.h"
#include "InventorySystem.h"
#include "QuestSystem.h"
#include "StatusEffectSystem.h"
#include "RPGGameSystemsManager.generated.h"

/**
 * Master RPG Systems Manager - Central hub for all game systems
 */
UCLASS()
class RPGPROJECT_API ARPGGameSystemsManager : public AGameStateBase
{
	GENERATED_BODY()

public:
	ARPGGameSystemsManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// System Components
	UPROPERTY(BlueprintReadWrite, Category = "RPG Systems")
	class UCharacterProgressionSystem* ProgressionSystem;

	UPROPERTY(BlueprintReadWrite, Category = "RPG Systems")
	class UCombatSystem* CombatSystem;

	UPROPERTY(BlueprintReadWrite, Category = "RPG Systems")
	class UInventorySystem* InventorySystem;

	UPROPERTY(BlueprintReadWrite, Category = "RPG Systems")
	class UQuestSystem* QuestSystem;

	UPROPERTY(BlueprintReadWrite, Category = "RPG Systems")
	class UStatusEffectSystem* StatusEffectSystem;

	// Global Game Settings
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Settings")
	float GlobalDifficultyMultiplier = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Settings")
	bool bEnablePvP = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Settings")
	bool bEnablePermaDeath = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Settings")
	int32 MaxPlayersInParty = 4;

	// Initialization Functions
	UFUNCTION(BlueprintCallable, Category = "RPG Systems")
	void InitializeAllSystems();

	UFUNCTION(BlueprintCallable, Category = "RPG Systems")
	void InitializeProgressionSystem();

	UFUNCTION(BlueprintCallable, Category = "RPG Systems")
	void InitializeCombatSystem();

	UFUNCTION(BlueprintCallable, Category = "RPG Systems")
	void InitializeInventorySystem();

	UFUNCTION(BlueprintCallable, Category = "RPG Systems")
	void InitializeQuestSystem();

	UFUNCTION(BlueprintCallable, Category = "RPG Systems")
	void InitializeStatusEffectSystem();

	// Getter Functions
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Systems")
	class UCharacterProgressionSystem* GetProgressionSystem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Systems")
	class UCombatSystem* GetCombatSystem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Systems")
	class UInventorySystem* GetInventorySystem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Systems")
	class UQuestSystem* GetQuestSystem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RPG Systems")
	class UStatusEffectSystem* GetStatusEffectSystem() const;

	// Global Game State Functions
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void SaveGameProgress();

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void LoadGameProgress();

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void ResetAllSystems();

private:
	bool bSystemsInitialized = false;
};
