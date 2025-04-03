// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_AirHockey.h"
#include "CameraController.h"
#include "ControllerC2P.h"

void AGM_AirHockey::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	Side++;
	ControllersRef.AddUnique(NewPlayer);
	AControllerC2P* PlayerController = Cast<AControllerC2P>(NewPlayer);
}
