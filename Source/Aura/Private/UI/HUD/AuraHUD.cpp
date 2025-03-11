// Copyright Virtualis Terra


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetController(WidgetControllerParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,	UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized. Please assign in HUDBP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized. Please assign in HUDBP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	
	Widget->AddToViewport();
}
