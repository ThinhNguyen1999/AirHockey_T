


#include "ScoreArea.h"

#include "Components/BoxComponent.h"


// Sets default values
AScoreArea::AScoreArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AreaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Area Mesh"));
	SetRootComponent(AreaMesh);

	AreaCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall Collision"));
	AreaCollision->SetupAttachment(AreaMesh);
}

// Called when the game starts or when spawned
void AScoreArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

