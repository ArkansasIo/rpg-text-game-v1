#include "StatusEffectSystem.h"

UStatusEffectSystem::UStatusEffectSystem()
{
	TickTimer = 0.0f;
}

void UStatusEffectSystem::ApplyEffect(const FStatusEffect& NewEffect)
{
	// Check if effect already exists and can stack
	FStatusEffect* ExistingEffect = GetEffect(NewEffect.EffectID);
	if (ExistingEffect)
	{
		if (ExistingEffect->bCanStack && ExistingEffect->Stacks < ExistingEffect->MaxStacks)
		{
			ExistingEffect->Stacks++;
			ExistingEffect->RemainingTime = ExistingEffect->Duration; // Refresh duration
			return;
		}
		else
		{
			// Refresh existing effect
			ExistingEffect->RemainingTime = NewEffect.Duration;
			return;
		}
	}

	// Add new effect
	FStatusEffect Effect = NewEffect;
	Effect.RemainingTime = Effect.Duration;
	ActiveEffects.Add(Effect);
	OnStatusEffectApplied.Broadcast(NewEffect.EffectType);
}

void UStatusEffectSystem::RemoveEffect(const FString& EffectID)
{
	FStatusEffect* Effect = GetEffect(EffectID);
	if (Effect)
	{
		EStatusEffectType EffectType = Effect->EffectType;
		ActiveEffects.Remove(*Effect);
		OnStatusEffectRemoved.Broadcast(EffectType);
	}
}

void UStatusEffectSystem::RemoveEffectByType(EStatusEffectType EffectType)
{
	ActiveEffects.RemoveAll([EffectType](const FStatusEffect& Effect)
	{
		return Effect.EffectType == EffectType;
	});
	OnStatusEffectRemoved.Broadcast(EffectType);
}

void UStatusEffectSystem::UpdateEffects(float DeltaTime)
{
	TickTimer += DeltaTime;

	for (int32 i = ActiveEffects.Num() - 1; i >= 0; --i)
	{
		FStatusEffect& Effect = ActiveEffects[i];

		// Update remaining time
		if (!Effect.bIsPermanent)
		{
			Effect.RemainingTime -= DeltaTime;

			if (Effect.RemainingTime <= 0.0f)
			{
				RemoveEffect(Effect.EffectID);
				continue;
			}
		}

		// Process ticks
		if (TickTimer >= Effect.TickInterval)
		{
			ProcessEffectTick(Effect, DeltaTime);
		}
	}

	if (TickTimer >= 1.0f)
	{
		TickTimer = 0.0f;
	}
}

FStatusEffect* UStatusEffectSystem::GetEffect(const FString& EffectID)
{
	return ActiveEffects.FindByPredicate([EffectID](const FStatusEffect& Effect)
	{
		return Effect.EffectID == EffectID;
	});
}

bool UStatusEffectSystem::HasEffect(EStatusEffectType EffectType) const
{
	return ActiveEffects.ContainsByPredicate([EffectType](const FStatusEffect& Effect)
	{
		return Effect.EffectType == EffectType;
	});
}

void UStatusEffectSystem::ClearAllEffects()
{
	ActiveEffects.Clear();
}

void UStatusEffectSystem::CleansPoison()
{
	RemoveEffectByType(EStatusEffectType::Poison);
}

float UStatusEffectSystem::GetTotalStatModifier(EStatusEffectType EffectType) const
{
	float TotalModifier = 0.0f;
	for (const FStatusEffect& Effect : ActiveEffects)
	{
		if (Effect.EffectType == EffectType)
		{
			TotalModifier += Effect.StatModifier * Effect.Stacks;
		}
	}
	return TotalModifier;
}

int32 UStatusEffectSystem::GetActiveEffectCount() const
{
	return ActiveEffects.Num();
}

bool UStatusEffectSystem::IsImmobilized() const
{
	return HasEffect(EStatusEffectType::Stun) || HasEffect(EStatusEffectType::Freeze);
}

bool UStatusEffectSystem::IsSlowed() const
{
	return HasEffect(EStatusEffectType::Freeze);
}

void UStatusEffectSystem::ProcessEffectTick(FStatusEffect& Effect, float DeltaTime)
{
	// Override in derived classes or in game code
	// This is where damage/healing from effects happens
}
