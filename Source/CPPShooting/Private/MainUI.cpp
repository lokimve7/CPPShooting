// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>

void UMainUI::UpdateCurrScoreUI(int32 score)
{
	//currScoreUI �� text ���� score ������ �Ѵ�.
	currScoreUI->SetText(FText::AsNumber(score));
}

void UMainUI::UpdateBestScoreUI(int32 bestScore)
{
	//bestScoreUI �� text ���� bestScore ������ �Ѵ�.
	bestScoreUI->SetText(FText::AsNumber(bestScore));
}