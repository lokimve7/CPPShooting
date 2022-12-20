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
}

void ACPPShootingGameModeBase::AddScore(int32 addValue)
{
	currScore = currScore + addValue;
	UE_LOG(LogTemp, Warning, TEXT("curr score : %d"), currScore);
}