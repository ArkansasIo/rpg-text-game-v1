// RPGGameMode.h
// Main Game Mode for Open World MMORPG

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameMode.generated.h"

UCLASS()
class RPGPROJECT_API ARPGGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ARPGGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Player Management
    UFUNCTION(BlueprintCallable, Category = "RPG|Players")
    void RegisterPlayer(class ARPGPlayerController* PlayerController);

    UFUNCTION(BlueprintCallable, Category = "RPG|Players")
    void UnregisterPlayer(class ARPGPlayerController* PlayerController);

    UFUNCTION(BlueprintCallable, Category = "RPG|Players")
    TArray<ARPGPlayerController*> GetAllPlayers() const { return ActivePlayers; }

    // World Management
    UFUNCTION(BlueprintCallable, Category = "RPG|World")
    void SpawnWorldEvents();

    UFUNCTION(BlueprintCallable, Category = "RPG|World")
    void UpdateDayNightCycle(float DeltaTime);

    // Server Management
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RPG|Server")
    int32 MaxPlayers = 100;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RPG|Server")
    bool bEnablePvP = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RPG|Server")
    float WorldEventSpawnInterval = 300.0f; // 5 minutes

protected:
    UPROPERTY()
    TArray<ARPGPlayerController*> ActivePlayers;

    UPROPERTY()
    float CurrentTimeOfDay = 12.0f; // 0-24 hours

    UPROPERTY()
    float WorldEventTimer = 0.0f;
};

// RPGGameMode.cpp
#include "RPGGameMode.h"
#include "RPGPlayerController.h"
#include "RPGCharacter.h"
#include "Kismet/GameplayStatics.h"

ARPGGameMode::ARPGGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Set default pawn class
    DefaultPawnClass = ARPGCharacter::StaticClass();
    PlayerControllerClass = ARPGPlayerController::StaticClass();
}

void ARPGGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("RPG Game Mode Started - Max Players: %d"), MaxPlayers);
}

void ARPGGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Update day/night cycle
    UpdateDayNightCycle(DeltaTime);
    
    // Handle world events
    WorldEventTimer += DeltaTime;
    if (WorldEventTimer >= WorldEventSpawnInterval)
    {
        SpawnWorldEvents();
        WorldEventTimer = 0.0f;
    }
}

void ARPGGameMode::RegisterPlayer(ARPGPlayerController* PlayerController)
{
    if (PlayerController && !ActivePlayers.Contains(PlayerController))
    {
        ActivePlayers.Add(PlayerController);
        UE_LOG(LogTemp, Log, TEXT("Player registered. Total players: %d"), ActivePlayers.Num());
    }
}

void ARPGGameMode::UnregisterPlayer(ARPGPlayerController* PlayerController)
{
    if (PlayerController)
    {
        ActivePlayers.Remove(PlayerController);
        UE_LOG(LogTemp, Log, TEXT("Player unregistered. Total players: %d"), ActivePlayers.Num());
    }
}

void ARPGGameMode::UpdateDayNightCycle(float DeltaTime)
{
    // 24 real-time minutes = 24 in-game hours
    float TimeScale = 60.0f; // 1 real minute = 1 game hour
    CurrentTimeOfDay += (DeltaTime / 60.0f) * TimeScale;
    
    if (CurrentTimeOfDay >= 24.0f)
    {
        CurrentTimeOfDay -= 24.0f;
    }
    
    // Update directional light (sun)
    // This would be implemented with actual light actors in the level
}

void ARPGGameMode::SpawnWorldEvents()
{
    UE_LOG(LogTemp, Warning, TEXT("World Event Spawned at time: %.2f"), CurrentTimeOfDay);
    // Spawn rare NPCs, world bosses, etc.
}
