


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"
#include "Interaction/HighlightInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	auto* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EnhancedInputSubsystem);
	EnhancedInputSubsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CursorTrace();
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator ControllerRotation = GetControlRotation();
	const FRotator ControllerYaw(0.f, ControllerRotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(ControllerYaw).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(ControllerYaw).GetUnitAxis(EAxis::Y);

	if (auto* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	auto NewHighlightActor = TScriptInterface<IHighlightInterface>(CursorHit.GetActor());
	if (CurHighlightActor == NewHighlightActor)
	{
		return;
	}

	if (CurHighlightActor)
	{
		CurHighlightActor->UnhighlightActor();
	}

	CurHighlightActor = NewHighlightActor;

	if (CurHighlightActor)
	{
		NewHighlightActor->HighlightActor();
	}
}
