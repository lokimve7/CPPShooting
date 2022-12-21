// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPPShootingGameModeBase.generated.h"



UCLASS()
class CPPSHOOTING_API ACPPShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPPShootingGameModeBase();

	void DelegateTest();
	

	UFUNCTION()
	void TestFunc();
	UFUNCTION()
	void TestFunc1(int32 n);
	UFUNCTION()
	void TestFunc2(int32 n);
	UFUNCTION()
	void TestFunc3(int32 score);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMainUI* mainUI;

public:
	void AddScore(int32 addValue);
	void SaveBestScore();
	void LoadBestScore();


	void ShuffleStudy();
};
