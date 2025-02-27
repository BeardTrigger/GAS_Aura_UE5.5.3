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
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
};
