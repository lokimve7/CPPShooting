// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/BoxComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//box component �߰� (RootComponent��)
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	SetRootComponent(compBox);
	//box �� boxextent ���� 25, 25, 50
	compBox->SetBoxExtent(FVector(25, 25, 50));
	//Collision Preset �� BulletPreset ���� �Ѵ�.
	compBox->SetCollisionProfileName(TEXT("BulletPreset"));

	//static mesh component �߰� (box �� �ڽ�����)
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox);
	//mesh �� ������ ���� (0.5, 0.5, 1)
	compMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1));
	//Collision Preset �� NoCollision ���� �Ѵ�.
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
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

	//���࿡ compMesh�� �Ⱥ��̴� ���¶�� (��Ȱ��ȭ ����..)
	if (compMesh->IsVisible() == false) return;
	
	//��� ���� �ö󰡰� �ʹ�.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector vt = GetActorUpVector() * speed * DeltaTime;
	SetActorLocation(p0 + vt);	
}

void ABullet::SetActive(bool isActive)
{
	if (isActive == true)
	{
		//���̰� ����
		compMesh->SetVisibility(true);
		//�浹 �� �� �ְ� ����.
		compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		//������ �Ѿ��� ������ �ʰ� �Ѵ�.
		compMesh->SetVisibility(false);
		//������ �Ѿ��� �浹 �ɼ��� NoCollision ���� �Ѵ�.
		compBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
