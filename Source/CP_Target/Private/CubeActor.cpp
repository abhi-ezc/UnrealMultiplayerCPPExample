// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeActor.h"
#include "CubeWidget.h"

// Sets default values
ACubeActor::ACubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CubeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CubeWidget"));
	Mesh->SetupAttachment(RootComponent);
	CubeWidgetComponent->SetupAttachment(Mesh);
	CubeWidgetComponent->SetWidgetClass(UCubeWidget::StaticClass());
	SetReplicates(true);
    SetReplicateMovement(true);
	
	TransformHistory = TArray<FTransform>();
}

// Called when the game starts or when spawned
void ACubeActor::BeginPlay()
{
	Super::BeginPlay();
	InitialTransform = GetActorTransform();
}

// Called every frame
void ACubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeActor::CreateNewTransformHistory()
{
	FTransform currentTransform = GetActorTransform();
	TransformHistory.Add(currentTransform);
}

FTransform ACubeActor::UndoTransform()
{
	if(TransformHistory.Num()>0)
	{
		return TransformHistory.Pop();
	}
	else
	{
		return InitialTransform;
	}
}

void ACubeActor::ClearTransformHistory()
{
	TransformHistory.Empty();
}

void ACubeActor::OnMove(EMoveAxis axis)
{
	CreateNewTransformHistory();
	FVector actorLocation = GetActorLocation();
	switch (axis)
	{
	case EMoveAxis::XPos:
		actorLocation += FVector(MoveOffset,0,0);
		break;
	case EMoveAxis::XNeg:
		actorLocation += FVector(MoveOffset*-1,0,0);
		break;
	case EMoveAxis::ZPos:
		actorLocation += FVector(0,0,MoveOffset);
		break;
	case EMoveAxis::ZNeg:
		actorLocation += FVector(0,0,MoveOffset*-1);
		break;
	default:
			break;
	}

	PlayMoveTimeline(GetActorLocation(),actorLocation);

}

void ACubeActor::OnRotate(float rotationValue)
{
	CreateNewTransformHistory();
	FRotator rotation = GetActorRotation();
	rotation.Yaw+=rotationValue;

	PlayRotationTimeline(GetActorRotation(),rotation);
}

void ACubeActor::OnScale(float scaleValue)
{
	CreateNewTransformHistory();
	FVector scale = GetActorScale();
	scale.X += scaleValue;
	scale.Y += scaleValue;
	scale.Z += scaleValue;

	PlayScaleTimeline(GetActorScale(),scale);
}

void ACubeActor::OnResetTransform()
{
	ClearTransformHistory();
	PlayTransformTimeline(GetActorTransform(),InitialTransform);
}

void ACubeActor::OnUndoTransform()
{
	FTransform newTransform = UndoTransform();
	PlayTransformTimeline(GetActorTransform(),newTransform);
}


// Timeline Events Implemented in Blueprint
void ACubeActor::PlayMoveTimeline_Implementation(FVector currentLocation,FVector newLocation)
{
}

void ACubeActor::PlayRotationTimeline_Implementation(FRotator currentRotation, FRotator newRotation)
{
}

void ACubeActor::PlayScaleTimeline_Implementation(FVector currentScale, FVector newScale)
{
}

void ACubeActor::PlayTransformTimeline_Implementation(FTransform currentTransform, FTransform newTransform)
{
}


void ACubeActor::UpdateWidgetControl_Implementation(EWidgetControl control)
{
}

