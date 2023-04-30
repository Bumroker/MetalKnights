// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Aim.h"
#include "AIController.h"
#include "Tank.h"

UBTTask_Aim::UBTTask_Aim()
{
    NodeName=("Aim to Player");
}

EBTNodeResult::Type UBTTask_Aim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ATank* Enemy = Cast<ATank>(OwnerComp.GetAIOwner()->GetPawn());
    if(Enemy==nullptr)return EBTNodeResult::Failed;
    if(Enemy->AutoAim==true){
        Enemy->AutoAim=false;
    }else{
        Enemy->AutoAim=true;
    }
    return EBTNodeResult::Succeeded;
}
