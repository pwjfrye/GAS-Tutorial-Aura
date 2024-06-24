


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	// TODO: Move this to "HighlightComponent"
	GetMesh()->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnhighlightActor()
{
	// TODO: Move this to "HighlightComponent"
	GetMesh()->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Move this to "HighlightComponent"
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(250);
}

