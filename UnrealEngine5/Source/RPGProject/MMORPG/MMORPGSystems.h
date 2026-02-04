#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MMORPGSystems.generated.h"

/**
 * PARTY SYSTEM
 */

USTRUCT(BlueprintType)
struct FPartyMember
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	FName MemberName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	class ARPGCharacter* MemberCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	FString ClassName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	float ManaPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	bool bIsLeader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	bool bIsOnline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	int32 Distance; // In meters
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnPartyMemberJoined, FName, MemberName, int32, PartySize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnPartyMemberLeft, FName, MemberName, int32, RemainingMembers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnPartyDisbanded, int32, PartyID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Three(FOnPartyMemberHealthChanged, FName, MemberName, float, HealthPercent, float, ManaPercent);

UCLASS(Blueprintable)
class RPGPROJECT_API APartySystem : public AInfo
{
	GENERATED_BODY()

public:
	APartySystem();

	// Party Management
	UFUNCTION(BlueprintCallable, Category = "Party")
	void CreateParty(class ARPGCharacter* Leader, const FString& PartyName);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void InviteToParty(class ARPGCharacter* Invitee);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void AcceptPartyInvite(class ARPGCharacter* Member);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void DeclinePartyInvite();

	UFUNCTION(BlueprintCallable, Category = "Party")
	void LeaveParty();

	UFUNCTION(BlueprintCallable, Category = "Party")
	void KickFromParty(FName MemberName);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void DisbandParty();

	UFUNCTION(BlueprintCallable, Category = "Party")
	void TransferLeadership(FName NewLeaderName);

	// Getters
	UFUNCTION(BlueprintPure, Category = "Party")
	TArray<FPartyMember> GetPartyMembers() const { return PartyMembers; }

	UFUNCTION(BlueprintPure, Category = "Party")
	FPartyMember GetPartyMember(FName MemberName) const;

	UFUNCTION(BlueprintPure, Category = "Party")
	int32 GetPartySize() const { return PartyMembers.Num(); }

	UFUNCTION(BlueprintPure, Category = "Party")
	bool IsMemberInParty(FName MemberName) const;

	UFUNCTION(BlueprintPure, Category = "Party")
	bool IsPartyLeader(FName MemberName) const;

	// Loot Distribution
	UFUNCTION(BlueprintCallable, Category = "Party|Loot")
	void SetLootDistribution(int32 Mode); // 0=Need Before Greed, 1=Round Robin, 2=Master Loot, 3=Free For All

	UFUNCTION(BlueprintCallable, Category = "Party|Loot")
	void DistributeLoot(class AItem* LootItem, int32 Rarity);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Party|Events")
	FOnPartyMemberJoined OnMemberJoined;

	UPROPERTY(BlueprintAssignable, Category = "Party|Events")
	FOnPartyMemberLeft OnMemberLeft;

	UPROPERTY(BlueprintAssignable, Category = "Party|Events")
	FOnPartyDisbanded OnPartyDisbanded;

	UPROPERTY(BlueprintAssignable, Category = "Party|Events")
	FOnPartyMemberHealthChanged OnMemberHealthChanged;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Party")
	int32 PartyID;

	UPROPERTY(BlueprintReadOnly, Category = "Party")
	FString PartyName;

	UPROPERTY(BlueprintReadOnly, Category = "Party")
	TArray<FPartyMember> PartyMembers;

	UPROPERTY(BlueprintReadOnly, Category = "Party")
	int32 MaxPartySize = 5;

	UPROPERTY(BlueprintReadOnly, Category = "Party")
	int32 LootDistributionMode = 0;
};

/**
 * RAID SYSTEM
 */

USTRUCT(BlueprintType)
struct FRaidMember
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Raid")
	FName MemberName;

	UPROPERTY(BlueprintReadWrite, Category = "Raid")
	class ARPGCharacter* MemberCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "Raid")
	FString ClassName;

	UPROPERTY(BlueprintReadWrite, Category = "Raid")
	int32 Group; // 1-8

	UPROPERTY(BlueprintReadWrite, Category = "Raid")
	bool bIsReadyCheck;
};

UCLASS(Blueprintable)
class RPGPROJECT_API ARaidSystem : public AInfo
{
	GENERATED_BODY()

public:
	ARaidSystem();

	// Raid Management
	UFUNCTION(BlueprintCallable, Category = "Raid")
	void CreateRaid(class ARPCCharacter* Leader, const FString& RaidName, int32 MaxPlayers = 20);

	UFUNCTION(BlueprintCallable, Category = "Raid")
	void InviteToRaid(class ARPGCharacter* Invitee);

	UFUNCTION(BlueprintCallable, Category = "Raid")
	void JoinRaid();

	UFUNCTION(BlueprintCallable, Category = "Raid")
	void LeaveRaid();

	UFUNCTION(BlueprintCallable, Category = "Raid")
	void DisbandRaid();

	// Ready Check
	UFUNCTION(BlueprintCallable, Category = "Raid")
	void InitiateReadyCheck();

	UFUNCTION(BlueprintCallable, Category = "Raid")
	void MarkReady(bool bReady);

	// Group Management
	UFUNCTION(BlueprintCallable, Category = "Raid")
	void SetGroup(FName MemberName, int32 GroupNumber);

	UFUNCTION(BlueprintCallable, Category = "Raid")
	int32 GetMemberGroup(FName MemberName) const;

	// Getters
	UFUNCTION(BlueprintPure, Category = "Raid")
	TArray<FRaidMember> GetRaidMembers() const { return RaidMembers; }

	UFUNCTION(BlueprintPure, Category = "Raid")
	int32 GetRaidSize() const { return RaidMembers.Num(); }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Raid")
	FString RaidName;

	UPROPERTY(BlueprintReadOnly, Category = "Raid")
	TArray<FRaidMember> RaidMembers;

	UPROPERTY(BlueprintReadOnly, Category = "Raid")
	int32 MaxRaidSize = 20;

	UPROPERTY(BlueprintReadOnly, Category = "Raid")
	bool bReadyCheckInProgress = false;
};

/**
 * GUILD SYSTEM - Advanced
 */

UENUM(BlueprintType)
enum class EGuildRank : uint8
{
	Founder UMETA(DisplayName = "Founder"),
	LeadOfficer UMETA(DisplayName = "Lead Officer"),
	Officer UMETA(DisplayName = "Officer"),
	Member UMETA(DisplayName = "Member"),
	Initiate UMETA(DisplayName = "Initiate")
};

USTRUCT(BlueprintType)
struct FGuildMember
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FName MemberName;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	int32 Level;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FString ClassName;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	EGuildRank Rank;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	int32 GuildXP;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	bool bIsOnline;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FDateTime JoinDate;
};

USTRUCT(BlueprintType)
struct FGuildInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	int32 GuildID;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FString GuildName;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FString Tagline;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FString Leader;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	int32 MemberCount;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	int32 Level;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	int64 TotalGuildXP;

	UPROPERTY(BlueprintReadWrite, Category = "Guild")
	FLinearColor GuildColor;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnGuildMemberJoined, FName, MemberName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnGuildMemberLeft, FName, MemberName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnGuildLevelUp, int32, NewLevel, int64, TotalXP);

UCLASS(Blueprintable)
class RPGPROJECT_API AGuildSystem : public AInfo
{
	GENERATED_BODY()

public:
	AGuildSystem();

	// Guild Management
	UFUNCTION(BlueprintCallable, Category = "Guild")
	void CreateGuild(class ARPGCharacter* Founder, const FString& GuildName, const FString& Tagline);

	UFUNCTION(BlueprintCallable, Category = "Guild")
	void InviteToGuild(class ARPGCharacter* Invitee);

	UFUNCTION(BlueprintCallable, Category = "Guild")
	void JoinGuild(class ARPGCharacter* Member);

	UFUNCTION(BlueprintCallable, Category = "Guild")
	void LeaveGuild(class ARPGCharacter* Member);

	UFUNCTION(BlueprintCallable, Category = "Guild")
	void KickFromGuild(FName MemberName);

	UFUNCTION(BlueprintCallable, Category = "Guild")
	void DisbandGuild();

	// Rank Management
	UFUNCTION(BlueprintCallable, Category = "Guild|Rank")
	void SetMemberRank(FName MemberName, EGuildRank NewRank);

	UFUNCTION(BlueprintPure, Category = "Guild|Rank")
	EGuildRank GetMemberRank(FName MemberName) const;

	// Guild Perks & Leveling
	UFUNCTION(BlueprintCallable, Category = "Guild|Leveling")
	void AddGuildXP(int32 XPAmount);

	UFUNCTION(BlueprintPure, Category = "Guild|Leveling")
	int32 GetGuildLevel() const { return GuildInfo.Level; }

	UFUNCTION(BlueprintPure, Category = "Guild|Leveling")
	int64 GetGuildXP() const { return GuildInfo.TotalGuildXP; }

	// Getters
	UFUNCTION(BlueprintPure, Category = "Guild")
	FGuildInfo GetGuildInfo() const { return GuildInfo; }

	UFUNCTION(BlueprintPure, Category = "Guild")
	TArray<FGuildMember> GetGuildMembers() const { return GuildMembers; }

	UFUNCTION(BlueprintPure, Category = "Guild")
	int32 GetMemberCount() const { return GuildMembers.Num(); }

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Guild|Events")
	FOnGuildMemberJoined OnMemberJoined;

	UPROPERTY(BlueprintAssignable, Category = "Guild|Events")
	FOnGuildMemberLeft OnMemberLeft;

	UPROPERTY(BlueprintAssignable, Category = "Guild|Events")
	FOnGuildLevelUp OnGuildLevelUp;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Guild")
	FGuildInfo GuildInfo;

	UPROPERTY(BlueprintReadOnly, Category = "Guild")
	TArray<FGuildMember> GuildMembers;

	UPROPERTY(BlueprintReadOnly, Category = "Guild")
	int32 MaxGuildMembers = 200;

private:
	void CheckGuildLevelUp();
};

/**
 * SOCIAL SYSTEM
 */

USTRUCT(BlueprintType)
struct FFriend
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Social")
	FName FriendName;

	UPROPERTY(BlueprintReadWrite, Category = "Social")
	int32 FriendLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Social")
	FString ClassName;

	UPROPERTY(BlueprintReadWrite, Category = "Social")
	bool bIsOnline;

	UPROPERTY(BlueprintReadWrite, Category = "Social")
	FString CurrentZone;

	UPROPERTY(BlueprintReadWrite, Category = "Social")
	FDateTime LastOnline;
};

UCLASS(Blueprintable)
class RPGPROJECT_API ASocialSystem : public AInfo
{
	GENERATED_BODY()

public:
	ASocialSystem();

	// Friends
	UFUNCTION(BlueprintCallable, Category = "Social")
	void AddFriend(FName FriendName);

	UFUNCTION(BlueprintCallable, Category = "Social")
	void RemoveFriend(FName FriendName);

	UFUNCTION(BlueprintCallable, Category = "Social")
	void BlockPlayer(FName PlayerName);

	UFUNCTION(BlueprintCallable, Category = "Social")
	void UnblockPlayer(FName PlayerName);

	// Chat
	UFUNCTION(BlueprintCallable, Category = "Social|Chat")
	void SendMessage(const FString& Message, int32 ChatChannel); // 0=Say, 1=Party, 2=Guild, 3=Trade, 4=Whisper

	UFUNCTION(BlueprintCallable, Category = "Social|Chat")
	void SendWhisper(FName TargetPlayer, const FString& Message);

	// Getters
	UFUNCTION(BlueprintPure, Category = "Social")
	TArray<FFriend> GetFriends() const { return Friends; }

	UFUNCTION(BlueprintPure, Category = "Social")
	bool IsFriend(FName PlayerName) const;

	UFUNCTION(BlueprintPure, Category = "Social")
	bool IsBlocked(FName PlayerName) const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Social")
	TArray<FFriend> Friends;

	UPROPERTY(BlueprintReadOnly, Category = "Social")
	TArray<FName> BlockedPlayers;

	UPROPERTY(BlueprintReadOnly, Category = "Social")
	int32 MaxFriends = 200;
};
