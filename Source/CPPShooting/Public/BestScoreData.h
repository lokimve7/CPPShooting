// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BestScoreData.generated.h"

/**
 * 
 */
UCLASS()
class CPPSHOOTING_API UBestScoreData : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	int32 saveBestScore;
};
