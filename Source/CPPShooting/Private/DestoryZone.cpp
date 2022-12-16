// Fill out your copyright notice in the Description page of Project Settings.


#include "DestoryZone.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestoryZone::ADestoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComponent ������
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//RootComponent�� ��������
	SetRootComponent(compBox);
	//boxExtent ���� 50, 2000, 50 ����
	compBox->SetBoxExtent(FVector(50, 2000, 50));
	//Collision Preset �� DestroyPreset ���� ����
	compBox->SetCollisionProfileName(TEXT("DestroyPreset"));
}

// Called when the game starts or when spawned
void ADestoryZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//�ε��� ���� �ı�����
	OtherActor->Destroy();
}

