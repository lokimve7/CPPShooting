// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Button.h>

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	//btnRetry Ŭ�� �� Retry �Լ� ����
	btnRetry->OnClicked.AddDynamic(this, &UGameOverUI::Retry);
	//btnQuit Ŭ�� �� Quit �Լ� ����
	btnQuit->OnClicked.AddDynamic(this, &UGameOverUI::Quit);
}

void UGameOverUI::Retry()
{
	//������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), "StootingMap");
}

void UGameOverUI::Quit()
{
	//���� ���� ��Ų��.
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}