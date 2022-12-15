// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerPawn.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	compBox->SetBoxExtent(FVector(50));
	SetRootComponent(compBox);

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//랜덤한 값을 뽑는다.(1 ~ 100)
	int32 rand = FMath::RandRange(1, 100);

	//만약에 랜덤한 값이 50보다 작으면(50%)
	if (rand < 100)
	{
		//1. 플레이어를 찾자
		AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
		//2. 플레이어를 향하는 방향을 구하자. (타겟 - 나)
		dir = player->GetActorLocation() - GetActorLocation();
		//3. 노멀라이즈 (벡터의 크기를 1로 만든다)
		dir.Normalize();
	}
	else
	{
		dir = -GetActorUpVector();
	}	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//dir 방향으로 계속 간다.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	SetActorLocation(p0 + vt);
}

