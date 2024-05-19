// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

UCLASS()
class CP_TARGET_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Mesh,meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Widget,meta=(AllowPrivateAccess=true))
	UWidgetComponent* CubeWidgetComponent;

	FTransform InitialTransform;
	TArray<FTransform> TransformHistory;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inputs|Move",meta=(AllowPrivateAccess=true))
	int32 MoveOffset = 10;
	
public:	
	// Sets default values for this actor's properties
	ACubeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CreateNewTransformHistory();
	
	UFUNCTION()
	FTransform UndoTransform();
	
	UFUNCTION()
	void ClearTransformHistory();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnMove(EMoveAxis axis);

	UFUNCTION()
	void OnRotate(float rotationValue);

	UFUNCTION()
	void OnScale(float scaleValue);

	UFUNCTION(BlueprintNativeEvent)
	void PlayMoveTimeline(FVector currentLocation,FVector newLocation);

	UFUNCTION(BlueprintNativeEvent)
	void PlayRotationTimeline(FRotator currentRotation,FRotator newRotation);

	UFUNCTION(BlueprintNativeEvent)
	void PlayScaleTimeline(FVector currentScale,FVector newScale);

	UFUNCTION(BlueprintNativeEvent)
	void PlayTransformTimeline(FTransform currentTransform,FTransform newTransform);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateWidgetControl(EWidgetControl control);

	UFUNCTION()
	void OnUndoTransform();

	UFUNCTION()
	void OnResetTransform();
};
