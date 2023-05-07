// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FaceMoveDirection.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Tank.h"


UBTService_FaceMoveDirection::UBTService_FaceMoveDirection()
{
    NodeName="Face Move Direction";
}

void UBTService_FaceMoveDirection::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    ATank* Enemy = Cast<ATank>(OwnerComp.GetAIOwner()->GetPawn());

    FVector BBDirection = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

    Enemy->RotateForwardDirection(BBDirection);
}
