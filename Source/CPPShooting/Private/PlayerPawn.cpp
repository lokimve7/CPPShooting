// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include <Components/BoxComponent.h>
#include "Bullet.h"
#include "PointerTest.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComponent
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//RootComponent�� �����.
	SetRootComponent(compBox);
	//Box Extent ���� 50, 50, 50 ���� ����
	compBox->SetBoxExtent(FVector(50, 50, 50));

	//StaticMeshComponent
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//RootComponent �ڽ����� �����.	
	compMesh->SetupAttachment(compBox);
	//StaticMesh �� ��������
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��� ���������� �̵��ϰ� �ʹ�.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	//��, �츦 �����ϴ� ������ ���Ѵ�.
	FVector dirH = GetActorRightVector() * h; // (0, 1, 0) * h = (0, h, 0);
	//��, �ϸ� �����ϴ� ������ ���Ѵ�.
	FVector dirV = GetActorUpVector() * v; //(0, 0, 1) * v = (0, 0, v);
	//���� ���� ������ ���Ѵ�.(��������)
	FVector dir = dirH + dirV;
	//ũ�⸦ 1�� ����� �ش�.
	dir.Normalize();

	FVector p = p0 + dir * speed * DeltaTime;
	SetActorLocation(p);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Horizontal (A or D) �� ȣ��� �� ����Ǵ� �Լ� ���
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::InputHorizontal);
	//Vertical (W or S) �� ȣ��� �� ����Ǵ� �Լ� ���
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::InputVertical);
	//Fire �� ȣ��� �� ����Ǵ� �Լ� ���
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerPawn::InputFire);
}

void APlayerPawn::InputHorizontal(float value)
{
	//value ���� h ������ �ִ´�.
	h = value;
}

void APlayerPawn::InputVertical(float value)
{
	//value ���� v ������ �ִ´�.
	v = value;
}

void APlayerPawn::InputFire()
{	
	//2. �Ѿ˰��忡�� �Ѿ��� �����.
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory);
	//3. ��ġ, ȸ������ �����Ѵ�
	bullet->SetActorLocation(GetActorLocation());
	bullet->SetActorRotation(GetActorRotation());
}


