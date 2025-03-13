// Copyright Virtualis Terra


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (ASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle GameplayEffectContextHandle = ASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, GameplayEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
	
}

