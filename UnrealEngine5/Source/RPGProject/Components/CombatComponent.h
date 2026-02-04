// CombatComponent.h
// Complete combat system with abilities, cooldowns, and damage calculation

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "CombatComponent.generated.h"

USTRUCT(BlueprintType)
struct FAbilityCooldown
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AbilityID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RemainingTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalCooldown = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================== ABILITIES ====================
    
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Combat")
    TArray<int32> LearnedAbilities;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Combat")
    TArray<FAbilityCooldown> AbilityCooldowns;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    UDataTable* AbilityDataTable;

    // ==================== TARGETING ====================
    
    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Combat")
    AActor* CurrentTarget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    float MaxTargetDistance = 4000.0f;

    // ==================== FUNCTIONS ====================
    
    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool ExecuteAbility(int32 AbilityID, AActor* Target);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Combat")
    void Server_ExecuteAbility(int32 AbilityID, AActor* Target);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_PlayAbilityEffects(int32 AbilityID, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void LearnAbility(int32 AbilityID);

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool HasAbility(int32 AbilityID) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsAbilityOnCooldown(int32 AbilityID) const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    float GetAbilityCooldownPercent(int32 AbilityID) const;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetTarget(AActor* NewTarget);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ClearTarget();

    UFUNCTION(BlueprintPure, Category = "Combat")
    float CalculateDamage(const FRPGAbilityData& Ability) const;

protected:
    void UpdateCooldowns(float DeltaTime);
    void StartCooldown(int32 AbilityID, float Duration);
    bool CanUseAbility(const FRPGAbilityData& Ability) const;
    void ConsumeResources(const FRPGAbilityData& Ability);
    void ApplyDamage(AActor* Target, float Damage);
    void ApplyHealing(AActor* Target, float Healing);
};

// CombatComponent.cpp
#include "CombatComponent.h"
#include "RPGCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"

UCombatComponent::UCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (GetOwnerRole() == ROLE_Authority)
    {
        UpdateCooldowns(DeltaTime);
    }
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UCombatComponent, LearnedAbilities);
    DOREPLIFETIME(UCombatComponent, AbilityCooldowns);
    DOREPLIFETIME(UCombatComponent, CurrentTarget);
}

bool UCombatComponent::ExecuteAbility(int32 AbilityID, AActor* Target)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_ExecuteAbility(AbilityID, Target);
        return true;
    }

    if (!AbilityDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("AbilityDataTable is not set!"));
        return false;
    }

    // Get ability data
    FString ContextString;
    FRPGAbilityData* AbilityData = AbilityDataTable->FindRow<FRPGAbilityData>(
        FName(*FString::FromInt(AbilityID)), 
        ContextString
    );

    if (!AbilityData)
    {
        UE_LOG(LogTemp, Error, TEXT("Ability %d not found!"), AbilityID);
        return false;
    }

    // Check if can use ability
    if (!CanUseAbility(*AbilityData))
        return false;

    ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
    if (!Owner)
        return false;

    // Consume resources
    ConsumeResources(*AbilityData);

    // Start cooldown
    StartCooldown(AbilityID, AbilityData->Cooldown);

    // Apply effects
    if (AbilityData->Damage > 0.0f && Target)
    {
        float FinalDamage = CalculateDamage(*AbilityData);
        ApplyDamage(Target, FinalDamage);
    }

    if (AbilityData->Healing > 0.0f)
    {
        ApplyHealing(Target ? Target : Owner, AbilityData->Healing);
    }

    // Play effects
    Multicast_PlayAbilityEffects(AbilityID, Target ? Target->GetActorLocation() : Owner->GetActorLocation());

    return true;
}

void UCombatComponent::Server_ExecuteAbility_Implementation(int32 AbilityID, AActor* Target)
{
    ExecuteAbility(AbilityID, Target);
}

bool UCombatComponent::Server_ExecuteAbility_Validate(int32 AbilityID, AActor* Target)
{
    return HasAbility(AbilityID);
}

void UCombatComponent::Multicast_PlayAbilityEffects_Implementation(int32 AbilityID, FVector Location)
{
    if (!AbilityDataTable)
        return;

    FString ContextString;
    FRPGAbilityData* AbilityData = AbilityDataTable->FindRow<FRPGAbilityData>(
        FName(*FString::FromInt(AbilityID)), 
        ContextString
    );

    if (AbilityData)
    {
        // Spawn cast effect
        if (AbilityData->CastEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                AbilityData->CastEffect,
                GetOwner()->GetActorLocation()
            );
        }

        // Spawn hit effect
        if (AbilityData->HitEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                AbilityData->HitEffect,
                Location
            );
        }

        // Play sound
        if (AbilityData->CastSound)
        {
            UGameplayStatics::PlaySoundAtLocation(
                GetWorld(),
                AbilityData->CastSound,
                GetOwner()->GetActorLocation()
            );
        }
    }
}

void UCombatComponent::LearnAbility(int32 AbilityID)
{
    if (!LearnedAbilities.Contains(AbilityID))
    {
        LearnedAbilities.Add(AbilityID);
        UE_LOG(LogTemp, Log, TEXT("Learned ability: %d"), AbilityID);
    }
}

bool UCombatComponent::HasAbility(int32 AbilityID) const
{
    return LearnedAbilities.Contains(AbilityID);
}

bool UCombatComponent::IsAbilityOnCooldown(int32 AbilityID) const
{
    for (const FAbilityCooldown& CD : AbilityCooldowns)
    {
        if (CD.AbilityID == AbilityID && CD.RemainingTime > 0.0f)
            return true;
    }
    return false;
}

float UCombatComponent::GetAbilityCooldownPercent(int32 AbilityID) const
{
    for (const FAbilityCooldown& CD : AbilityCooldowns)
    {
        if (CD.AbilityID == AbilityID)
            return CD.TotalCooldown > 0 ? (1.0f - CD.RemainingTime / CD.TotalCooldown) : 1.0f;
    }
    return 1.0f;
}

void UCombatComponent::SetTarget(AActor* NewTarget)
{
    if (NewTarget && FVector::Dist(GetOwner()->GetActorLocation(), NewTarget->GetActorLocation()) <= MaxTargetDistance)
    {
        CurrentTarget = NewTarget;
    }
}

void UCombatComponent::ClearTarget()
{
    CurrentTarget = nullptr;
}

float UCombatComponent::CalculateDamage(const FRPGAbilityData& Ability) const
{
    ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
    if (!Owner)
        return Ability.Damage;

    float BaseDamage = Ability.Damage;
    
    // Add attack power or spell power
    if (Ability.ManaCost > 0)
    {
        // Spell damage
        BaseDamage += Owner->GetSpellPower() * 0.5f;
    }
    else
    {
        // Physical damage
        BaseDamage += Owner->GetAttackPower() * 0.3f;
    }

    // Random variance (±10%)
    BaseDamage *= FMath::RandRange(0.9f, 1.1f);

    return BaseDamage;
}

void UCombatComponent::UpdateCooldowns(float DeltaTime)
{
    for (FAbilityCooldown& CD : AbilityCooldowns)
    {
        if (CD.RemainingTime > 0.0f)
        {
            CD.RemainingTime = FMath::Max(0.0f, CD.RemainingTime - DeltaTime);
        }
    }
}

void UCombatComponent::StartCooldown(int32 AbilityID, float Duration)
{
    // Find existing cooldown
    for (FAbilityCooldown& CD : AbilityCooldowns)
    {
        if (CD.AbilityID == AbilityID)
        {
            CD.RemainingTime = Duration;
            CD.TotalCooldown = Duration;
            return;
        }
    }

    // Add new cooldown
    FAbilityCooldown NewCD;
    NewCD.AbilityID = AbilityID;
    NewCD.RemainingTime = Duration;
    NewCD.TotalCooldown = Duration;
    AbilityCooldowns.Add(NewCD);
}

bool UCombatComponent::CanUseAbility(const FRPGAbilityData& Ability) const
{
    ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
    if (!Owner)
        return false;

    // Check cooldown
    if (IsAbilityOnCooldown(Ability.AbilityID))
        return false;

    // Check resources
    if (Ability.ManaCost > 0 && Owner->CurrentMana < Ability.ManaCost)
        return false;

    if (Ability.EnergyCost > 0 && Owner->Energy < Ability.EnergyCost)
        return false;

    if (Ability.RageCost > 0 && Owner->Rage < Ability.RageCost)
        return false;

    // Check target
    if (Ability.Range > 0 && CurrentTarget)
    {
        float Distance = FVector::Dist(Owner->GetActorLocation(), CurrentTarget->GetActorLocation());
        if (Distance > Ability.Range)
            return false;
    }

    return true;
}

void UCombatComponent::ConsumeResources(const FRPGAbilityData& Ability)
{
    ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
    if (!Owner)
        return;

    Owner->CurrentMana = FMath::Max(0.0f, Owner->CurrentMana - Ability.ManaCost);
    Owner->Energy = FMath::Max(0.0f, Owner->Energy - Ability.EnergyCost);
    Owner->Rage = FMath::Max(0.0f, Owner->Rage - Ability.RageCost);
}

void UCombatComponent::ApplyDamage(AActor* Target, float Damage)
{
    ARPGCharacter* TargetChar = Cast<ARPGCharacter>(Target);
    if (TargetChar)
    {
        TargetChar->TakeDamageRPG(Damage, GetOwner());
    }
}

void UCombatComponent::ApplyHealing(AActor* Target, float Healing)
{
    ARPGCharacter* TargetChar = Cast<ARPGCharacter>(Target);
    if (TargetChar)
    {
        TargetChar->CurrentHealth = FMath::Min(TargetChar->MaxHealth, TargetChar->CurrentHealth + Healing);
    }
}
