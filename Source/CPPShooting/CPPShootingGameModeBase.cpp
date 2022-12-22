// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPPShootingGameModeBase.h"
#include "MainUI.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "BestScoreData.h"
#include "GameOverUI.h"

ACPPShootingGameModeBase::ACPPShootingGameModeBase()
{
	ConstructorHelpers::FClassFinder<UMainUI> tempMainUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_MainUI.BP_MainUI_C'"));
	if (tempMainUI.Succeeded())
	{
		mainWidget = tempMainUI.Class;
	}

	ConstructorHelpers::FClassFinder<UGameOverUI> tempGameOverUI(TEXT("WidgetBlueprint'/Game/Blueprints/BP_GameOverUI.BP_GameOverUI_C'"));
	if (tempGameOverUI.Succeeded())
	{
		gameOverWidget = tempGameOverUI.Class;
	}
}

void ACPPShootingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//mainUI �� �����.
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);
	//���� UI �� ViewPort�� ������.
	mainUI->AddToViewport();	

	//�ְ����� �ҷ�����
	LoadBestScore();
}

void ACPPShootingGameModeBase::AddScore(int32 addValue)
{
	currScore = currScore + addValue;
	mainUI->UpdateCurrScoreUI(currScore);
	//UE_LOG(LogTemp, Warning, TEXT("curr score : %d"), currScore);
	
	//���࿡ ���������� �ְ��������� Ŀ����
	if (currScore > bestScore)
	{
		//�ְ������� ���������� �ִ´�. 
		bestScore = currScore;
		//�ְ������� ����Ѵ�.
		mainUI->UpdateBestScoreUI(bestScore);
		//UE_LOG(LogTemp, Warning, TEXT("best score : %d"), bestScore);

		//����Ʈ ���ھ� ����
		SaveBestScore();
	}	
}

void ACPPShootingGameModeBase::SaveBestScore()
{
	//bestScore -> BestScoreData �� �ִ� saveBestScore ������ �ִ´�.

	//1. UBestScoreData �� �ϳ� �����Ѵ�. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::CreateSaveGameObject(UBestScoreData::StaticClass());
	
	//2. ������ ���� UBestScoreData �� Cast ����
	UBestScoreData* bestScoreData = Cast<UBestScoreData>(saveGame);

	//3. saveBestScore = bestScore
	bestScoreData->saveBestScore = bestScore;

	//4. �����Ѵ�.
	UGameplayStatics::SaveGameToSlot(bestScoreData, TEXT("BEST_SCORE"), 0);
}

void ACPPShootingGameModeBase::LoadBestScore()
{
	//1. "BEST_SCORE"���� �Ǿ� �ִ� �����͸� �ҷ��´�. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::LoadGameFromSlot(TEXT("BEST_SCORE"), 0);

	//2. �ҷ��� ���� UBestScoreData �� Cast ����
	UBestScoreData* bestScoreData = Cast<UBestScoreData>(saveGame);

	//���࿡ bestScoreData �� nullptr �� �ƴ϶�� (������ ���� �ִٸ�)
	if (bestScoreData != nullptr)
	{
		//3. bestScore = saveBestScore
		bestScore = bestScoreData->saveBestScore;

		//4. Bestscore UI �� �����Ѵ�.
		mainUI->UpdateBestScoreUI(bestScore);
	}
}

void ACPPShootingGameModeBase::ShowGameOverUI()
{
	//GameOverUI �� �ϳ� �����.
	gameOverUI = CreateWidget<UGameOverUI>(GetWorld(), gameOverWidget);
	//���� UI�� ȭ�鿡 ����.
	gameOverUI->AddToViewport();
}


void ACPPShootingGameModeBase::ShuffleStudy()
{
	//1. int�� 5�� ���� �� �ִ� �迭�� �����. 
	int32 numbers[100];

	//2. �ʱⰪ�� 1 ~ 5���� ���� �Ѵ�. [0] = 1;, [1] = 2;, [2] = 3 ..[3] = 4...[4] = 5;
	for (int32 i = 0; i < 100; i++)
	{
		numbers[i] = i + 1;
	}

	for (int32 i = 0; i < 100; i++)
	{
		// ������ ���� �̴´�. (0 ~ 4) 
		int32 randA = FMath::RandRange(0, 99);
		// ������ ���� �̴´�. (0 ~ 4)
		int32 randB = FMath::RandRange(0, 99);

		//3. randA �ڸ�, randB �ڸ� ���� �ٲ㺸��
		//	3-1. int ������ �ϳ� ���� 1���ڸ� �� �ִ� ���� �ִ´�.
		int32 temp = numbers[randA];		//temp = 2, number[1] = 2, number[3] = 4
		//	3-2. 3�� �ڸ� ���� 1�� �ڸ��� ������.
		numbers[randA] = numbers[randB];		//temp = 2, number[1] = 4, number[3] = 4
		//	3-3. ���� ������� ���� ���� 3���ڸ��� ���� �����.
		numbers[randB] = temp;				//temp = 2, number[1] = 4, number[3] = 2
	}


	FString str;
	//4. ��ü �迭�� ����ִ� ���� �������.
	for (int32 i = 0; i < 100; i++)
	{
		str.Append(FString::Printf(TEXT(" %d"), numbers[i]));
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
}