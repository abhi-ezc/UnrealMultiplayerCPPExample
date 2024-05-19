// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.h"
#include "Blueprint/UserWidget.h"
#include "CubeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CP_TARGET_API UCubeWidget : public UUserWidget
{
	GENERATED_BODY()

	class ABasePlayerController* BasePlayerController;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable,Category=Action)
	void OnMove(EMoveAxis axis);

	UFUNCTION(BlueprintCallable,Category=Action)
	void OnRotate(int rotateValue);

	UFUNCTION(BlueprintCallable,Category=Action)
	void OnScale(float scaleValue);
	
};
