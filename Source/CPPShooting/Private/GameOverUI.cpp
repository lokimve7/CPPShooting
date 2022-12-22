// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Button.h>

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	//btnRetry 클릭 시 Retry 함수 연결
	btnRetry->OnClicked.AddDynamic(this, &UGameOverUI::Retry);
	//btnQuit 클릭 시 Quit 함수 연결
	btnQuit->OnClicked.AddDynamic(this, &UGameOverUI::Quit);
}

void UGameOverUI::Retry()
{
	//레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(), "StootingMap");
}

void UGameOverUI::Quit()
{
	//앱을 종료 시킨다.
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}