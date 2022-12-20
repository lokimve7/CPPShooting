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

	//BoxComponent 만들자
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//RootComponent로 셋팅하자
	SetRootComponent(compBox);
	//boxExtent 값을 50, 2000, 50 으로
	compBox->SetBoxExtent(FVector(50, 2000, 50));
	//Collision Preset 을 DestroyPreset 으로 하자
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
	//만약에 부딪힌 놈이 Bullet 이면 
	if (OtherActor->GetName().Contains(TEXT("Bullet")))
	{
		//OtherActor -> ABullet 로 Cast(형변환)
		ABullet* bullet = Cast<ABullet>(OtherActor);
		//비활성화 하자
		bullet->SetActive(false);
		
		//APlayerPawn 을 찾자
		AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
		APlayerPawn* player = Cast<APlayerPawn>(actor);
		//탄창에 다시 넣자
		player->arrayBullet.Add(bullet);
	}
	//그렇지 않으면
	else
	{
		//부딪힌 놈을 파괴하자
		OtherActor->Destroy();
	}
}

