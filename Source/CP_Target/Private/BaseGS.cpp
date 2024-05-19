// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGS.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

ABaseGS::ABaseGS()
{
	const ConstructorHelpers::FClassFinder<ACubeActor> BP_CUBE(TEXT("Blueprint'/Game/Blueprints/Actors/BP_Cube.BP_Cube_C'"));
	CubeActorClass = BP_CUBE.Class;
}

FTransform ABaseGS::GetRandomSpawnPosition() const
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(),PlayerStarts);
	const int32 randomIndex = UKismetMathLibrary::RandomInteger(PlayerStarts.Num()-1);
	return PlayerStarts[randomIndex]->GetActorTransform();
}

void ABaseGS::Server_SpawnCubeActor_Implementation()
{
	if( CubeActor==nullptr && bIsCubeActorSpawn == false)
	{
		CubeActor = GetWorld()->SpawnActor<ACubeActor>(CubeActorClass);
		MARK_PROPERTY_DIRTY_FROM_NAME(ABaseGS,CubeActor,this);
		UpdateIsCubeActorValid(true);
	}
}

bool ABaseGS::IsCubeActorValid()
{
	return bIsCubeActorSpawn;
}

void ABaseGS::UpdateIsCubeActorValid(bool newCubeActorValid)
{
	if(newCubeActorValid!=bIsCubeActorSpawn)
	{
		bIsCubeActorSpawn = newCubeActorValid;
		MARK_PROPERTY_DIRTY_FROM_NAME(ABaseGS,bIsCubeActorSpawn,this);
	}
}

void ABaseGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased=true;
	
	DOREPLIFETIME_WITH_PARAMS_FAST(ABaseGS,bIsCubeActorSpawn,SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ABaseGS,CubeActor,SharedParams);
}

void ABaseGS::Server_OnMoveCube_Implementation(EMoveAxis axis)
{
	if(CubeActor!=nullptr)
	{
		CubeActor->OnMove(axis);
	}
}

void ABaseGS::Server_OnOtherCubeActions_Implementation(EWidgetControl control, float actionValue)
{
	if(CubeActor==nullptr)
	{
		return;
	}
	
	switch(control)
	{
	case EWidgetControl::SCALE:
		CubeActor->OnScale(actionValue);
		break;
		
	case EWidgetControl::ROTATION:
		CubeActor->OnRotate(actionValue);
		break;
		
	default:
		break;
	}
}

void ABaseGS::Client_UpdateCubeWidgetControl_Implementation(EWidgetControl control)
{
	if(CubeActor==nullptr)
	{
		return;
	}
	CubeActor->UpdateWidgetControl(control);
}

void ABaseGS::Server_OnDestroyCube_Implementation()
{
	CubeActor->Destroy(true);
	CubeActor = nullptr;
	MARK_PROPERTY_DIRTY_FROM_NAME(ABaseGS,CubeActor,this);
	UpdateIsCubeActorValid(false);
}

void ABaseGS::Server_OnResetCubeTransform_Implementation()
{
	CubeActor->OnResetTransform();
}

void ABaseGS::Server_OnUndoCubeTransform_Implementation()
{
	CubeActor->OnUndoTransform();
}



