// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Shoot.h"
#include "AIController.h"
#include "BasePawn.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName=("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    if(OwnerComp.GetAIOwner()==nullptr)return EBTNodeResult::Failed;
    ABasePawn* Enemy = Cast<ABasePawn>(OwnerComp.GetAIOwner()->GetPawn());
    if(Enemy==nullptr)return EBTNodeResult::Failed;
    Enemy->Fire();
    return EBTNodeResult::Succeeded;
}
