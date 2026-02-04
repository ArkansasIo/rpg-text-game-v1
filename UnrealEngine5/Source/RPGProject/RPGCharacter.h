// RPGCharacter.h
// Main player character with all RPG systems

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGTypes.h"
#include "RPGCharacter.generated.h"

UCLASS()
class RPGPROJECT_API ARPGCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ARPGCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================== CHARACTER DATA ====================
    
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "RPG|Character")
    int32 CharacterID;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    FString CharacterName;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    ERPGRace Race;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    ERPGClass Class;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    FString Specialization;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    int32 Level = 1;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    int64 Experience = 0;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Character")
    int64 Gold = 100;

    // ==================== STATS ====================
    
    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Stats")
    int32 Strength = 10;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Stats")
    int32 Agility = 10;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Stats")
    int32 Intelligence = 10;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Stats")
    int32 Stamina = 10;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Stats")
    int32 Spirit = 10;

    // ==================== COMBAT ====================
    
    UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadWrite, Category = "RPG|Combat")
    float CurrentHealth = 100.0f;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Combat")
    float MaxHealth = 100.0f;

    UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadWrite, Category = "RPG|Combat")
    float CurrentMana = 100.0f;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Combat")
    float MaxMana = 100.0f;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Combat")
    float Energy = 100.0f;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Combat")
    float Rage = 0.0f;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Combat")
    int32 ComboPoints = 0;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "RPG|Combat")
    bool bInCombat = false;

    UFUNCTION()
    void OnRep_Health();

    UFUNCTION()
    void OnRep_Mana();

    // ==================== COMPONENTS ====================
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Components")
    class UInventoryComponent* InventoryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Components")
    class UQuestComponent* QuestComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Components")
    class UCombatComponent* CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Components")
    class UEquipmentComponent* EquipmentComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Components")
    class UTalentComponent* TalentComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG|Components")
    class UGuildComponent* GuildComponent;

    // ==================== ACTIONS ====================
    
    UFUNCTION(BlueprintCallable, Category = "RPG|Combat")
    void UseAbility(int32 AbilityID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "RPG|Combat")
    void Server_UseAbility(int32 AbilityID, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "RPG|Combat")
    void TakeDamageRPG(float Damage, AActor* DamageDealer);

    UFUNCTION(Server, Reliable, WithValidation, Category = "RPG|Combat")
    void Server_TakeDamage(float Damage, AActor* DamageDealer);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ShowDamageNumber(float Damage, bool bCritical);

    UFUNCTION(BlueprintCallable, Category = "RPG|Interaction")
    void InteractWithObject(AActor* Target);

    UFUNCTION(Server, Reliable, WithValidation, Category = "RPG|Interaction")
    void Server_Interact(AActor* Target);

    // ==================== MOVEMENT ====================
    
    UFUNCTION(BlueprintCallable, Category = "RPG|Movement")
    void StartSprinting();

    UFUNCTION(BlueprintCallable, Category = "RPG|Movement")
    void StopSprinting();

    UFUNCTION(BlueprintCallable, Category = "RPG|Movement")
    void StartFlying();

    UFUNCTION(BlueprintCallable, Category = "RPG|Movement")
    void StopFlying();

    // ==================== UTILITY ====================
    
    UFUNCTION(BlueprintPure, Category = "RPG|Stats")
    float GetHealthPercent() const { return MaxHealth > 0 ? CurrentHealth / MaxHealth : 0.0f; }

    UFUNCTION(BlueprintPure, Category = "RPG|Stats")
    float GetManaPercent() const { return MaxMana > 0 ? CurrentMana / MaxMana : 0.0f; }

    UFUNCTION(BlueprintPure, Category = "RPG|Stats")
    int32 GetTotalArmor() const;

    UFUNCTION(BlueprintPure, Category = "RPG|Stats")
    int32 GetAttackPower() const;

    UFUNCTION(BlueprintPure, Category = "RPG|Stats")
    int32 GetSpellPower() const;

    UFUNCTION(BlueprintCallable, Category = "RPG|Level")
    void AddExperience(int64 Amount);

    UFUNCTION(BlueprintCallable, Category = "RPG|Level")
    void LevelUp();

protected:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void StartJump();
    void StopJump();

private:
    bool bIsSprinting = false;
    float SprintSpeedMultiplier = 1.5f;
};

// RPGCharacter.cpp
#include "RPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/QuestComponent.h"
#include "Components/CombatComponent.h"
#include "Components/EquipmentComponent.h"
#include "Components/TalentComponent.h"
#include "Components/GuildComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

ARPGCharacter::ARPGCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bAlwaysRelevant = true;

    // Create components
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
    QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
    CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
    EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
    TalentComponent = CreateDefaultSubobject<UTalentComponent>(TEXT("TalentComponent"));
    GuildComponent = CreateDefaultSubobject<UGuildComponent>(TEXT("GuildComponent"));

    // Configure character movement
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.35f;
}

void ARPGCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        // Initialize character on server
        MaxHealth = 100 + (Stamina * 10);
        CurrentHealth = MaxHealth;
        MaxMana = 100 + (Intelligence * 15);
        CurrentMana = MaxMana;
    }
}

void ARPGCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Health/Mana regeneration
    if (!bInCombat && HasAuthority())
    {
        if (CurrentHealth < MaxHealth)
        {
            CurrentHealth = FMath::Min(CurrentHealth + (Spirit * 0.5f * DeltaTime), MaxHealth);
        }

        if (CurrentMana < MaxMana)
        {
            CurrentMana = FMath::Min(CurrentMana + (Spirit * 1.0f * DeltaTime), MaxMana);
        }
    }
}

void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Movement
    PlayerInputComponent->BindAxis("MoveForward", this, &ARPGCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARPGCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    // Actions
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPGCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARPGCharacter::StopJump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ARPGCharacter::StartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ARPGCharacter::StopSprinting);
}

void ARPGCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ARPGCharacter, CharacterID);
    DOREPLIFETIME(ARPGCharacter, CharacterName);
    DOREPLIFETIME(ARPGCharacter, Race);
    DOREPLIFETIME(ARPGCharacter, Class);
    DOREPLIFETIME(ARPGCharacter, Specialization);
    DOREPLIFETIME(ARPGCharacter, Level);
    DOREPLIFETIME(ARPGCharacter, Experience);
    DOREPLIFETIME(ARPGCharacter, Gold);
    DOREPLIFETIME(ARPGCharacter, Strength);
    DOREPLIFETIME(ARPGCharacter, Agility);
    DOREPLIFETIME(ARPGCharacter, Intelligence);
    DOREPLIFETIME(ARPGCharacter, Stamina);
    DOREPLIFETIME(ARPGCharacter, Spirit);
    DOREPLIFETIME(ARPGCharacter, CurrentHealth);
    DOREPLIFETIME(ARPGCharacter, MaxHealth);
    DOREPLIFETIME(ARPGCharacter, CurrentMana);
    DOREPLIFETIME(ARPGCharacter, MaxMana);
    DOREPLIFETIME(ARPGCharacter, Energy);
    DOREPLIFETIME(ARPGCharacter, Rage);
    DOREPLIFETIME(ARPGCharacter, ComboPoints);
    DOREPLIFETIME(ARPGCharacter, bInCombat);
}

void ARPGCharacter::OnRep_Health()
{
    // Update UI
}

void ARPGCharacter::OnRep_Mana()
{
    // Update UI
}

void ARPGCharacter::UseAbility(int32 AbilityID)
{
    if (GetLocalRole() < ROLE_Authority)
    {
        Server_UseAbility(AbilityID, nullptr);
    }
}

void ARPGCharacter::Server_UseAbility_Implementation(int32 AbilityID, AActor* Target)
{
    if (CombatComponent)
    {
        CombatComponent->ExecuteAbility(AbilityID, Target);
    }
}

bool ARPGCharacter::Server_UseAbility_Validate(int32 AbilityID, AActor* Target)
{
    return true;
}

void ARPGCharacter::TakeDamageRPG(float Damage, AActor* DamageDealer)
{
    if (GetLocalRole() < ROLE_Authority)
    {
        Server_TakeDamage(Damage, DamageDealer);
    }
    else
    {
        float FinalDamage = Damage;
        
        // Apply armor reduction
        int32 TotalArmor = GetTotalArmor();
        float ArmorReduction = TotalArmor * 0.001f; // 0.1% per armor point
        FinalDamage *= (1.0f - FMath::Clamp(ArmorReduction, 0.0f, 0.75f));

        CurrentHealth = FMath::Max(0.0f, CurrentHealth - FinalDamage);
        bInCombat = true;

        bool bCritical = FMath::RandRange(0, 100) < 10; // 10% crit chance
        Multicast_ShowDamageNumber(FinalDamage, bCritical);

        if (CurrentHealth <= 0.0f)
        {
            // Handle death
        }
    }
}

void ARPGCharacter::Server_TakeDamage_Implementation(float Damage, AActor* DamageDealer)
{
    TakeDamageRPG(Damage, DamageDealer);
}

bool ARPGCharacter::Server_TakeDamage_Validate(float Damage, AActor* DamageDealer)
{
    return Damage >= 0;
}

void ARPGCharacter::Multicast_ShowDamageNumber_Implementation(float Damage, bool bCritical)
{
    // Spawn damage number widget
}

void ARPGCharacter::InteractWithObject(AActor* Target)
{
    Server_Interact(Target);
}

void ARPGCharacter::Server_Interact_Implementation(AActor* Target)
{
    if (Target)
    {
        // Handle interaction (NPC dialogue, looting, etc.)
    }
}

bool ARPGCharacter::Server_Interact_Validate(AActor* Target)
{
    return true;
}

void ARPGCharacter::AddExperience(int64 Amount)
{
    Experience += Amount;
    
    int64 RequiredXP = Level * 1000;
    while (Experience >= RequiredXP)
    {
        LevelUp();
        RequiredXP = Level * 1000;
    }
}

void ARPGCharacter::LevelUp()
{
    Level++;
    
    // Stat increases based on class
    Strength += 2;
    Agility += 2;
    Intelligence += 2;
    Stamina += 3;
    Spirit += 1;

    MaxHealth = 100 + (Stamina * 10);
    CurrentHealth = MaxHealth;
    MaxMana = 100 + (Intelligence * 15);
    CurrentMana = MaxMana;

    UE_LOG(LogTemp, Warning, TEXT("%s reached level %d!"), *CharacterName, Level);
}

int32 ARPGCharacter::GetTotalArmor() const
{
    int32 BaseArmor = Agility * 2;
    
    if (EquipmentComponent)
    {
        BaseArmor += EquipmentComponent->GetTotalArmorFromEquipment();
    }
    
    return BaseArmor;
}

int32 ARPGCharacter::GetAttackPower() const
{
    return Strength * 2 + Agility;
}

int32 ARPGCharacter::GetSpellPower() const
{
    return Intelligence * 2;
}

void ARPGCharacter::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void ARPGCharacter::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void ARPGCharacter::StartJump()
{
    Jump();
}

void ARPGCharacter::StopJump()
{
    StopJumping();
}

void ARPGCharacter::StartSprinting()
{
    if (!bIsSprinting)
    {
        bIsSprinting = true;
        GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
    }
}

void ARPGCharacter::StopSprinting()
{
    if (bIsSprinting)
    {
        bIsSprinting = false;
        GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
    }
}
