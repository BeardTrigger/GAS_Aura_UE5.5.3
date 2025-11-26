// Copyright Virtualis Terra

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyBase : public ACharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	
	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo() override;
};
