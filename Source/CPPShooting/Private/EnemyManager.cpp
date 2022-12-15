// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//0. 시간을 흐르게 한다.
	currTime += DeltaTime;
	//1. 일정시간이 지나면(currTime > createTime)
	if (currTime > createTime)
	{
		//2. 에너미 공장에서 에너미를 생성한다.
		AEnemy* enemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
		/*enemy->SetActorLocation(GetActorLocation());
		enemy->SetActorRotation(GetActorRotation());*/

		//3. 흐르는시간 초기화
		currTime = 0;
	}
}

