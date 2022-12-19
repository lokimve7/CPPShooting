// Fill out your copyright notice in the Description page of Project Settings.


#include "BG.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABG::ABG()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	SetRootComponent(compMesh);
	//충돌이 되지않게 하자
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Plane Mesh 셋팅
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	//우주그림 Material 셋팅
	ConstructorHelpers::FObjectFinder<UMaterialInterface> tempMat(TEXT("Material'/Game/MatBg.MatBg'"));
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}
}

// Called when the game starts or when spawned
void ABG::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//아래로 움직이자 P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector vt = -FVector::UpVector * 500 * DeltaTime;
	FVector p = p0 + vt;

	//만약에 위치.Z 값이 -3000보다 작아지면 (100(Plane크기) * 30(Scale) = 3000)
	if (p.Z < -3000)
	{
		//나의 위치를 위로 +6000 하겠다
		p.Z += 6000;
	}
	
	SetActorLocation(p);
}

