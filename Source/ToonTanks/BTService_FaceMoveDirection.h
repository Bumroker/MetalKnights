// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FaceMoveDirection.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTService_FaceMoveDirection : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_FaceMoveDirection();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

};
