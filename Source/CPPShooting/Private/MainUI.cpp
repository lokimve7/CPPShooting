// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>

void UMainUI::UpdateCurrScoreUI(int32 score)
{
	//currScoreUI 의 text 값을 score 값으로 한다.
	currScoreUI->SetText(FText::AsNumber(score));
}

void UMainUI::UpdateBestScoreUI(int32 bestScore)
{
	//bestScoreUI 의 text 값을 bestScore 값으로 한다.
	bestScoreUI->SetText(FText::AsNumber(bestScore));
}