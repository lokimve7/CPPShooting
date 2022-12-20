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
	//Collision Preset 을 PlayerPreset 으로 하자
	compBox->SetCollisionProfileName(TEXT("PlayerPreset"));

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
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < bulletFirstCount; i++)
	{
		//총알을 생성한다.
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, GetActorLocation(), GetActorRotation());
		//생성된 총알을 비활성화 하자
		bullet->SetActive(false);
		//생성된 총알을 arrayBullet 에 추가한다. 
		arrayBullet.Add(bullet);
	}	
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

	//시간을 흐르게 한다.
	currTime += DeltaTime;
	//흐르는 시간이 발사시간보다 커지면
	if (currTime > fireTime)
	{
		//총알을 발사한다.
		//InputFire();
		//흐르는 시간을 초기화
		currTime = 0;
	}
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
	//만약에 arrayBullet의 갯수가 0보다 클 때
	if (arrayBullet.Num() > 0)
	{
		//총알의 위치, 회전 값을 Player 값으로 셋팅한다.
		arrayBullet[0]->SetActorLocation(GetActorLocation());
		arrayBullet[0]->SetActorRotation(GetActorRotation());

		//탄창에서 하나씩 빼서 총알을 활성화 시킨다.
		arrayBullet[0]->SetActive(true);	

		//탄창에서 뺀다.
		arrayBullet.RemoveAt(0);
	}
	else
	{
		//2. 총알공장에서 총알을 만든다.
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, GetActorLocation(), GetActorRotation());
	}
}


