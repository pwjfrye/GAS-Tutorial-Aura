


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (auto* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		check(GameplayEffectClass);

		auto EffectContextHandle = TargetAsc->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const auto EffectSpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
		TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
