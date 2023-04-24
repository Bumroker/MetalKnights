// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "BTService_PlayerLocationIfSeen.h"


UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName="Refresh Player Location";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
    APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn==nullptr)return;
    if(OwnerComp.GetAIOwner()==nullptr)return;
    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)){
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());  
    }else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());  
    }
}