// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class CPPSHOOTING_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	float speed = 500;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bulletFactory;

	float h;
	float v;

	//흐르는 시간
	float currTime = 0;
	//발사 시간
	UPROPERTY(EditAnywhere)
	float fireTime = 0.01f;

	//총알 탄창
	UPROPERTY(EditAnywhere)
	TArray<class ABullet*> arrayBullet;

	//탄창 초기 갯수
	UPROPERTY(EditAnywhere)
	int32 bulletFirstCount = 10;

public:
	//사용자의 입력을 처리 함수
	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputFire();
	void MakeBullet(FVector pos, FRotator rot);

	//한번에 발사 가능 갯수
	UPROPERTY(EditAnywhere)
	int32 bulletCount = 1;
	//총알의 좌우 간격
	UPROPERTY(EditAnywhere)
	float bulletGap = 100;

	//원형으로 발사되는 총알 현재 갯수
	int32 currFireBulletCount = 100;

	void InputSkill1();
	void InputSkill2();

	UFUNCTION()
	void AddBullet(class ABullet* bullet);
};