

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HighlightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AURA_API UHighlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHighlightComponent();

protected:
	virtual void BeginPlay() override;

public:
	void HighlightActor();
	void UnhighlightActor();

private:
	UPROPERTY()
	TArray<UPrimitiveComponent*> Meshes;
};
