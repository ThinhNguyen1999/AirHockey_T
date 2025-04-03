// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_AirHockey.generated.h"

/**
 * 
 */
UCLASS()
class AIRHOCKEY_API AGM_AirHockey : public AGameModeBase
{
	GENERATED_BODY()

	virtual void OnPostLogin(AController* NewPlayer) override;

	UPROPERTY()
	TArray<AController*> ControllersRef;
public:

private:

	UPROPERTY()
	FVector PawnLocation1 = {1500,1152,32};

	UPROPERTY()
	FVector PawnLocation2 = {1500,2152,32};
	UPROPERTY()
	int Side = -1;
};
