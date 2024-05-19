// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUDWidget.h"

#include "BasePlayerController.h"

bool UBaseHUDWidget::Initialize(){
	Super::Initialize();
	BasePlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
	BaseGameState = Cast<ABaseGS>(GetWorld()->GetGameState());
	return true;
}

void UBaseHUDWidget::SpawnCube()
{
	BasePlayerController->SpawnCubeActor();
}

void UBaseHUDWidget::UpdateWidgetControl(EWidgetControl control)
{
	BasePlayerController->SetWidgetControl(control);
}

void UBaseHUDWidget::UndoCubeTransform()
{
	BasePlayerController->UndoCubeTransform();
}
void UBaseHUDWidget::ResetCubeTransform()
{
	BasePlayerController->ResetCubeTransform();
}

void UBaseHUDWidget::DestroyCube()
{
	BasePlayerController->DestroyCube();
}

void UBaseHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	ActiveWidgetControl(BasePlayerController->GetCurrentWidgetControl());
}

void UBaseHUDWidget::ActiveWidgetControl_Implementation(EWidgetControl control)
{
}



