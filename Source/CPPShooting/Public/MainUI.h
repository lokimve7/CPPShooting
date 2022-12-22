// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

DECLARE_DELEGATE(FFirstDel);
DECLARE_DELEGATE_OneParam(FSndDel, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FThdDel, int32);

UCLASS()
class CPPSHOOTING_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* currScoreUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* bestScoreUI;

public:
	void UpdateCurrScoreUI(int32 score);
	void UpdateBestScoreUI(int32 bestScore);

public:
	FFirstDel onFirstDel;
	UFUNCTION()
	void FuncFirstDel();

	FSndDel onSndDel;
	UFUNCTION()
	void FuncSndDel(int32 number);

	FThdDel onThdDel;
	UFUNCTION()
	void FuncThdDel(int32 number);

	UFUNCTION()
	void FuncThdDel2(int32 number);
};
