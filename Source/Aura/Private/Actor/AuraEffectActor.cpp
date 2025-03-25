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

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const FEffectConfiguration& GamePlayEffect)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (ASC == nullptr) return;

	check(GamePlayEffect.GameplayEffectClass);
	FGameplayEffectContextHandle GameplayEffectContextHandle = ASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = ASC->MakeOutgoingSpec(GamePlayEffect.GameplayEffectClass, ActorLevel, GameplayEffectContextHandle);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	// Check if we applied an infinite effect
	if (GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite
		&& GamePlayEffect.EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// Cache the Handle and the Target Actor in a Map
		ActiveInfiniteGameplayEffectHandlesMap.Add(ActiveGameplayEffectHandle, ASC);
	}
}

void AAuraEffectActor::RemoveEffectsFromTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (ASC == nullptr) return;
	
	check(GameplayEffectClass);
	
	ASC->RemoveActiveGameplayEffectBySourceEffect(GameplayEffectClass, nullptr);
}


void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{	
	// Instant Effects
	EvaluateEffectsForApplication(TargetActor, InstantEffects, EEffectApplicationPolicy::ApplyOnOverlap);

	// Duration Effects
	EvaluateEffectsForApplication(TargetActor, DurationEffects, EEffectApplicationPolicy::ApplyOnOverlap);

	// Infinite Effects
	EvaluateEffectsForApplication(TargetActor, InfiniteEffects, EEffectApplicationPolicy::ApplyOnOverlap);

	if (bDestroyOnEffectApplication)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	// Instant Effects
	EvaluateEffectsForApplication(TargetActor, InstantEffects, EEffectApplicationPolicy::ApplyOnEndOverlap);

	// Duration Effects
	EvaluateEffectsForApplication(TargetActor, DurationEffects, EEffectApplicationPolicy::ApplyOnEndOverlap);

	//// Infinite Effects
	// Apply
	EvaluateEffectsForApplication(TargetActor, InfiniteEffects, EEffectApplicationPolicy::ApplyOnEndOverlap);
	// Remove
	EvaluateEffectsForRemoval(TargetActor, InfiniteEffects, EEffectRemovalPolicy::RemoveOnEndOverlap);

}

void AAuraEffectActor::EvaluateEffectsForApplication(AActor* TargetActor, const TArray<FEffectConfiguration>& Effects, const EEffectApplicationPolicy& ApplicationPolicy)
{
	for (auto& Effect : Effects)
	{
		if (Effect.EffectApplicationPolicy == ApplicationPolicy)
		{
			ApplyEffectToTarget(TargetActor, Effect);
		}
	}
}

void AAuraEffectActor::EvaluateEffectsForRemoval(AActor* TargetActor, const TArray<FEffectConfiguration>& Effects,	const EEffectRemovalPolicy& RemovalPolicy)
{
	// We want to track if we actually removed an effect for later
	bool bWasGameplayEffectRemoved = false;

	// Array of removed effect handles so we can take them out of the map
	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandlesRemoved;

	// Loop though all the effects
	for (auto& Effect : Effects)
	{
		// Check if one of them has the removal policy we are checking
		if (Effect.EffectRemovalPolicy == RemovalPolicy)
		{
			// Check if the Target Actor has an Ability System Component
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			if (!IsValid(ASC)) return;

			// Loop though our map of applied Infinite Effects
			for (auto HandlePair : ActiveInfiniteGameplayEffectHandlesMap)
			{
				// If the TargetActors AbilitySystemComponent is in the map
				if (ASC == HandlePair.Value)
				{
					// Remove the gameplay effect by handle
					ASC->RemoveActiveGameplayEffect(HandlePair.Key);
					// Add it to the array of handles to remove
					// Doing the remove at this time will likely mess up how we are looping this map
					ActiveGameplayEffectHandlesRemoved.Add(HandlePair.Key);

					bWasGameplayEffectRemoved = true;
				}
			}
		}
	}

	// Remove elements in the Map for Handles that we removed
	for (auto& Handle : ActiveGameplayEffectHandlesRemoved)
	{
		ActiveInfiniteGameplayEffectHandlesMap.FindAndRemoveChecked(Handle);
	}

	// If we actually removed an effect and this effect class is marked to be destroyed when an effect is removed
	if (bDestroyOnEffectRemoval && bWasGameplayEffectRemoved)
	{
		// Then we will destroy
		Destroy();
	}
}

