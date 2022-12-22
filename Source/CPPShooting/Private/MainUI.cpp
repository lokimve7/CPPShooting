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

	//��������Ʈ�� �Լ� ���
	onFirstDel.BindUObject(this, &UMainUI::FuncFirstDel);
	onSndDel.BindUFunction(this, TEXT("FuncSndDel"));
	onThdDel.AddUObject(this, &UMainUI::FuncThdDel);
	onThdDel.AddUObject(this, &UMainUI::FuncThdDel2);
	onThdDel.AddUObject(this, &UMainUI::FuncSndDel);
}

void UMainUI::UpdateCurrScoreUI(int32 score)
{
	//currScoreUI �� text ���� score ������ �Ѵ�.
	currScoreUI->SetText(FText::AsNumber(score));

	//��������Ʈ�� ��ϵ� �Լ� ����
	onFirstDel.ExecuteIfBound();
	onSndDel.ExecuteIfBound(score);
	onThdDel.Broadcast(score);
}

void UMainUI::UpdateBestScoreUI(int32 bestScore)
{
	//bestScoreUI �� text ���� bestScore ������ �Ѵ�.
	bestScoreUI->SetText(FText::AsNumber(bestScore));
}

void UMainUI::FuncFirstDel()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void UMainUI::FuncSndDel(int32 number)
{
	UE_LOG(LogTemp, Warning, TEXT("%s, %d"), *FString(__FUNCTION__), number);
}

void UMainUI::FuncThdDel(int32 number)
{
	UE_LOG(LogTemp, Warning, TEXT("%s, %d"), *FString(__FUNCTION__), number);
}

void UMainUI::FuncThdDel2(int32 number)
{
	UE_LOG(LogTemp, Warning, TEXT("%s, %d"), *FString(__FUNCTION__), number);
}