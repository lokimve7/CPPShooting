// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

DECLARE_DELEGATE(FMyDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FMyDelegate1, int);
DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDelegate2, int32, score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDelegate3, int32, score);

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
	

	FMyDelegate myDel;
	FMyDelegate1 myDel1;
	FMyDelegate2 myDel2;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMyDelegate3 myDel3;
};
