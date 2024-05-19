// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGS.h"
#include "BaseHUDWidget.h"
#include "GameFramework/PlayerController.h"
#include "BasePawn.h"
#include "CubeActor.h"
#include "CustomTypes.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CP_TARGET_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	TSubclassOf<ABasePawn> PawnClass = ABasePawn::StaticClass(); // Spawn Class
	
	UPROPERTY()
	ABasePawn* PlayerPawn = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Widget,meta=(AllowPrivateAccess=true))
	UBaseHUDWidget* BaseHUDWidget;

	TSubclassOf<UBaseHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=GameState,meta=(AllowPrivateAccess=true))
	ABaseGS* CurrentGameState;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=WidgetControl,meta=(AllowPrivateAccess=true))
	TEnumAsByte<EWidgetControl> WidgetControl = EWidgetControl::NONE;
	
	ABasePlayerController();
public:
	
	
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnCubeActor();

	UFUNCTION(BlueprintCallable,Client,Reliable)
	void CreateHUDWidget();

	UFUNCTION(BlueprintCallable)
	void OnCubeMoveAction(EWidgetControl control,EMoveAxis axis);
	
	UFUNCTION(BlueprintCallable,Client,Reliable)
	void OnCubeAction(EWidgetControl control,float actionValue);

	UFUNCTION()
	void SetWidgetControl(EWidgetControl newWidgetControl);

	UFUNCTION()
	void UndoCubeTransform();
	UFUNCTION()
	void ResetCubeTransform();
	UFUNCTION()
	void DestroyCube();

	UFUNCTION()
	EWidgetControl GetCurrentWidgetControl() const;

private:
	UFUNCTION(BlueprintAuthorityOnly, Server, Reliable)
	void Server_SpawnPlayerPawn();

	UFUNCTION(BlueprintAuthorityOnly, Server, Reliable)
	void Server_SpawnCubeActor();

	UFUNCTION(BlueprintAuthorityOnly,Server,Reliable)
	void Server_OnCubeMoveAction(EMoveAxis axis);

	UFUNCTION(BlueprintAuthorityOnly,Server,Reliable)
	void Server_OnCubeAction(EWidgetControl control,float actionValue);

	UFUNCTION(Server,Reliable)
	void Server_UndoCubeTransform();
	UFUNCTION(Server,Reliable)
	void Server_ResetCubeTransform();
	UFUNCTION(Server,Reliable)
	void Server_DestroyCube();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
