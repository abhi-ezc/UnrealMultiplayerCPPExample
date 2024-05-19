// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.generated.h"

UENUM(BlueprintType)
enum EWidgetControl
{
	NONE UMETA(DisplayName="None"),
	MOVE UMETA(DisplayName="Move"),
	ROTATION UMETA(DisplayName="Rotation"),
	SCALE UMETA(DisplayName="Scale")
};

UENUM(BlueprintType)
enum EMoveAxis
{
	XPos UMETA(DisplayName="Positive X"),
	XNeg UMETA(DisplayName="Negative X"),
	ZPos UMETA(DisplayName="Positive Z"),
	ZNeg UMETA(DisplayName="Negative Z"),
};
