// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Aim.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTTask_Aim : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Aim();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);


};
