


#include "Actor/AuraAbilitySystemActor.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraAbilitySystemActor::AAuraAbilitySystemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	// TODO: Should these be set only on the server?
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AAuraAbilitySystemActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
