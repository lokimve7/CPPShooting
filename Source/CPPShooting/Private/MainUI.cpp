// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanelSlot.h>

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	//bestScoreUI �� ���� �ٲ㺸��
	//r  g b (0 ~ 255) or (0 ~ 1) r : 1, g : 0, b : 0	
	bestScoreUI->SetColorAndOpacity(FLinearColor(FVector3f(0, 1, 0)));

	//��ġ X���� 500���� �ٲ���
	//slot�� ��������
	UPanelSlot* slot = bestScoreUI->Slot;

	//Canvas panel slot ���� Cast ������
	UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

	//��ġ�� �ٲ���
	canvasSlot->SetPosition(FVector2D(500, 108));
}

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