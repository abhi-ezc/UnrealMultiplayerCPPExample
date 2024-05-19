// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CP_TARGET_API UBaseHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=PlayerController)
	class ABasePlayerController* BasePlayerController;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=GameState)
	class ABaseGS* BaseGameState;

	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnCube();

	UFUNCTION(BlueprintCallable)
	void UpdateWidgetControl(EWidgetControl control);

	UFUNCTION(BlueprintCallable)
	void UndoCubeTransform();
	
	UFUNCTION(BlueprintCallable)
	void ResetCubeTransform();

	UFUNCTION(BlueprintCallable)
	void DestroyCube();

	UFUNCTION(BlueprintNativeEvent)
	void ActiveWidgetControl(EWidgetControl control);
};
