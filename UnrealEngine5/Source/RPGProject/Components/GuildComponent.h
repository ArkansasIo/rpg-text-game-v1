// GuildComponent.h
// Complete guild system with ranks, permissions, bank

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "GuildComponent.generated.h"

USTRUCT(BlueprintType)
struct FGuildMember
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CharacterID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RankID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RankName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOnline = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime JoinDate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime LastOnline;
};

USTRUCT(BlueprintType)
struct FGuildRank
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RankID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RankName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanInvite = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanKick = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanPromote = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanEditRanks = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanAccessGuildBank = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DailyWithdrawLimit = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API UGuildComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGuildComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================== GUILD INFO ====================
    
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Guild")
    FGuildInfo GuildInfo;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Guild")
    TArray<FGuildMember> GuildMembers;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Guild")
    TArray<FGuildRank> GuildRanks;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Guild")
    int32 PlayerRankID = 0;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Guild")
    int64 GuildGold = 0;

    // ==================== FUNCTIONS ====================
    
    UFUNCTION(BlueprintCallable, Category = "Guild")
    void CreateGuild(const FString& GuildName, const FString& GuildTag);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_CreateGuild(const FString& GuildName, const FString& GuildTag);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void InviteToGuild(const FString& CharacterName);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_InviteToGuild(const FString& CharacterName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void AcceptGuildInvite(int32 GuildID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_AcceptGuildInvite(int32 GuildID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void LeaveGuild();

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_LeaveGuild();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void KickMember(const FString& CharacterName);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_KickMember(const FString& CharacterName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void PromoteMember(const FString& CharacterName, int32 NewRankID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_PromoteMember(const FString& CharacterName, int32 NewRankID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void SendGuildChat(const FString& Message);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Guild")
    void Server_SendGuildChat(const FString& Message);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ReceiveGuildChat(const FString& Sender, const FString& Message);

    UFUNCTION(BlueprintPure, Category = "Guild")
    bool IsInGuild() const { return GuildInfo.GuildID > 0; }

    UFUNCTION(BlueprintPure, Category = "Guild")
    bool HasPermission(const FString& Permission) const;

    UFUNCTION(BlueprintPure, Category = "Guild")
    FGuildRank GetPlayerRank() const;

    // ==================== EVENTS ====================
    
    UPROPERTY(BlueprintAssignable, Category = "Guild")
    FOnGuildInvite OnGuildInvite;

protected:
    void InitializeDefaultRanks();
    FGuildRank* FindRank(int32 RankID);
};

// EquipmentComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "EquipmentComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API UEquipmentComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEquipmentComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ==================== EQUIPMENT ====================
    
    UPROPERTY(ReplicatedUsing = OnRep_Equipment, BlueprintReadOnly, Category = "Equipment")
    TMap<EEquipmentSlot, FRPGItemData> EquippedItems;

    UFUNCTION()
    void OnRep_Equipment();

    // ==================== FUNCTIONS ====================
    
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    bool EquipItem(const FRPGItemData& Item, EEquipmentSlot Slot);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Equipment")
    void Server_EquipItem(const FRPGItemData& Item, EEquipmentSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    bool UnequipItem(EEquipmentSlot Slot);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Equipment")
    void Server_UnequipItem(EEquipmentSlot Slot);

    UFUNCTION(BlueprintPure, Category = "Equipment")
    FRPGItemData GetEquippedItem(EEquipmentSlot Slot) const;

    UFUNCTION(BlueprintPure, Category = "Equipment")
    bool IsSlotEquipped(EEquipmentSlot Slot) const;

    UFUNCTION(BlueprintPure, Category = "Equipment")
    int32 GetTotalArmorFromEquipment() const;

    UFUNCTION(BlueprintPure, Category = "Equipment")
    int32 GetTotalStatBonus(const FString& StatName) const;

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void UpdateVisualEquipment();

protected:
    void ApplyItemStats(const FRPGItemData& Item, bool bApply);
    void AttachItemMesh(const FRPGItemData& Item, EEquipmentSlot Slot);
    void DetachItemMesh(EEquipmentSlot Slot);
    EEquipmentSlot DetermineSlotForItem(const FRPGItemData& Item) const;
};

// TalentComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TalentComponent.generated.h"

USTRUCT(BlueprintType)
struct FTalentNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TalentID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TalentName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxRank = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentRank = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TreeIndex = 0; // 0, 1, or 2 for the three talent trees

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Row = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Column = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredPoints = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> RequiredTalents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon = nullptr;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPROJECT_API UTalentComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTalentComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Talents")
    TArray<FTalentNode> LearnedTalents;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Talents")
    int32 UnspentTalentPoints = 0;

    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Talents")
    TArray<int32> TreePoints; // Points spent in each tree [0,0,0]

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Talents")
    UDataTable* TalentDataTable;

    UFUNCTION(BlueprintCallable, Category = "Talents")
    bool LearnTalent(int32 TalentID);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Talents")
    void Server_LearnTalent(int32 TalentID);

    UFUNCTION(BlueprintCallable, Category = "Talents")
    void ResetTalents(int32 TreeIndex = -1);

    UFUNCTION(Server, Reliable, WithValidation, Category = "Talents")
    void Server_ResetTalents(int32 TreeIndex);

    UFUNCTION(BlueprintPure, Category = "Talents")
    bool HasTalent(int32 TalentID) const;

    UFUNCTION(BlueprintPure, Category = "Talents")
    int32 GetTalentRank(int32 TalentID) const;

    UFUNCTION(BlueprintPure, Category = "Talents")
    bool CanLearnTalent(const FTalentNode& Talent) const;

    UFUNCTION(BlueprintCallable, Category = "Talents")
    void AwardTalentPoint();
};
