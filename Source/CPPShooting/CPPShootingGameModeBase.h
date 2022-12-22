// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPPShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPSHOOTING_API ACPPShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPPShootingGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//현재점수
	int32 currScore = 0;
	//최고점수
	int32 bestScore = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainUI> mainWidget;

	UPROPERTY()
	class UMainUI* mainUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverUI> gameOverWidget;

	UPROPERTY()
	class UGameOverUI* gameOverUI;

public:
	void AddScore(int32 addValue);
	void SaveBestScore();
	void LoadBestScore();

	void ShowGameOverUI();


	void ShuffleStudy();
};
