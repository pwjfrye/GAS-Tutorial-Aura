

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraLevelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UAuraLevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAuraLevelComponent();

	UFUNCTION(BlueprintCallable)
	float GetLevel() const { return Level; }

private:
	UPROPERTY(EditAnywhere)
	float Level;
};
