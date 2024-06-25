


#include "Interaction/HighlightComponent.h"

#include "Aura/Aura.h"

UHighlightComponent::UHighlightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetComponents(Meshes);

	for (auto* Mesh : Meshes)
	{
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void UHighlightComponent::HighlightActor()
{
	for (auto* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void UHighlightComponent::UnhighlightActor()
{
	for (auto* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}