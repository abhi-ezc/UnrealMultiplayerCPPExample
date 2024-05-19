// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeActor.h"
#include "CustomTypes.h"
#include "GameFramework/GameState.h"
#include "BaseGS.generated.h"

/**
 * 
 */
UCLASS()
class CP_TARGET_API ABaseGS : public AGameState
{
	GENERATED_BODY()
	TSubclassOf<ACubeActor> CubeActorClass; // Cube Actor

	UPROPERTY(VisibleAnywhere,Replicated,BlueprintReadOnly,Category=Cube,meta=(AllowPrivateAccess=true))
	bool bIsCubeActorSpawn = false;

	UPROPERTY(VisibleAnywhere,Replicated, BlueprintReadOnly,Category=Cube,meta=(AllowPrivateAccess=true))
	ACubeActor* CubeActor;
	
public:
	ABaseGS();
	FTransform GetRandomSpawnPosition() const;

	UFUNCTION(BlueprintCallable)
	bool IsCubeActorValid();

	UFUNCTION(BlueprintCallable)
	void UpdateIsCubeActorValid(bool newCubeActorValid);

	UFUNCTION(Server,Reliable)
	void Server_SpawnCubeActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintAuthorityOnly,Server,Reliable)
	void Server_OnMoveCube(EMoveAxis axis);

	UFUNCTION(BlueprintAuthorityOnly,Server,Reliable)
	void Server_OnOtherCubeActions(EWidgetControl control,float actionValue);

	UFUNCTION(Client,Reliable)
	void Client_UpdateCubeWidgetControl(EWidgetControl control);

	UFUNCTION(Server,Reliable)
	void Server_OnUndoCubeTransform();
	
	UFUNCTION(Server,Reliable)
	void Server_OnResetCubeTransform();
	
	UFUNCTION(Server,Reliable)
	void Server_OnDestroyCube();
};
