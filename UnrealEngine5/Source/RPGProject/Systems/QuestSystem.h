#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestSystem.generated.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	Unaccepted UMETA(DisplayName = "Unaccepted"),
	Active UMETA(DisplayName = "Active"),
	InProgress UMETA(DisplayName = "In Progress"),
	ReadyToTurnIn UMETA(DisplayName = "Ready to Turn In"),
	Completed UMETA(DisplayName = "Completed"),
	Failed UMETA(DisplayName = "Failed"),
	Abandoned UMETA(DisplayName = "Abandoned")
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Kill UMETA(DisplayName = "Kill Quest"),
	Collect UMETA(DisplayName = "Collection Quest"),
	Explore UMETA(DisplayName = "Exploration Quest"),
	Rescue UMETA(DisplayName = "Rescue Quest"),
	Escort UMETA(DisplayName = "Escort Quest"),
	Defend UMETA(DisplayName = "Defense Quest"),
	Puzzle UMETA(DisplayName = "Puzzle Quest"),
	Custom UMETA(DisplayName = "Custom Quest")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnQuestStartedDelegate, const class UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two(FOnQuestProgressDelegate, const class UQuest*, Quest, int32, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnQuestCompletedDelegate, const class UQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnQuestFailedDelegate, const class UQuest*, Quest);

USTRUCT(BlueprintType)
struct FQuestReward
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ExperienceReward = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GoldReward = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> ItemRewards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ReputationReward = 10;
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsComplete = false;
};

/**
 * Individual Quest Object
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UQuest : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType QuestType = EQuestType::Custom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestStatus QuestStatus = EQuestStatus::Unaccepted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RecommendedLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestGiverName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestReward QuestReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanRepeat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMastered = false;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AcceptQuest();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateObjective(const FString& ObjectiveID, int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CompleteQuest();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void FailQuest();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AbandonQuest();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	float GetCompletionPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool IsAllObjectivesComplete() const;
};

/**
 * Quest System for managing all quests
 */
UCLASS(BlueprintType)
class RPGPROJECT_API UQuestSystem : public UObject
{
	GENERATED_BODY()

public:
	UQuestSystem();

	UPROPERTY(BlueprintReadWrite, Category = "Quest System")
	TArray<UQuest*> ActiveQuests;

	UPROPERTY(BlueprintReadWrite, Category = "Quest System")
	TArray<UQuest*> CompletedQuests;

	UPROPERTY(BlueprintReadWrite, Category = "Quest System")
	TArray<UQuest*> AvailableQuests;

	UPROPERTY(BlueprintReadWrite, Category = "Quest System")
	int32 TotalQuestsCompleted = 0;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Quest Events")
	FOnQuestStartedDelegate OnQuestStarted;

	UPROPERTY(BlueprintAssignable, Category = "Quest Events")
	FOnQuestProgressDelegate OnQuestProgress;

	UPROPERTY(BlueprintAssignable, Category = "Quest Events")
	FOnQuestCompletedDelegate OnQuestCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Quest Events")
	FOnQuestFailedDelegate OnQuestFailed;

	// Quest Management
	UFUNCTION(BlueprintCallable, Category = "Quest System")
	void RegisterQuest(UQuest* NewQuest);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	bool AcceptQuest(const FString& QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	bool CompleteQuest(const FString& QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	bool FailQuest(const FString& QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	bool AbandonQuest(const FString& QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	UQuest* GetQuest(const FString& QuestID);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	void UpdateQuestProgress(const FString& QuestID, const FString& ObjectiveID, int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	TArray<UQuest*> GetAvailableQuestsForLevel(int32 PlayerLevel) const;

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	int32 GetTotalCompletedQuests() const;

private:
	TMap<FString, UQuest*> QuestMap;
};
