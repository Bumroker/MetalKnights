// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	APawn* PlayerPawn;

private:
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

};
