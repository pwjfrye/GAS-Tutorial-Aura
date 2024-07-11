

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "AuraAbilitySystemActor.generated.h"

UCLASS()
class AURA_API AAuraAbilitySystemActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraAbilitySystemActor();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

};
