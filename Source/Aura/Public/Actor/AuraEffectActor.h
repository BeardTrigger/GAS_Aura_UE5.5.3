// Copyright Virtualis Terra

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply,
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove,
};

USTRUCT(Blueprintable)
struct FEffectConfiguration
{
	GENERATED_BODY()
	// The Gameplay Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	// Application Policy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	// Removal Policy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	
protected:
	virtual void BeginPlay() override;

	void ApplyEffectToTarget(AActor* TargetActor, const FEffectConfiguration& GamePlayEffect);
	void RemoveEffectsFromTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectApplication = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;
	
	// Instant Effects
	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TArray<FEffectConfiguration> InstantEffects;

	// Duration Effects
	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TArray<FEffectConfiguration> DurationEffects;
	
	// Infinite Effects
	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TArray<FEffectConfiguration> InfiniteEffects;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveInfiniteGameplayEffectHandlesMap;

	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	float ActorLevel = 1.0f;
	
private:

	void EvaluateEffectsForApplication(AActor* TargetActor, const TArray<FEffectConfiguration>& Effects, const EEffectApplicationPolicy& ApplicationPolicy);
	void EvaluateEffectsForRemoval(AActor* TargetActor, const TArray<FEffectConfiguration>& Effects, const EEffectRemovalPolicy& RemovalPolicy);
};
