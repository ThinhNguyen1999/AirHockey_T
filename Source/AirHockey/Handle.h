// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Handle.generated.h"

UCLASS()
class AIRHOCKEY_API AHandle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HandleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* HandleMesh;

	FVector GetHandleVelocity() const;


private:
	FVector HandleVelocity;
};
