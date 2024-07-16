


#include "AbilitySystem/AuraEffectApplierComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystem/AuraLevelComponent.h"

UAuraEffectApplierComponent::UAuraEffectApplierComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAuraEffectApplierComponent::BeginPlay()
{
	Super::BeginPlay();

	check(GameplayEffectClass);
}

bool UAuraEffectApplierComponent::TryApplyEffectToTarget(AActor* TargetActor)
{
	auto* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetActor == nullptr)
	{
		return false;
	}

	auto Level = 1.0f;
	if (const auto* LevelComponent = GetOwner()->FindComponentByClass<UAuraLevelComponent>())
	{
		Level = LevelComponent->GetLevel();
	}

	auto EffectContextHandle = TargetAsc->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const auto EffectSpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);
	const auto ActiveEffectHandle = TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	if (EffectSpecHandle.Data.Get()->Def->DurationPolicy != EGameplayEffectDurationType::Instant)
	{
		if (!ActiveEffectHandle.IsValid())
		{
			return false;
		}

		ActiveEffectsMap.Add(ActiveEffectHandle, TargetActor);
	}

	return true;
}

void UAuraEffectApplierComponent::RemoveEffectFromTarget(AActor* TargetActor)
{
	if (auto* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		for (auto It = ActiveEffectsMap.CreateIterator(); It; ++It)
		{
			const auto& KVP = *It;
			if (KVP.Value == TargetActor)
			{
				TargetAsc->RemoveActiveGameplayEffect(KVP.Key, 1);
				It.RemoveCurrent();
			}
		}
	}
}
