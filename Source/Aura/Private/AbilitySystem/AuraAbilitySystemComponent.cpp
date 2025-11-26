// Copyright Virtualis Terra


#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::GameplayEffectAppliedCallback);
}

void UAuraAbilitySystemComponent::GameplayEffectAppliedCallback(UAbilitySystemComponent* ASCPointer, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle)
{
	FGameplayTagContainer TagContainer;
	GESpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
}
