// Copyright Virtualis Terra


#include "Character/EnemyBase.h"

void AEnemyBase::HighlightActor()
{
	bHighlighted = true;
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(50, 50, 50), FColor::Green, false, 0.5f);
}

void AEnemyBase::UnHighlightActor()
{
	bHighlighted = false;
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(50, 50, 50), FColor::Red, false, 0.5f);
}
