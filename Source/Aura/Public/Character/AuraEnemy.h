

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

	AAuraEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//~ Begin IHighlightInterface Interface.
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	//~ End IHighlightInterface Interface.

private:
	bool bIsHighlighted;
};
