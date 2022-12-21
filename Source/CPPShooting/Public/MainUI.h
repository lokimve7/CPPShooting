// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
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
};
