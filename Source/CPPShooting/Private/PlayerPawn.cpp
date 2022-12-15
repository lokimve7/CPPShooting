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
	//RootComponent로 만든다.
	SetRootComponent(compBox);
	//Box Extent 값을 50, 50, 50 으로 하자
	compBox->SetBoxExtent(FVector(50, 50, 50));

	//StaticMeshComponent
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//RootComponent 자식으로 만든다.	
	compMesh->SetupAttachment(compBox);
	//StaticMesh 를 셋팅하자
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

	//계속 오른쪽으로 이동하고 싶다.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	//좌, 우를 결정하는 방향을 구한다.
	FVector dirH = GetActorRightVector() * h; // (0, 1, 0) * h = (0, h, 0);
	//상, 하를 결정하는 방향을 구한다.
	FVector dirV = GetActorUpVector() * v; //(0, 0, 1) * v = (0, 0, v);
	//위에 구한 방향을 더한다.(최종방향)
	FVector dir = dirH + dirV;
	//크기를 1로 만들어 준다.
	dir.Normalize();

	FVector p = p0 + dir * speed * DeltaTime;
	SetActorLocation(p);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Horizontal (A or D) 가 호출될 때 실행되는 함수 등록
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::InputHorizontal);
	//Vertical (W or S) 가 호출될 때 실행되는 함수 등록
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::InputVertical);
	//Fire 가 호출될 때 실행되는 함수 등록
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerPawn::InputFire);
}

void APlayerPawn::InputHorizontal(float value)
{
	//value 값을 h 변수에 넣는다.
	h = value;
}

void APlayerPawn::InputVertical(float value)
{
	//value 값을 v 변수에 넣는다.
	v = value;
}

void APlayerPawn::InputFire()
{	
	//2. 총알공장에서 총알을 만든다.
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory);
	//3. 위치, 회전값을 셋팅한다
	bullet->SetActorLocation(GetActorLocation());
	bullet->SetActorRotation(GetActorRotation());
}


