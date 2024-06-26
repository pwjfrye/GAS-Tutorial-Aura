


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	auto* MyCharacterMovement = GetCharacterMovement();
	MyCharacterMovement->bOrientRotationToMovement = true;
	MyCharacterMovement->RotationRate = FRotator(0.f, 400.f, 0.f);
	MyCharacterMovement->bConstrainToPlane = true;
	MyCharacterMovement->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init on server
	InitAbilitySystem();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init on client
	InitAbilitySystem();
}

void AAuraCharacter::InitAbilitySystem()
{
	auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	if (!AuraPlayerState)
	{
		return;
	}

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	check(AbilitySystemComponent);
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	AttributeSet = AuraPlayerState->GetAttributeSet();

	// Init HUD
	if (auto* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (auto* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
