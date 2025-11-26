// Copyright Virtualis Terra

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// Delegate Declarations
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer /* Asset Tag Container */)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();
	
	FEffectAssetTags EffectAssetTags;
	
protected:
	void GameplayEffectAppliedCallback(UAbilitySystemComponent* ASCPointer, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle);
};
