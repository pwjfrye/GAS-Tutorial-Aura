


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
