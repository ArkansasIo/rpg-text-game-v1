// QuestComponent.h
// Complete quest system with objectives and tracking

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "QuestComponent.generated.h"

USTRUCT(BlueprintType)
struct FQuestObjectiveProgress
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ObjectiveText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentProgress = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredProgress = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCompleted = false;
};

USTRUCT(BlueprintType)
struct FActiveQuest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 QuestID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRPGQuestData QuestData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestObjectiveProgress> Objectives;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestStatus Status = EQuestStatus::Active;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime AcceptedTime;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API UQuestComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================== QUESTS ====================
    
    UPROPERTY(ReplicatedUsing = OnRep_ActiveQuests, BlueprintReadOnly, Category = "Quests")
    TArray<FActiveQuest> ActiveQuests;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Quests")
    TArray<int32> CompletedQuests;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quests")
    UDataTable* QuestDataTable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quests")
    int32 MaxActiveQuests = 25;

    UFUNCTION()
    void OnRep_ActiveQuests();

    // ==================== FUNCTIONS ====================
    
    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool AcceptQuest(int32 QuestID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Quests")
    void Server_AcceptQuest(int32 QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool AbandonQuest(int32 QuestID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Quests")
    void Server_AbandonQuest(int32 QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool CompleteQuest(int32 QuestID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Quests")
    void Server_CompleteQuest(int32 QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void UpdateObjective(int32 QuestID, int32 ObjectiveIndex, int32 Amount = 1);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Quests")
    void Server_UpdateObjective(int32 QuestID, int32 ObjectiveIndex, int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Quests")
    bool HasQuest(int32 QuestID) const;

    UFUNCTION(BlueprintPure, Category = "Quests")
    bool IsQuestComplete(int32 QuestID) const;

    UFUNCTION(BlueprintPure, Category = "Quests")
    bool HasCompletedQuest(int32 QuestID) const;

    UFUNCTION(BlueprintPure, Category = "Quests")
    FActiveQuest GetQuest(int32 QuestID) const;

    UFUNCTION(BlueprintPure, Category = "Quests")
    int32 GetActiveQuestCount() const { return ActiveQuests.Num(); }

    // ==================== EVENTS ====================
    
    UPROPERTY(BlueprintAssignable, Category = "Quests")
    FOnQuestAccepted OnQuestAccepted;

    UPROPERTY(BlueprintAssignable, Category = "Quests")
    FOnQuestCompleted OnQuestCompleted;

protected:
    void GiveQuestRewards(const FRPGQuestData& QuestData);
    bool CheckAllObjectivesComplete(const FActiveQuest& Quest) const;
};

// QuestComponent.cpp
#include "QuestComponent.h"
#include "RPGCharacter.h"
#include "Net/UnrealNetwork.h"

UQuestComponent::UQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void UQuestComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UQuestComponent, ActiveQuests);
    DOREPLIFETIME(UQuestComponent, CompletedQuests);
}

void UQuestComponent::OnRep_ActiveQuests()
{
    // Update UI
}

bool UQuestComponent::AcceptQuest(int32 QuestID)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_AcceptQuest(QuestID);
        return true;
    }

    if (!QuestDataTable)
        return false;

    // Check if already has quest
    if (HasQuest(QuestID) || HasCompletedQuest(QuestID))
        return false;

    // Check max active quests
    if (ActiveQuests.Num() >= MaxActiveQuests)
        return false;

    // Get quest data
    FString ContextString;
    FRPGQuestData* QuestData = QuestDataTable->FindRow<FRPGQuestData>(
        FName(*FString::FromInt(QuestID)), 
        ContextString
    );

    if (!QuestData)
        return false;

    // Check level requirement
    ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
    if (Owner && Owner->Level < QuestData->RequiredLevel)
        return false;

    // Create active quest
    FActiveQuest NewQuest;
    NewQuest.QuestID = QuestID;
    NewQuest.QuestData = *QuestData;
    NewQuest.Status = EQuestStatus::Active;
    NewQuest.AcceptedTime = FDateTime::Now();

    // Initialize objectives
    for (const FString& ObjectiveText : QuestData->Objectives)
    {
        FQuestObjectiveProgress Objective;
        Objective.ObjectiveText = ObjectiveText;
        Objective.CurrentProgress = 0;
        Objective.RequiredProgress = 1; // Would parse from objective text
        Objective.bCompleted = false;
        NewQuest.Objectives.Add(Objective);
    }

    ActiveQuests.Add(NewQuest);
    OnQuestAccepted.Broadcast(QuestID);

    UE_LOG(LogTemp, Log, TEXT("Quest accepted: %s"), *QuestData->QuestName);
    return true;
}

void UQuestComponent::Server_AcceptQuest_Implementation(int32 QuestID)
{
    AcceptQuest(QuestID);
}

bool UQuestComponent::Server_AcceptQuest_Validate(int32 QuestID)
{
    return QuestID > 0;
}

bool UQuestComponent::AbandonQuest(int32 QuestID)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_AbandonQuest(QuestID);
        return true;
    }

    for (int32 i = 0; i < ActiveQuests.Num(); i++)
    {
        if (ActiveQuests[i].QuestID == QuestID)
        {
            ActiveQuests.RemoveAt(i);
            return true;
        }
    }

    return false;
}

void UQuestComponent::Server_AbandonQuest_Implementation(int32 QuestID)
{
    AbandonQuest(QuestID);
}

bool UQuestComponent::Server_AbandonQuest_Validate(int32 QuestID)
{
    return QuestID > 0;
}

bool UQuestComponent::CompleteQuest(int32 QuestID)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_CompleteQuest(QuestID);
        return true;
    }

    for (int32 i = 0; i < ActiveQuests.Num(); i++)
    {
        if (ActiveQuests[i].QuestID == QuestID && CheckAllObjectivesComplete(ActiveQuests[i]))
        {
            // Give rewards
            GiveQuestRewards(ActiveQuests[i].QuestData);

            // Move to completed
            CompletedQuests.Add(QuestID);
            ActiveQuests.RemoveAt(i);

            OnQuestCompleted.Broadcast(QuestID);

            UE_LOG(LogTemp, Log, TEXT("Quest completed: %d"), QuestID);
            return true;
        }
    }

    return false;
}

void UQuestComponent::Server_CompleteQuest_Implementation(int32 QuestID)
{
    CompleteQuest(QuestID);
}

bool UQuestComponent::Server_CompleteQuest_Validate(int32 QuestID)
{
    return HasQuest(QuestID);
}

void UQuestComponent::UpdateObjective(int32 QuestID, int32 ObjectiveIndex, int32 Amount)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        Server_UpdateObjective(QuestID, ObjectiveIndex, Amount);
        return;
    }

    for (FActiveQuest& Quest : ActiveQuests)
    {
        if (Quest.QuestID == QuestID && ObjectiveIndex >= 0 && ObjectiveIndex < Quest.Objectives.Num())
        {
            FQuestObjectiveProgress& Objective = Quest.Objectives[ObjectiveIndex];
            Objective.CurrentProgress = FMath::Min(Objective.CurrentProgress + Amount, Objective.RequiredProgress);

            if (Objective.CurrentProgress >= Objective.RequiredProgress)
            {
                Objective.bCompleted = true;
                UE_LOG(LogTemp, Log, TEXT("Quest objective completed: %s"), *Objective.ObjectiveText);
            }

            // Check if all objectives complete
            if (CheckAllObjectivesComplete(Quest))
            {
                Quest.Status = EQuestStatus::Complete;
            }

            break;
        }
    }
}

void UQuestComponent::Server_UpdateObjective_Implementation(int32 QuestID, int32 ObjectiveIndex, int32 Amount)
{
    UpdateObjective(QuestID, ObjectiveIndex, Amount);
}

bool UQuestComponent::Server_UpdateObjective_Validate(int32 QuestID, int32 ObjectiveIndex, int32 Amount)
{
    return Amount >= 0;
}

bool UQuestComponent::HasQuest(int32 QuestID) const
{
    for (const FActiveQuest& Quest : ActiveQuests)
    {
        if (Quest.QuestID == QuestID)
            return true;
    }
    return false;
}

bool UQuestComponent::IsQuestComplete(int32 QuestID) const
{
    for (const FActiveQuest& Quest : ActiveQuests)
    {
        if (Quest.QuestID == QuestID)
            return Quest.Status == EQuestStatus::Complete;
    }
    return false;
}

bool UQuestComponent::HasCompletedQuest(int32 QuestID) const
{
    return CompletedQuests.Contains(QuestID);
}

FActiveQuest UQuestComponent::GetQuest(int32 QuestID) const
{
    for (const FActiveQuest& Quest : ActiveQuests)
    {
        if (Quest.QuestID == QuestID)
            return Quest;
    }
    return FActiveQuest();
}

void UQuestComponent::GiveQuestRewards(const FRPGQuestData& QuestData)
{
    ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
    if (!Owner)
        return;

    // Give experience
    if (QuestData.ExperienceReward > 0)
    {
        Owner->AddExperience(QuestData.ExperienceReward);
    }

    // Give gold
    if (QuestData.GoldReward > 0)
    {
        Owner->Gold += QuestData.GoldReward;
    }

    // Give item rewards
    if (Owner->InventoryComponent)
    {
        for (const FRPGItemData& Item : QuestData.RewardItems)
        {
            Owner->InventoryComponent->AddItem(Item, 1);
        }
    }
}

bool UQuestComponent::CheckAllObjectivesComplete(const FActiveQuest& Quest) const
{
    for (const FQuestObjectiveProgress& Objective : Quest.Objectives)
    {
        if (!Objective.bCompleted)
            return false;
    }
    return Quest.Objectives.Num() > 0;
}
