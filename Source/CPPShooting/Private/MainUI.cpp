// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanelSlot.h>

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	//bestScoreUI 의 색을 바꿔보자
	//r  g b (0 ~ 255) or (0 ~ 1) r : 1, g : 0, b : 0	
	bestScoreUI->SetColorAndOpacity(FLinearColor(FVector3f(0, 1, 0)));

	//위치 X값만 500으로 바꾸자
	//slot을 가져오자
	UPanelSlot* slot = bestScoreUI->Slot;

	//Canvas panel slot 으로 Cast 해주자
	UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

	//위치를 바꾸자
	canvasSlot->SetPosition(FVector2D(500, 108));

	//딜리게이트에 함수 등록
	onFirstDel.BindUObject(this, &UMainUI::FuncFirstDel);
	onSndDel.BindUFunction(this, TEXT("FuncSndDel"));
	onThdDel.AddUObject(this, &UMainUI::FuncThdDel);
	onThdDel.AddUObject(this, &UMainUI::FuncThdDel2);
	onThdDel.AddUObject(this, &UMainUI::FuncSndDel);
}

void UMainUI::UpdateCurrScoreUI(int32 score)
{
	//currScoreUI 의 text 값을 score 값으로 한다.
	currScoreUI->SetText(FText::AsNumber(score));

	//딜리게이트에 등록된 함수 실행
	onFirstDel.ExecuteIfBound();
	onSndDel.ExecuteIfBound(score);
	onThdDel.Broadcast(score);
}

void UMainUI::UpdateBestScoreUI(int32 bestScore)
{
	//bestScoreUI 의 text 값을 bestScore 값으로 한다.
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