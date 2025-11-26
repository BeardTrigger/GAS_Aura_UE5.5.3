// Copyright Virtualis Terra

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();
	
protected:
	void GameplayEffectAppliedCallback(UAbilitySystemComponent* ASCPointer, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle);
};
