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
	
	for (const FGameplayTag& Tag : TagContainer)
	{
		// Broadcast the tag to the widget controller
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, Msg);
	}
}
