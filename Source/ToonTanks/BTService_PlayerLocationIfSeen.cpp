// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Tank.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName="Refresh Player Location";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
    
//CAMBIAR ESTO PARA EL MULTIPLAYER
    APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
//CAMBIAR ESTO PARA EL MULTIPLAYER

    ATank* Enemy = Cast<ATank>(OwnerComp.GetAIOwner()->GetPawn());

    if(PlayerPawn==nullptr)return;
    if(OwnerComp.GetAIOwner()==nullptr)return;
    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)){
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        //OwnerComp.GetAIOwner()->SetFocus(PlayerPawn);  
        Enemy->AutoAim=true;
    }else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());  
        Enemy->AutoAim=false;
    }
}