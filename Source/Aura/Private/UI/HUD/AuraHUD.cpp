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
		OverlayWidgetController->BindCallbacksToDependencies();
		
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

	// Bind Widget BP events here
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	// Bind Callback for UI Messages Tags
	WidgetController->MessageWidgetRowDelegate.AddDynamic(this, &AAuraHUD::HandleUIMessagesTag);
	
	
	Widget->AddToViewport();
}

void AAuraHUD::HandleUIMessagesTag(const FUIWidgetRow& Row)
{		
	// Broadcast the tag to the widget controller
	// const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Row.Msg.ToString());
	// GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, Msg);
}
