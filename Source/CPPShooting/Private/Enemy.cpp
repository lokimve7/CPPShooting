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
	//Collision Enable ����
	compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Object Type ����
	compBox->SetCollisionObjectType(ECC_GameTraceChannel3);
	//��� Response �� Ignore �� �Ѵ�.
	compBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Bullet �� Overlap ���� �Ѵ�.
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	//DestroyZone �� Overlap ���� �Ѵ�.
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
	

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox);
	//Collision Presets �� NoCollision ���� ����
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	//exploFactory ��������
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExplo(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempExplo.Succeeded())
	{
		exploFactory = tempExplo.Object;
	}

	//exploSound ��������
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

	//������ ���� �̴´�.(1 ~ 100)
	int32 rand = FMath::RandRange(1, 100);

	//1. �÷��̾ ã��
	AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
	playerPawn = Cast<APlayerPawn>(player);

	//���࿡ ������ ���� 50���� ������(50%)
	if (rand < 50)
	{		
		//2. �÷��̾ ���ϴ� ������ ������. (Ÿ�� - ��)
		//���࿡ player �� �����Ѵٸ�
		if (player != nullptr)
		{
			dir = player->GetActorLocation() - GetActorLocation();
			//3. ��ֶ����� (������ ũ�⸦ 1�� �����)
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

	//�浹 ������ �� �� ȣ�� �Ǵ� �Լ� ���
	compBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//dir �������� ��� ����.
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
	//���࿡ �ε��� ���� �̸��� Bullet �����ϰ� �ִٸ�
	if (OtherActor->GetName().Contains(TEXT("Bullet")))
	{
		//�Ѿ��� ��Ȱ��ȭ
		ABullet* bullet = Cast<ABullet>(OtherActor);
		bullet->SetActive(false);
		//�Ѿ��� źâ�� �ִ´�.
		bullet->onDestroyBullet.Broadcast(bullet);
		//playerPawn->arrayBullet.Add(bullet);

		//���� ȿ�� ����Ʈ�� �����Ѵ�.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), exploFactory, GetActorLocation(), GetActorRotation());

		//���� �Ҹ��� ���� �ʹ�.
		UGameplayStatics::PlaySound2D(GetWorld(), exploSound);

		//ACPPShootingGameModeBase�� ��������
		AGameModeBase* mode = GetWorld()->GetAuthGameMode();
		ACPPShootingGameModeBase* currMode = Cast<ACPPShootingGameModeBase>(mode);
		//������ ���� ��Ų��
		currMode->AddScore(2);
	}
	//�׷��� �ʰ� ���࿡ �ε��� ���� �̸��� Player �� �����ϰ� ������
	else if (OtherActor->GetName().Contains(TEXT("Player")))
	{
		//���ӿ��� UI�� �����
		ACPPShootingGameModeBase* currMode = GetWorld()->GetAuthGameMode<ACPPShootingGameModeBase>();
		currMode->ShowGameOverUI();

		//������ �Ͻ� ����
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		//���콺 Ŀ���� ���̰� ����
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}


	//2. ���� �ı�����
	Destroy();
}

