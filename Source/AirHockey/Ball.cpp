// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Wall.h"
#include "ScoreArea.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/KismetSystemLibrary.h>

#include "Handle.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BallCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Ball Collision"));
	SetRootComponent(BallCollision);

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	BallMesh->SetupAttachment(BallCollision);

	bReplicates = true;

}
 
// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	//set lai ngẫu nhiên XYZ của vector di chuyển
	// Quyết định ngẫu nhiên xem vận tốc nên là + hay -

	Move.X = FMath::FRandRange(0.f,1.f) < 0.5f ? -1.f : 1.f;
	Move.Y = FMath::FRandRange(0.f,1.f) < 0.5f ? -1.f : 1.f;

	Move.X *= 10.f;
	Move.Y *= 12.f;
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// khai báo location của actor và di chuyển actor đến vị
	FVector Location = GetActorLocation();
	Location += Move;
	SetActorLocation(Location);

	//ve 1 duong line trace truoc mat 5cm
	FHitResult Hit;
	const FVector& TraceStar = Location; // diem dau can trace
	const FVector& TraceDirection = FVector(0.0f, 0.0f, 0.0f);  // diem cuoi can trace
	const FVector& TraceEnd = TraceStar + TraceDirection; // do dai trace
	const float& Radius = 50.0f; // Ban kinh cua sphere trace

	FCollisionQueryParams QueryParams; // define the collision
	QueryParams.AddIgnoredActor(this);  // add Actors to ignore, in this case this Actor

	//tao sphere trace thì dùng SweepSingleByChannel
	GetWorld()->SweepSingleByChannel(Hit, TraceStar, TraceEnd, FQuat::Identity, 
		TraceChannelProperty, FCollisionShape::MakeSphere(Radius), QueryParams);

	
	DrawDebugSphere(GetWorld(), Location, Radius, 8, FColor::Red, false, 2.0f);
	DrawDebugLine(GetWorld(), TraceStar, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStar.ToCompactString(), *TraceEnd.ToCompactString());

	if  (Hit.GetActor() && PreActor!= Hit.GetActor())
	{
		if (Cast<AHandle>(Hit.GetActor()))
		{
			AHandle* Handle = Cast<AHandle>(Hit.GetActor());
			if (Handle)
			{
				FVector HandleVelocity = Handle->GetHandleVelocity();
				float HandleSpeed = HandleVelocity.Size();
				float OrigialZ = Move.Z;


				// thay đổi speed của trái banh.
				if (HandleSpeed >1800.0f)
				{
					HandleSpeed =1500.0f;
					HandleSpeed = HandleSpeed/100;
					FVector normal = GetActorLocation() - Hit.GetActor()->GetActorLocation();
					normal.Z = Move.Z;
					Move = UKismetMathLibrary::MirrorVectorByNormal(Move,normal);

					Move = Move* 0.8 + HandleSpeed;
					Move.Z = OrigialZ;
					UE_LOG(LogTemp, Warning, TEXT("Handle Speed: %f"), HandleSpeed);
				}
				else
				{
					FVector normal = GetActorLocation() - Hit.GetActor()->GetActorLocation();
					Move = UKismetMathLibrary::MirrorVectorByNormal(Move,normal);
					Move = Move* 0.8;
				}
			}
		}
		else if (Cast<AWall>(Hit.GetActor()))
		{
			Move.X *=-1;
		}
		else if (Cast<AScoreArea>(Hit.GetActor()))
		{
			Move.Y *= -1;
		}
		PreActor = Hit.GetActor();
	}
	
}

void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABall, Move);
}


