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

	//mainUI 를 만든다.
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);
	//만든 UI 를 ViewPort에 붙힌다.
	mainUI->AddToViewport();	

	//최고점수 불러오자
	LoadBestScore();
}

void ACPPShootingGameModeBase::AddScore(int32 addValue)
{
	currScore = currScore + addValue;
	mainUI->UpdateCurrScoreUI(currScore);
	//UE_LOG(LogTemp, Warning, TEXT("curr score : %d"), currScore);
	
	//만약에 현재점수가 최고점수보다 커지면
	if (currScore > bestScore)
	{
		//최고점수에 현재점수를 넣는다. 
		bestScore = currScore;
		//최고점수를 출력한다.
		mainUI->UpdateBestScoreUI(bestScore);
		//UE_LOG(LogTemp, Warning, TEXT("best score : %d"), bestScore);

		//베스트 스코어 저장
		SaveBestScore();
	}	
}

void ACPPShootingGameModeBase::SaveBestScore()
{
	//bestScore -> BestScoreData 에 있는 saveBestScore 변수에 넣는다.

	//1. UBestScoreData 를 하나 생성한다. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::CreateSaveGameObject(UBestScoreData::StaticClass());
	
	//2. 생성한 놈을 UBestScoreData 로 Cast 하자
	UBestScoreData* bestScoreData = Cast<UBestScoreData>(saveGame);

	//3. saveBestScore = bestScore
	bestScoreData->saveBestScore = bestScore;

	//4. 저장한다.
	UGameplayStatics::SaveGameToSlot(bestScoreData, TEXT("BEST_SCORE"), 0);
}

void ACPPShootingGameModeBase::LoadBestScore()
{
	//1. "BEST_SCORE"으로 되어 있는 데이터를 불러온다. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::LoadGameFromSlot(TEXT("BEST_SCORE"), 0);

	//2. 불러온 놈을 UBestScoreData 로 Cast 하자
	UBestScoreData* bestScoreData = Cast<UBestScoreData>(saveGame);

	//만약에 bestScoreData 가 nullptr 이 아니라면 (저장한 값이 있다면)
	if (bestScoreData != nullptr)
	{
		//3. bestScore = saveBestScore
		bestScore = bestScoreData->saveBestScore;

		//4. Bestscore UI 를 갱신한다.
		mainUI->UpdateBestScoreUI(bestScore);
	}
}

void ACPPShootingGameModeBase::ShowGameOverUI()
{
	//GameOverUI 를 하나 만든다.
	gameOverUI = CreateWidget<UGameOverUI>(GetWorld(), gameOverWidget);
	//만든 UI를 화면에 띄운다.
	gameOverUI->AddToViewport();
}


void ACPPShootingGameModeBase::ShuffleStudy()
{
	//1. int를 5개 담을 수 있는 배열을 만든다. 
	int32 numbers[100];

	//2. 초기값을 1 ~ 5까지 들어가게 한다. [0] = 1;, [1] = 2;, [2] = 3 ..[3] = 4...[4] = 5;
	for (int32 i = 0; i < 100; i++)
	{
		numbers[i] = i + 1;
	}

	for (int32 i = 0; i < 100; i++)
	{
		// 랜덤한 값을 뽑는다. (0 ~ 4) 
		int32 randA = FMath::RandRange(0, 99);
		// 랜덤한 값을 뽑는다. (0 ~ 4)
		int32 randB = FMath::RandRange(0, 99);

		//3. randA 자리, randB 자리 값을 바꿔보자
		//	3-1. int 변수를 하나 만들어서 1번자리 에 있는 값을 넣는다.
		int32 temp = numbers[randA];		//temp = 2, number[1] = 2, number[3] = 4
		//	3-2. 3번 자리 값을 1번 자리에 덮어씌운다.
		numbers[randA] = numbers[randB];		//temp = 2, number[1] = 4, number[3] = 4
		//	3-3. 위에 만들었던 변수 값을 3번자리에 덮어 씌운다.
		numbers[randB] = temp;				//temp = 2, number[1] = 4, number[3] = 2
	}


	FString str;
	//4. 전체 배열에 들어있는 값을 출력하자.
	for (int32 i = 0; i < 100; i++)
	{
		str.Append(FString::Printf(TEXT(" %d"), numbers[i]));
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
}