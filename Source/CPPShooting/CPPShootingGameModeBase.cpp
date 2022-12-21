// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPPShootingGameModeBase.h"
#include "MainUI.h"
#include <Blueprint/UserWidget.h>

ACPPShootingGameModeBase::ACPPShootingGameModeBase()
{
	
}

void ACPPShootingGameModeBase::BeginPlay()
{
	//mainUI �� �����.
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);
	//���� UI �� ViewPort�� ������.
	mainUI->AddToViewport();	

	//�ְ������� ��������
	mainUI->UpdateBestScoreUI(bestScore);
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