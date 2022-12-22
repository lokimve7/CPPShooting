// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

//class UGameOverUI;
//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FDel, UGameOverUI, ttt, int32, score);
/**
 * 
 */
UCLASS()
class CPPSHOOTING_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnRetry;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnQuit;
};
