// Copyright Virtualis Terra


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(200.f);
	InitMana(100.f);
	InitMaxMana(200.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

// Use this override to clamp the values of Attributes that are being changed
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// Super::PreAttributeChange(Attribute, NewValue);
	//
	// // Clamp the Health to the Max Health Value
	// if (Attribute == GetHealthAttribute())
	// {
	// 	NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	// }
	//
	// // Clamp the Mana to the Max Mana Value
	// if (Attribute == GetManaAttribute())
	// {
	// 	NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	// }
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);
}


inline void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,	FEffectProperties& EffectProperties) const
{
	
	// Source is the causer of the effect
	// Target is the target of the effect (owner of this attribute set)

	// Just showing all the different data we can access in this function
	const FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.GameplayEffectHandle = ContextHandle;
	
	UAbilitySystemComponent* ASC = ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(ASC) && ASC->AbilityActorInfo.IsValid() && ASC->AbilityActorInfo->AvatarActor.IsValid())
	{		
		AActor* SourceAvatarActor = ASC->AbilityActorInfo->AvatarActor.Get();		
		AController* SourceController = ASC->AbilityActorInfo->PlayerController.Get();
		
		if (SourceController == nullptr && SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceAvatarActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		if (SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
			EffectProperties.Source.EEffectPartProperties(ASC, SourceAvatarActor, SourceController, SourceCharacter);
		}
	}
	

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{		
		AActor* TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();		
		AController* TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();		
		ACharacter* TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
		
		EffectProperties.Target.EEffectPartProperties(TargetASC, TargetAvatarActor, TargetController, TargetCharacter);
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
