// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/BoxComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//box component 추가 (RootComponent로)
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	SetRootComponent(compBox);
	//box 의 boxextent 값을 25, 25, 50
	compBox->SetBoxExtent(FVector(25, 25, 50));
	
	//static mesh component 추가 (box 에 자식으로)
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox);
	//mesh 의 스케일 값을 (0.5, 0.5, 1)
	compMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//계속 위로 올라가고 싶다.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector vt = GetActorUpVector() * speed * DeltaTime;
	SetActorLocation(p0 + vt);
}

