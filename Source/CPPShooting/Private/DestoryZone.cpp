// Fill out your copyright notice in the Description page of Project Settings.


#include "DestoryZone.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerPawn.h"

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
	//���࿡ �ε��� ���� Bullet �̸� 
	if (OtherActor->GetName().Contains(TEXT("Bullet")))
	{
		//OtherActor -> ABullet �� Cast(����ȯ)
		ABullet* bullet = Cast<ABullet>(OtherActor);
		//��Ȱ��ȭ ����
		bullet->SetActive(false);
		//źâ�� �ִ´�.
		bullet->onDestroyBullet.Broadcast(bullet);

		////APlayerPawn �� ã��
		//AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
		//APlayerPawn* player = Cast<APlayerPawn>(actor);
		////źâ�� �ٽ� ����
		//player->arrayBullet.Add(bullet);
	}
	//�׷��� ������
	else
	{
		//�ε��� ���� �ı�����
		OtherActor->Destroy();
	}
}

