// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class CPPSHOOTING_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//일정시간( 몇 초 마다..)
	UPROPERTY(EditAnywhere)
	float createTime = 2;

	//흐르는시간
	float currTime = 0;

	//에너미 공장
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> enemyFactory;
};
