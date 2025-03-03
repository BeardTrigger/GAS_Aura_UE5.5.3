// Copyright Virtualis Terra


#include "Character/EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(STENCIL_VALUE);
	Weapon->SetCustomDepthStencilValue(STENCIL_VALUE);
}

void AEnemyBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AEnemyBase::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);	
	Weapon->SetRenderCustomDepth(false);
}
