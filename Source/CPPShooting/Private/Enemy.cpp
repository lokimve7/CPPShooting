// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerPawn.h"
#include <Particles/ParticleSystem.h>
#include "Bullet.h"
#include "../CPPShootingGameModeBase.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	compBox->SetBoxExtent(FVector(50));
	SetRootComponent(compBox);
	//Collision Enable 설정
	compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Object Type 설정
	compBox->SetCollisionObjectType(ECC_GameTraceChannel3);
	//모든 Response 를 Ignore 로 한다.
	compBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Bullet 은 Overlap 으로 한다.
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	//DestroyZone 은 Overlap 으로 한다.
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
	

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox);
	//Collision Presets 을 NoCollision 으로 하자
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	//exploFactory 셋팅하자
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExplo(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempExplo.Succeeded())
	{
		exploFactory = tempExplo.Object;
	}

	//exploSound 셋팅하자
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
	if (tempSound.Succeeded())
	{
		exploSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//랜덤한 값을 뽑는다.(1 ~ 100)
	int32 rand = FMath::RandRange(1, 100);

	//1. 플레이어를 찾자
	AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	playerPawn = Cast<APlayerPawn>(player);

	//만약에 랜덤한 값이 50보다 작으면(50%)
	if (rand < 50)
	{		
		//2. 플레이어를 향하는 방향을 구하자. (타겟 - 나)
		//만약에 player 가 존재한다면
		if (player != nullptr)
		{
			dir = player->GetActorLocation() - GetActorLocation();
			//3. 노멀라이즈 (벡터의 크기를 1로 만든다)
			dir.Normalize();
		}
		else
		{
			dir = GetActorRightVector();
		}
	}
	else
	{
		dir = -GetActorUpVector();
	}	

	//충돌 오버랩 될 때 호출 되는 함수 등록
	compBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//dir 방향으로 계속 간다.
	//P = P0 + vt
	FVector p0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	SetActorLocation(p0 + vt);
}


void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
}

void AEnemy::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//만약에 부딪힌 놈의 이름이 Bullet 포함하고 있다면
	if (OtherActor->GetName().Contains(TEXT("Bullet")))
	{
		//총알을 비활성화
		ABullet* bullet = Cast<ABullet>(OtherActor);
		bullet->SetActive(false);
		//총알을 탄창에 넣는다.
		bullet->onDestroyBullet.Broadcast(bullet);
		//playerPawn->arrayBullet.Add(bullet);

		//폭발 효과 이펙트를 생성한다.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), exploFactory, GetActorLocation(), GetActorRotation());

		//폭발 소리를 내고 싶다.
		UGameplayStatics::PlaySound2D(GetWorld(), exploSound);

		//ACPPShootingGameModeBase를 가져오자
		AGameModeBase* mode = GetWorld()->GetAuthGameMode();
		ACPPShootingGameModeBase* currMode = Cast<ACPPShootingGameModeBase>(mode);
		//점수를 증가 시킨다
		currMode->AddScore(2);
	}
	//그렇지 않고 만약에 부딪히 놈의 이름이 Player 를 포함하고 있으면
	else if (OtherActor->GetName().Contains(TEXT("Player")))
	{
		//게임오버 UI를 띄우자
		ACPPShootingGameModeBase* currMode = GetWorld()->GetAuthGameMode<ACPPShootingGameModeBase>();
		currMode->ShowGameOverUI();

		//게임을 일시 정지
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		//마우스 커서를 보이게 하자
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}


	//2. 나를 파괴하자
	Destroy();
}

