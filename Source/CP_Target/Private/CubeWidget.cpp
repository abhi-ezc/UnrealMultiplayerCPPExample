// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeWidget.h"

#include "BasePlayerController.h"

void UCubeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BasePlayerController = Cast<ABasePlayerController>(GetOwningPlayer());
}


void UCubeWidget::OnMove(EMoveAxis axis)
{
	BasePlayerController->OnCubeMoveAction(EWidgetControl::MOVE,axis);
}

void UCubeWidget::OnRotate(int rotateValue)
{
	BasePlayerController->OnCubeAction(EWidgetControl::ROTATION,rotateValue);
}

void UCubeWidget::OnScale(float scaleValue)
{
	BasePlayerController->OnCubeAction(EWidgetControl::SCALE,scaleValue);
}
