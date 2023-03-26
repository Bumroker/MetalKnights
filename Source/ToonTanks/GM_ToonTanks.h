// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_ToonTanks.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AGM_ToonTanks : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	class ATank* Tank;
	class ATTPlayerController* TankPC;

	float StartDelay=3;

	void HandleGameStart();

	int32 TargetTowers=0;
	int32 GetTargetTowerCount();

};
