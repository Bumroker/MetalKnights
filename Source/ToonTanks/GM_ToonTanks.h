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

	UFUNCTION(BlueprintCallable)
	void ActorDied(AActor* DeadActor, bool IsEnemy);
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	int TargetEnemys=0;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);


private:

	
	class ATTPlayerController* TankPC;

	float StartDelay=3;

	void HandleGameStart();

	
	int32 GetTargetTowerCount();

    TArray<AActor*> Enemys;


};
