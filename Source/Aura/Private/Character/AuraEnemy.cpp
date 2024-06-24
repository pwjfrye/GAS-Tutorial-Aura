


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	bIsHighlighted = true;
}

void AAuraEnemy::UnhighlightActor()
{
	bIsHighlighted = false;
}

AAuraEnemy::AAuraEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Move this to "HighlightComponent"
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AAuraEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO: Remove debug visualization
	if (bIsHighlighted)
		DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 12, FColor::Red);
}

