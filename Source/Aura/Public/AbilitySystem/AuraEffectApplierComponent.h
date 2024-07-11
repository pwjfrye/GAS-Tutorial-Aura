

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "AuraEffectApplierComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UAuraEffectApplierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAuraEffectApplierComponent();

	UFUNCTION(BlueprintCallable)
	bool TryApplyEffectToTarget(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void RemoveEffectFromTarget(AActor* TargetActor);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, AActor*> ActiveEffectsMap;
};
