// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "BaseGS.h"
#include "BaseHUDWidget.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

ABasePlayerController::ABasePlayerController()
{
	const ConstructorHelpers::FClassFinder<UBaseHUDWidget> BP_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/Widgets/WB_HUDWidget.WB_HUDWidget_C'"));
	HUDWidgetClass = BP_HUD.Class;
}
void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	Server_SpawnPlayerPawn();

	CurrentGameState = Cast<ABaseGS>(GetWorld()->GetGameState());
}

// Spawning and Possessing Player Pawn Class
void ABasePlayerController::Server_SpawnPlayerPawn_Implementation() {
	const FTransform spawnTransform = Cast<ABaseGS>(GetWorld()->GetGameState())->GetRandomSpawnPosition();
	const FActorSpawnParameters actorSpawnParameters = FActorSpawnParameters();
	AActor* spawnedActor = GetWorld()->SpawnActor(PawnClass.Get(), &spawnTransform,actorSpawnParameters);
	PlayerPawn = Cast<ABasePawn>(spawnedActor);
	Possess(PlayerPawn);
}

void ABasePlayerController::CreateHUDWidget_Implementation()
{
	BaseHUDWidget = CreateWidget<UBaseHUDWidget>(this,HUDWidgetClass,FName("Base HUD"));
	if(BaseHUDWidget!=nullptr)
	{
		BaseHUDWidget->AddToViewport(0);
		FInputModeGameAndUI InputModeGameAndUI;
		InputModeGameAndUI.SetHideCursorDuringCapture(false);
		SetInputMode(InputModeGameAndUI);
		SetShowMouseCursor(true);
	}
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CreateHUDWidget();
}

void ABasePlayerController::SpawnCubeActor()
{
	Server_SpawnCubeActor();
}
void ABasePlayerController::Server_SpawnCubeActor_Implementation()
{
		CurrentGameState->Server_SpawnCubeActor();
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABasePlayerController::OnCubeMoveAction(EWidgetControl control,EMoveAxis axis)
{
	Server_OnCubeMoveAction(axis);
}

void ABasePlayerController::OnCubeAction_Implementation(EWidgetControl control,float actionValue)
{
	Server_OnCubeAction(control,actionValue);
}

void ABasePlayerController::Server_OnCubeMoveAction_Implementation(EMoveAxis axis)
{
	CurrentGameState->Server_OnMoveCube(axis);
}
void ABasePlayerController::Server_OnCubeAction_Implementation(EWidgetControl control,float actionValue)
{
	CurrentGameState->Server_OnOtherCubeActions(control,actionValue);
}

void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
}

void ABasePlayerController::SetWidgetControl(EWidgetControl newWidgetControl)
{
	if(WidgetControl!=newWidgetControl)
	{
		WidgetControl = newWidgetControl;
	}
	else
	{
		WidgetControl = EWidgetControl::NONE;
	}
	CurrentGameState->Client_UpdateCubeWidgetControl(WidgetControl);
}

void ABasePlayerController::UndoCubeTransform()
{
	Server_UndoCubeTransform();
}

void ABasePlayerController::Server_UndoCubeTransform_Implementation()
{
	CurrentGameState->Server_OnUndoCubeTransform();
}

void ABasePlayerController::ResetCubeTransform()
{
	Server_ResetCubeTransform();
}

void ABasePlayerController::Server_ResetCubeTransform_Implementation()
{
	CurrentGameState->Server_OnResetCubeTransform();
}

void ABasePlayerController::DestroyCube()
{
	Server_DestroyCube();
}

void ABasePlayerController::Server_DestroyCube_Implementation()
{
	CurrentGameState->Server_OnDestroyCube();
	SetWidgetControl(EWidgetControl::NONE);
}

EWidgetControl ABasePlayerController::GetCurrentWidgetControl() const
{
	return WidgetControl;
}