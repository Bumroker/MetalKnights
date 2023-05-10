// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Rotate.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Tank.h"

UBTTask_Rotate::UBTTask_Rotate()
{
    NodeName=("Activate Rotation");
}

EBTNodeResult::Type UBTTask_Rotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    if(OwnerComp.GetAIOwner()==nullptr)return EBTNodeResult::Failed;
    ATank* Enemy = Cast<ATank>(OwnerComp.GetAIOwner()->GetPawn());
    FVector LookAtTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
    if(Enemy==nullptr)return EBTNodeResult::Failed;
    Enemy->RotateForwardDirection(LookAtTarget);
    return EBTNodeResult::Succeeded;
}

