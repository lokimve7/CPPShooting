// Fill out your copyright notice in the Description page of Project Settings.


#include "BG.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
ABG::ABG()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	SetRootComponent(compMesh);

	//Plane Mesh ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	//���ֱ׸� Material ����
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

	//�Ʒ��� �������� P = P0 + vt

	//���࿡ ��ġ.Z ���� -3000���� �۾����� (100(Planeũ��) * 30(Scale) = 3000)
	
	//���� ��ġ�� ���� +6000 �ϰڴ�
}

