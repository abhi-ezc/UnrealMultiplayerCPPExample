// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGM.h"
#include "BasePlayerController.h"
#include "BaseGS.h"

ABaseGM::ABaseGM()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ABasePlayerController::StaticClass();
	GameStateClass = ABaseGS::StaticClass();
}