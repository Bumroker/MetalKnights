// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GoRND.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTTask_GoRND : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GoRND();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
	float SearchLocationRadious {1200};
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector RndLocationKey;
};
