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
}

void ACPPShootingGameModeBase::AddScore(int32 addValue)
{
	currScore = currScore + addValue;
	UE_LOG(LogTemp, Warning, TEXT("curr score : %d"), currScore);
}