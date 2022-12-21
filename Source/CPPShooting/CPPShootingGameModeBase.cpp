// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPPShootingGameModeBase.h"
#include "MainUI.h"
#include <Blueprint/UserWidget.h>

ACPPShootingGameModeBase::ACPPShootingGameModeBase()
{
	
}

void ACPPShootingGameModeBase::BeginPlay()
{
	//mainUI 를 만든다.
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);
	//만든 UI 를 ViewPort에 붙힌다.
	mainUI->AddToViewport();	

	//최고점수를 셋팅하자
	mainUI->UpdateBestScoreUI(bestScore);
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
	}	
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