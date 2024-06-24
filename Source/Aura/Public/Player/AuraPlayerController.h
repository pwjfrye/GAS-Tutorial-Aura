

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class IHighlightInterface;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	TScriptInterface<IHighlightInterface> PrevHighlightActor;
	TScriptInterface<IHighlightInterface> CurHighlightActor;
};
