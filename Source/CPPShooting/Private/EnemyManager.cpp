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

	//0. �ð��� �帣�� �Ѵ�.
	currTime += DeltaTime;
	//1. �����ð��� ������(currTime > createTime)
	if (currTime > createTime)
	{
		//2. ���ʹ� ���忡�� ���ʹ̸� �����Ѵ�.
		AEnemy* enemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
		/*enemy->SetActorLocation(GetActorLocation());
		enemy->SetActorRotation(GetActorRotation());*/

		//3. �帣�½ð� �ʱ�ȭ
		currTime = 0;
	}
}

