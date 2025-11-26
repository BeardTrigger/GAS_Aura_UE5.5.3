// Copyright Virtualis Terra


#include "Character/EnemyBase.h"
#include "AbilitySystem/AuraAttributeSet.h"

AEnemyBase::AEnemyBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(STENCIL_VALUE);
	Weapon->SetCustomDepthStencilValue(STENCIL_VALUE);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AEnemyBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
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
