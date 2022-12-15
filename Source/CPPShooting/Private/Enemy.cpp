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

	//������ ���� �̴´�.(1 ~ 100)
	int32 rand = FMath::RandRange(1, 100);

	//���࿡ ������ ���� 50���� ������(50%)
	if (rand < 100)
	{
		//1. �÷��̾ ã��
		AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
		//2. �÷��̾ ���ϴ� ������ ������. (Ÿ�� - ��)
		dir = player->GetActorLocation() - GetActorLocation();
		//3. ��ֶ����� (������ ũ�⸦ 1�� �����)
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

	//dir �������� ��� ����.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	SetActorLocation(p0 + vt);
}

