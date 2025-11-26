// Copyright Virtualis Terra


#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::GameplayEffectAppliedCallback);
}

void UAuraAbilitySystemComponent::GameplayEffectAppliedCallback(UAbilitySystemComponent* ASCPointer, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Blue, FString::Printf(TEXT("Effect Applied!")));
}
