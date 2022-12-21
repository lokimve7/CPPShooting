// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPPShootingGameModeBase.h"
#include "MainUI.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "BestScoreData.h"

ACPPShootingGameModeBase::ACPPShootingGameModeBase()
{
	
}

void ACPPShootingGameModeBase::DelegateTest()
{
	//DECLARE_DELEGATE
	//mainUI->myDel.BindUObject(this, &ACPPShootingGameModeBase::TestFunc);
	//mainUI->myDel.BindUFunction(this, TEXT("TestFunc"));
	/*mainUI->myDel.BindLambda([]()->void {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
	});*/
	
	//DECLARE_MULTICAST_DELEGATE_OneParam
	/*mainUI->myDel1.AddUObject(this, &ACPPShootingGameModeBase::TestFunc1);
	FDelegateHandle handle = mainUI->myDel1.AddUFunction(this, TEXT("TestFunc2"));
	mainUI->myDel1.Remove(handle);*/
	

	//DECLARE_DYNAMIC_DELEGATE_OneParam
	//mainUI->myDel2.BindDynamic(this, &ACPPShootingGameModeBase::TestFunc2);	
	//mainUI->myDel2.BindUFunction(this, TEXT("TestFunc2"));	

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam
	//mainUI->myDel3.AddDynamic(this, &ACPPShootingGameModeBase::TestFunc1);
	//mainUI->myDel3.AddDynamic(this, &ACPPShootingGameModeBase::TestFunc2);
	//mainUI->myDel3.RemoveDynamic(this, &ACPPShootingGameModeBase::TestFunc2);
}

void ACPPShootingGameModeBase::TestFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void ACPPShootingGameModeBase::TestFunc1(int32 n)
{
	UE_LOG(LogTemp, Warning, TEXT("%s , %d"), *FString(__FUNCTION__), n);
}

void ACPPShootingGameModeBase::TestFunc2(int32 n)
{
	UE_LOG(LogTemp, Warning, TEXT("%s , %d"), *FString(__FUNCTION__), n);
}

void ACPPShootingGameModeBase::TestFunc3(int32 score)
{
	UE_LOG(LogTemp, Warning, TEXT("%s , %d"), *FString(__FUNCTION__), score);
}

void ACPPShootingGameModeBase::BeginPlay()
{
	//mainUI �� �����.
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);
	//���� UI �� ViewPort�� ������.
	mainUI->AddToViewport();	

	//�ְ����� �ҷ�����
	LoadBestScore();

	DelegateTest();
	
	Super::BeginPlay();
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