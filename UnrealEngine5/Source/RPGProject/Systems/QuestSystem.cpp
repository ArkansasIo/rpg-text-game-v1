#include "QuestSystem.h"

// --- UQuest Implementation ---

void UQuest::AcceptQuest()
{
	if (QuestStatus == EQuestStatus::Unaccepted)
	{
		QuestStatus = EQuestStatus::Active;
	}
}

void UQuest::UpdateObjective(const FString& ObjectiveID, int32 Amount)
{
	for (FQuestObjective& Objective : Objectives)
	{
		if (Objective.ObjectiveID == ObjectiveID)
		{
			Objective.CurrentCount += Amount;
			if (Objective.CurrentCount >= Objective.TargetCount)
			{
				Objective.CurrentCount = Objective.TargetCount;
				Objective.bIsComplete = true;
			}
			return;
		}
	}
}

void UQuest::CompleteQuest()
{
	if (IsAllObjectivesComplete())
	{
		QuestStatus = EQuestStatus::Completed;
		bIsMastered = true;
	}
}

void UQuest::FailQuest()
{
	QuestStatus = EQuestStatus::Failed;
}

void UQuest::AbandonQuest()
{
	QuestStatus = EQuestStatus::Abandoned;
}

float UQuest::GetCompletionPercentage() const
{
	if (Objectives.Num() == 0)
	{
		return 0.0f;
	}

	int32 CompletedObjectives = 0;
	for (const FQuestObjective& Objective : Objectives)
	{
		if (Objective.bIsComplete)
		{
			CompletedObjectives++;
		}
	}

	return (float)CompletedObjectives / (float)Objectives.Num() * 100.0f;
}

bool UQuest::IsAllObjectivesComplete() const
{
	if (Objectives.Num() == 0)
	{
		return false;
	}

	for (const FQuestObjective& Objective : Objectives)
	{
		if (!Objective.bIsComplete)
		{
			return false;
		}
	}

	return true;
}

// --- UQuestSystem Implementation ---

UQuestSystem::UQuestSystem()
{
	TotalQuestsCompleted = 0;
}

void UQuestSystem::RegisterQuest(UQuest* NewQuest)
{
	if (NewQuest)
	{
		AvailableQuests.Add(NewQuest);
		QuestMap.Add(NewQuest->QuestID, NewQuest);
	}
}

bool UQuestSystem::AcceptQuest(const FString& QuestID)
{
	UQuest* Quest = GetQuest(QuestID);
	if (!Quest)
	{
		return false;
	}

	Quest->AcceptQuest();
	if (Quest->QuestStatus == EQuestStatus::Active)
	{
		ActiveQuests.Add(Quest);
		AvailableQuests.Remove(Quest);
		OnQuestStarted.Broadcast(Quest);
		return true;
	}

	return false;
}

bool UQuestSystem::CompleteQuest(const FString& QuestID)
{
	UQuest* Quest = GetQuest(QuestID);
	if (!Quest || !Quest->IsAllObjectivesComplete())
	{
		return false;
	}

	Quest->CompleteQuest();
	ActiveQuests.Remove(Quest);
	CompletedQuests.Add(Quest);
	TotalQuestsCompleted++;
	OnQuestCompleted.Broadcast(Quest);

	return true;
}

bool UQuestSystem::FailQuest(const FString& QuestID)
{
	UQuest* Quest = GetQuest(QuestID);
	if (!Quest)
	{
		return false;
	}

	Quest->FailQuest();
	ActiveQuests.Remove(Quest);
	OnQuestFailed.Broadcast(Quest);

	return true;
}

bool UQuestSystem::AbandonQuest(const FString& QuestID)
{
	UQuest* Quest = GetQuest(QuestID);
	if (!Quest)
	{
		return false;
	}

	Quest->AbandonQuest();
	ActiveQuests.Remove(Quest);
	AvailableQuests.Add(Quest);

	return true;
}

UQuest* UQuestSystem::GetQuest(const FString& QuestID)
{
	if (QuestMap.Contains(QuestID))
	{
		return QuestMap[QuestID];
	}
	return nullptr;
}

void UQuestSystem::UpdateQuestProgress(const FString& QuestID, const FString& ObjectiveID, int32 Amount)
{
	UQuest* Quest = GetQuest(QuestID);
	if (Quest)
	{
		Quest->UpdateObjective(ObjectiveID, Amount);
		OnQuestProgress.Broadcast(Quest, static_cast<int32>(Quest->GetCompletionPercentage()));
	}
}

TArray<UQuest*> UQuestSystem::GetAvailableQuestsForLevel(int32 PlayerLevel) const
{
	TArray<UQuest*> AvailableForLevel;
	for (UQuest* Quest : AvailableQuests)
	{
		if (Quest && Quest->RecommendedLevel <= PlayerLevel)
		{
			AvailableForLevel.Add(Quest);
		}
	}
	return AvailableForLevel;
}

int32 UQuestSystem::GetTotalCompletedQuests() const
{
	return TotalQuestsCompleted;
}
