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

	//�帣�� �ð�
	float currTime = 0;
	//�߻� �ð�
	UPROPERTY(EditAnywhere)
	float fireTime = 0.01f;

	//�Ѿ� źâ
	UPROPERTY(EditAnywhere)
	TArray<class ABullet*> arrayBullet;

	//źâ �ʱ� ����
	UPROPERTY(EditAnywhere)
	int32 bulletFirstCount = 10;

public:
	//������� �Է��� ó�� �Լ�
	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputFire();
	void MakeBullet(FVector pos, FRotator rot);

	//�ѹ��� �߻� ���� ����
	UPROPERTY(EditAnywhere)
	int32 bulletCount = 1;
	//�Ѿ��� �¿� ����
	UPROPERTY(EditAnywhere)
	float bulletGap = 100;

	//�������� �߻�Ǵ� �Ѿ� ���� ����
	int32 currFireBulletCount = 100;

	void InputSkill1();
	void InputSkill2();

	UFUNCTION()
	void AddBullet(class ABullet* bullet);
};